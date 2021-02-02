//
// Copyright 2016 Horizon Robotics.
//

#ifndef SRC_UTILS_SYSTEM_FIND_PROCESS_H_
#define SRC_UTILS_SYSTEM_FIND_PROCESS_H_

namespace HobotADAS {
int find_pid_by_name(const char* pname);
int SendADASResetSignal();
}  // namespace HobotADAS

#endif  // SRC_UTILS_SYSTEM_FIND_PROCESS_H_
