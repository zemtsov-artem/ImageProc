//
//  rgbtogray.cpp
//  Black-white(lab1)
//
//  Created by артем on 03.03.17.
//  Copyright © 2017 артем. All rights reserved.
//
//Some describe
//GI - gray image
//Arr - array
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include "src/hist.cpp"
#include "src/rgbtogray.cpp"
#include "src/graytobin.cpp"

using namespace cv;
using namespace std;

int main( )
{
    Mat img = imread("vova.jpg");
    if(! img.data ) {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    
    // rgb to gray scale
    Mat grayImg = intensity(img);
    // get histogram for gray scale
    Mat hist = getHist(grayImg);
    // declarate and init ptr and temrary min
    cv::Mat_<uchar> ptr = hist;
    cv::Mat_<uchar> GrayPtr = grayImg;
    // declarate arr
    uint *histArr = new uint[255];
    
    // init arr and filling from gray image
    initHistArr(histArr);
    fillArrayWithValuesFromGI(histArr, grayImg);
    
    // the declaration of the flags of the describing min an max
    uint leftFlag = 256, rightFlag = 0;
    findMaxValueInHistArrayAndFixIndex(histArr, &leftFlag);
    findMinValueInHistArrayAndFixIndex(histArr, &rightFlag);
    
    // declarate
    ushort barrierObtainedByTheMethodOfTheTriangle = -1;
    ushort SimpleBarrier = (rightFlag+leftFlag)/2;
    
    barrierObtainedByTheMethodOfTheTriangle = findMaxDistanceFromLineToSomePoint(
                                                                                 leftFlag,
                                                                                 rightFlag,
                                                                                 histArr);
    
    
    if ( checkCorrect(barrierObtainedByTheMethodOfTheTriangle,0,255)) {
        cout<<barrierObtainedByTheMethodOfTheTriangle<<" - unknownBarrier"<<endl;
    }
    else {
        cout<<"Wrong barrier"<<endl;
    }
    // declarate new mat to save new binary images
    Mat CoolBlackAndWhiteImage,SimpleBlackAndWhiteImage;
    
    grayImg.copyTo(CoolBlackAndWhiteImage);
    grayImg.copyTo(SimpleBlackAndWhiteImage);
    Mat_<uchar> blackAndWhiteImagePtr = CoolBlackAndWhiteImage;
    Mat_<uchar> SimpleBlackAndWhiteImagePtr = SimpleBlackAndWhiteImage;
    
    ConvertImageToBinaryWithBarrier(CoolBlackAndWhiteImage,barrierObtainedByTheMethodOfTheTriangle);
    ConvertImageToBinaryWithBarrier(SimpleBlackAndWhiteImage,SimpleBarrier);
    
    
    // show the pixels of the difference in 2 different methods
    compareTwoMat(CoolBlackAndWhiteImage,SimpleBlackAndWhiteImage);
    
    imshow("CoolBaw", CoolBlackAndWhiteImage);
    imshow("SimpleBaw",SimpleBlackAndWhiteImage);
    waitKey(0);
    return 0;
}

