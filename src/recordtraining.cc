// Copyright (c) 2019, The Regents of the University of California (Regents)
// See LICENSE for license details

#include <iostream>
#include <fstream>
#include <thread>

#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "imu.h"
#include "nfc.h"
#include "camera.h"

/*
  Action Recognizer
  
  Drives an IMU, NFC, and Video camera
  Uses Neural Network to classify action

  Author: Ryan Lorica
*/


int parse(int argc, char* argv[], std::string &outfile, int32_t &filelength)
{
    if (argc < 3) {
	std::cout << "Missing arguments" << std::endl;
	return -1;
    }
    int opt;
    while (-1 !=  (opt = getopt(argc, argv, "f:s:"))) {
	switch (opt) {
	case 'f':
	    outfile = optarg;
	    break;
	case 's':
	    filelength = atoi(optarg);
	    break;
	default:
	    std::cout << "Unrecognized option" << std::endl;
	    return -1;
	}
    }
    return 0;
}

int main(int argc, char* argv[])
{
    std::string outfile;
    int32_t filelength;
    if (parse(argc, argv, outfile, filelength) == -1)
	exit(1);
    
    imu_pid imu_out;
    int nfc_out;
    int cam_out;
    std::thread imu_thread(run_imu, &imu_out);
    std::thread nfc_thread(run_nfc, &nfc_out);
    std::thread cam_thread(run_cam, &cam_out);

    std::ofstream ofile;
    ofile.open(outfile);
    for (int i = 0; i < filelength; i++) {
	int32_t imu_p = imu_out.proportional;
	int32_t imu_d = imu_out.derivative;
	int32_t imu_i = imu_out.integral;
	int32_t nfc_capture = nfc_out;
	int32_t cam_capture = cam_out;
	ofile << i << ','
	      << imu_p << ','
	      << imu_d << ','
	      << imu_i << ','
	      << nfc_capture << ','
	      << cam_capture << std::endl;
    }
    ofile.close();
    
    imu_thread.join();
    nfc_thread.join();
    cam_thread.join();
}
