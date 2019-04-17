// Copyright (c) 2019, The Regents of the University of California (Regents)
// See LICENSE for license details

#ifndef IMU_H
#define IMU_H

struct imu_pid {
    int proportional;
    int integral;
    int derivative;
};

void run_imu(imu_pid *out);


#endif
