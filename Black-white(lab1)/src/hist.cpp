//
//  hist.cpp
//  Black-white(lab1)
//
//  Created by артем on 03.03.17.
//  Copyright © 2017 артем. All rights reserved.
//


#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"

using namespace cv;

void getNewHist(uint *_arrayPtr,uint _sizeOfArray,uint _maxValueInArray) {
    //create zero mat
    Mat myHist = Mat::zeros(_maxValueInArray,_sizeOfArray,CV_8U);
    //fill mat
    for (int i = 0; i < 255; i++) {
        for (int j = 0; j < *(_arrayPtr + i); j += 2) {
            myHist.at<uchar>(_maxValueInArray - j / 2 , i) = 255;
        }
    }
    //show histogram
    imshow("Myhist",myHist);
    
}
