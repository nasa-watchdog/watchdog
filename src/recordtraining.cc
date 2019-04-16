// Copyright (c) 2019, The Regents of the University of California (Regents)
// See LICENSE for license details

#include <iostream>
#include <thread>

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

//#include "imu.h"
//#include "nfc.h"
//#include "camera.h"

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
    while (-1 !=  (opt = getopt(argc, argv, "f:s"))) {
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
    
    
    std::thread imu_thread(run_imu, &imu_out);
    std::thread nfc_thread(run_nfc, &nfc_out);
    std::thread cam_thread(run_cam, &cam_out);

    for (int i = 0; i < num_samples; i++) {

    }
    
    imu_thread.join();
    nfc_thread.join();
    cam_thread.join();
}
