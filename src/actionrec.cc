// Copyright (c) 2019, The Regents of the University of California (Regents)
// See LICENSE for license details

#include <thread>

#include "imu.h"
#include "nfc.h"
#include "camera.h"

/*
  Action Recognizer
  
  Drives an IMU, NFC, and Video camera
  Uses Neural Network to classify action

  Author: Ryan Lorica
*/

struct imu_pid {
    int proportional;
    int integral;
    int derivative;
};

void run_imu(volatile imu_pid &out);
void run_nfc(volatile int &out);

int main()
{
    volatile imu_pid imu_out;
    
    std::thread imu_thread(run_imu, &imu_out);
    std::thread nfc_thread(run_nfc, &nfc_out);
    std::thread cam_thread(run_cam, &cam_out);

    imu_thread.join();
    nfc_thread.join();
    cam_thread.join();
}
