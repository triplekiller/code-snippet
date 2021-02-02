//
// Copyright 2016 Horizon Robotics.
//

#include <hobot-adas/utils/system/get_system_info.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#elif defined(__MACH__)
#include "sys/times.h"
#elif !defined(__ANDROID__) && !defined(__QNX__)
#include "sys/times.h"
#include "sys/vtimes.h"
#include "unistd.h"
#endif

namespace HobotADAS {

//////////////////////////////////////////////////////////////////////////
// cpu usage

#ifdef _WIN32
static HANDLE self;
static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
#else
static clock_t lastCPU, lastSysCPU, lastUserCPU;
#endif
static int numProcessors;

static void init_cpu_usage() {
#ifdef _WIN32
  SYSTEM_INFO sysInfo;
  FILETIME ftime, fsys, fuser;

  GetSystemInfo(&sysInfo);
  numProcessors = sysInfo.dwNumberOfProcessors;

  GetSystemTimeAsFileTime(&ftime);
  memcpy(&lastCPU, &ftime, sizeof(FILETIME));

  self = GetCurrentProcess();
  GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
  memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
  memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
#elif !defined(__ANDROID__) && !defined(__MACH__) && !defined(__QNX__)
  FILE* file;
  struct tms timeSample;
  char line[128];

  lastCPU = times(&timeSample);
  lastSysCPU = timeSample.tms_stime;
  lastUserCPU = timeSample.tms_utime;

  file = fopen("/proc/cpuinfo", "r");
  numProcessors = 0;
  while (fgets(line, 128, file) != NULL) {
    if (strncmp(line, "processor", 9) == 0) {
      numProcessors++;
    }
  }
  fclose(file);
#endif
}

class CPUUsageIniter {
 public:
  CPUUsageIniter() {
    init_cpu_usage();
  }
};
static CPUUsageIniter cpu_usage_initer_;

float GetCPUUsage() {
  float percent = -1.0f;

#ifdef _WIN32
  FILETIME ftime, fsys, fuser;
  ULARGE_INTEGER now, sys, user;

  GetSystemTimeAsFileTime(&ftime);
  memcpy(&now, &ftime, sizeof(FILETIME));

  GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
  memcpy(&sys, &fsys, sizeof(FILETIME));
  memcpy(&user, &fuser, sizeof(FILETIME));
  percent = static_cast<float>((sys.QuadPart - lastSysCPU.QuadPart)
                               + (user.QuadPart - lastUserCPU.QuadPart));
  percent /= (now.QuadPart - lastCPU.QuadPart);
  percent /= numProcessors;
  lastCPU = now;
  lastUserCPU = user;
  lastSysCPU = sys;

  percent *= 100.0f;
#elif !defined(__ANDROID__) && !defined(__MACH__) && !defined(__QNX__)
  struct tms timeSample;
  clock_t now;

  now = times(&timeSample);
  if (now <= lastCPU || timeSample.tms_stime < lastSysCPU ||
      timeSample.tms_utime < lastUserCPU) {
    // Overflow detection. Just skip this value.
    percent = -1.0f;
  } else {
    percent = static_cast<float>((timeSample.tms_stime - lastSysCPU) +
      (timeSample.tms_utime - lastUserCPU));
    percent /= static_cast<float>((now - lastCPU));
    percent /= static_cast<float>(numProcessors);
    percent *= 100.0f;
  }
  lastCPU = now;
  lastSysCPU = timeSample.tms_stime;
  lastUserCPU = timeSample.tms_utime;
#endif
  return percent;
}

//////////////////////////////////////////////////////////////////////////
// memory usage

static int parseLine(char* line) {
  // This assumes that a digit will be found and the line ends in " Kb".
  size_t i = strlen(line);
  const char* p = line;
  while (*p <'0' || *p > '9') {
    p++;
  }
  line[i - 3] = '\0';
  i = strtoul(p, NULL, 0);
  return static_cast<int>(i);
}

float GetMemUsed() {  // Note: this value is in MB!
#ifdef _WIN32
  PROCESS_MEMORY_COUNTERS pmc;
  GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
  // pmc.WorkingSetSize;
  // SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
  SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

  return physMemUsedByMe / 1024.0f / 1024.0f;
#elif !defined(__ANDROID__) && !defined(__MACH__) && !defined(__QNX__)
  FILE* file = fopen("/proc/self/status", "r");
  int result = -1;
  char line[128];

  while (fgets(line, 128, file) != NULL) {
    if (strncmp(line, "VmRSS:", 6) == 0) {
    // if (strncmp(line, "VmSize:", 7) == 0) {
      result = parseLine(line);
      break;
    }
  }
  fclose(file);
  return static_cast<float>(result) / 1024.0f;
#else
  return -1;
#endif
}

int GetProductID() {
#ifdef ADAS_ALTERA
  if (access("/usr/bin/hrut_productid", X_OK) != 0) {
    return 1;   // assume matrix 1.6
  }

  const int BLOCK_SIZE = 255;
  char *buff;
  int bufflen;
  FILE *out;
  const char *shellstr = "/usr/bin/hrut_productid";
  if (!(out = popen(shellstr, "r"))) {
    return 1;
  }

  bufflen = BLOCK_SIZE;
  buff = (char *)malloc(BLOCK_SIZE);

  int readlen = 0;
  while (!feof(out)) {
    int len = fread(buff + readlen, 1, bufflen - readlen - 1, out);
    if (len < 0) {
      break;
    } else if (len > 0) {
      readlen += len;
      if ((readlen + 1) == bufflen) {
        bufflen += BLOCK_SIZE;
        buff = (char *)realloc(buff, bufflen);
        continue;
      }
    }
  }
  fclose(out);
  buff[readlen] = '\0';
  int productid = atoi(buff);
  free(buff);

  return productid;
#else
  return -1;
#endif
}

#ifdef ADAS_J2

static int GetFirstLine(const std::string& file_name, std::string& detail) {
  std::ifstream ifs(file_name.c_str());
  if (!ifs.is_open()) {
    return -1;
  }
  std::getline(ifs, detail);
  return 0;
}

float GetCPUTemprature(void) {
  float temprature = 0.0f;
  std::string detail;
  if (!GetFirstLine("/sys/class/thermal/thermal_zone0/temp", detail)) {
    temprature =
      static_cast<float>(strtol(detail.c_str(), NULL, 0)) / 1000.f;
  }
  return temprature;
}

int64_t GetBPUFreq(int id) {
  int64_t bpu_freq = 0;
  std::string detail;
  char file_name[100] = {0};
  if (id < 2 && id >= 0) {
    snprintf(file_name, sizeof(file_name),
      "/sys/devices/system/bpu/bpu%01d/bpufreq/cur_freq", id);
    if (!GetFirstLine(file_name, detail)) {
      bpu_freq = strtoul(detail.c_str(), NULL, 0);
    }
  }
  return bpu_freq;
}

int64_t GetCPUFreq(int id) {
  int64_t cpu_freq = 0;
  std::string detail;
  if (id < 2 && id >= 0) {
    char file_name[100] = {0};
    snprintf(file_name, sizeof(file_name),
      "/sys/devices/system/cpu/cpu%01d/cpufreq/cpuinfo_cur_freq", id);
    if (!GetFirstLine(file_name, detail)) {
      cpu_freq = strtoul(detail.c_str(), NULL, 0);
    }
  }
  return cpu_freq;
}

float GetAllCPUUsage(void) {
  static uint64_t last_user = 0;
  static uint64_t last_nice = 0;
  static uint64_t last_sys = 0;
  static uint64_t last_idle = 0;
  uint64_t cur_user = 0;
  uint64_t cur_nice = 0;
  uint64_t cur_sys  = 0;
  uint64_t cur_idle = 0;
  std::string detail;
  GetFirstLine("/proc/stat", detail);
  // cpu  11758382 0 2746588 15622969 43 0 91640 0 0 0
  sscanf(detail.c_str(), "cpu %lu %lu %lu %lu",
    &cur_user, &cur_nice, &cur_sys, &cur_idle);
  // CPU usage   =   100   * (user   +   nice   +   system) /
  //  (user   +   nice   +   system   +   idle)
  float res = 0.0f;
  if (last_user) {
    uint64_t tmp = cur_user - last_user + cur_nice -
      last_nice + cur_sys - last_sys;
    res = static_cast<float>(tmp) / (tmp + cur_idle - last_idle) * 100;
  } else {
    res = 0.0f;
  }
  last_idle = cur_idle;
  last_nice = cur_nice;
  last_sys = cur_sys;
  last_user = cur_user;
  return res;
}

int16_t GetBPUUsage(int id) {
  int64_t bpu_usage = 0;
  std::string detail;
  char file_name[100] = {0};
  if (id < 2 && id >= 0) {
    snprintf(file_name, sizeof(file_name),
      "/sys/devices/system/bpu/bpu%01d/ratio", id);
    if (!GetFirstLine(file_name, detail)) {
      bpu_usage = strtoul(detail.c_str(), NULL, 0);
    }
  }
  return bpu_usage;
}

#endif

}  // namespace HobotADAS
