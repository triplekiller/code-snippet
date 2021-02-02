//
// Copyright 2016 Horizon Robotics.
//

#include <hobot-adas/utils/system/find_process.h>

#ifndef _WIN32
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <signal.h>
#endif
#include <iostream>

namespace HobotADAS {

int find_pid_by_name(const char *pname) {
#ifndef _WIN32
  DIR *dir;
  struct dirent *next;

  dir = opendir("/proc");
  if (!dir) {
    return -2;
  }

  while (true) {
    next = readdir(dir);
    if (next == NULL) {
      break;
    }
    FILE *status;
    const int kReadBufSize = 50;
    char filename[kReadBufSize];
    char buffer[kReadBufSize];
    char name[kReadBufSize];

    /* Must skip ".." since that is outside /proc */
    if (strncmp(next->d_name, "..", 2) == 0) {
      continue;
    }

    /* If it isn't a number, we don't want it */
    if (!isdigit(*next->d_name)) {
      continue;
    }

    snprintf(filename, sizeof(filename), "/proc/%s/status", next->d_name);
    status = fopen(filename, "r");
    if (!status) {
      continue;
    }
    if (fgets(buffer, kReadBufSize - 1, status) == NULL) {
      fclose(status);
      continue;
    }
    fclose(status);

    /* Buffer should contain a string like "Name:   binary_name" */
    sscanf(buffer, "%*s %s", name);
    // suppose pname max len is 100
    if (strncmp(name, pname, strnlen(pname, 100)) == 0) {
      closedir(dir);
      return static_cast<int>(strtol(next->d_name, NULL, 0));
    }
  }

  closedir(dir);
#endif

  return -1;
}

int SendADASResetSignal() {
#if !defined(_WIN32) && !defined(__ANDROID__) && !defined(__MACH__)
  int sig = SIGRTMIN;
  int pid;
  int ret = 0;

  // internal reset signal, do not wait trigger signal
  union sigval mysigval;
  mysigval.sival_int = 1;

  pid = getpid();

  ret = sigqueue(pid, sig, mysigval);
  if (ret != 0) {
    printf("Sigqueue failed %d\n", ret);
    return -3;
  }
#endif
  return 0;
}
}  // namespace HobotADAS
