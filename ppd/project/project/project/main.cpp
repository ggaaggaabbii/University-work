//
//  main.cpp
//  project
//
//  Created by Gabriel Goteciuc on 12/01/2020.
//  Copyright © 2020 Gabriel Goteciuc. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <thread>
#include <stdio.h>

using namespace cv;

int convertToInt(const char *s) {
  std::string _s(s);
  std::stringstream str(_s);
  int x;
  str >> x;
  if(!str || x <= 0) {
    return -1;
  }
  return x;
}

void displayImage(Mat &image) {
    namedWindow("Display Image", WINDOW_OPENGL);
    imshow("Display Image", image);
    waitKey(0);
}

int main(int argc, const char * argv[]) {
    
    if (argc != 2) {
      printf("Usage: main.o  <number of threads>\n");
      return -1;
    }
    
    int T = convertToInt(argv[1]);
    if(T == -1) {
      printf("Please give me a valid integer for the number of threads\n");
      return -1;
    }
    
    return 0;
}
