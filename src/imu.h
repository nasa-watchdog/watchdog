// Copyright (c) 2019, The Regents of the University of California (Regents)
// See LICENSE for license details

struct imu_pid {
    int proportional;
    int integral;
    int dervative;
};

void run_imu(volatile imu_pid &out);
