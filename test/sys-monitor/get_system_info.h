//
// Copyright 2016 Horizon Robotics.
//

#ifndef HOBOT_ADAS_UTILS_SYSTEM_GET_SYSTEM_INFO_H_
#define HOBOT_ADAS_UTILS_SYSTEM_GET_SYSTEM_INFO_H_
#include <stdint.h>
namespace HobotADAS {

float GetCPUUsage();

float GetMemUsed();

// -1 : not supported
// 0: unknown, probably 1.6
// 1: matrix 1.6
// 2: matrix 1.7
int GetProductID();

#ifdef ADAS_J2
float GetCPUTemprature(void);
int64_t GetBPUFreq(int id);
int64_t GetCPUFreq(int id);
float GetAllCPUUsage(void);
int16_t GetBPUUsage(int id);
#endif

}  // namespace HobotADAS

#endif  // HOBOT_ADAS_UTILS_SYSTEM_GET_SYSTEM_INFO_H_
