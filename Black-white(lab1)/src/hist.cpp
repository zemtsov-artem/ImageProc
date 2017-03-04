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

Mat getHist(Mat& img) {
    Mat hist;
    
    int bins = 256;
    int histSize[] = {bins};
    int channels[] = {0};
    float lranges[] = {0, 256};
    const float* ranges[] = {lranges};
    
    calcHist(&img, 1, channels, Mat(), hist, 1, histSize, ranges);
    
    double max_val = 0;
    minMaxLoc(hist, 0, &max_val);
    
    int hist_h = 256;
    Mat imgHist(hist_h, bins, CV_8U);
    
    for(int i = 0; i < bins; i++) {
        line(imgHist, Point(i, hist_h - cvRound(hist.at<float>(i) * hist_h / max_val)),
             Point(i, hist_h), Scalar::all(255));
    }
    
    return imgHist;
}
