////
////  graytobin.cpp
////  Black-white(lab1)
////
////  Created by артем on 03.03.17.
////  Copyright © 2017 артем. All rights reserved.
////
//
//#include <stdio.h>
//
//#include "rgbtogray.cpp"
//
//int tempMin = 255;
//int temMax = 0;
//uint *histArr = new uint[255];
//
//
//// init arr
//for (int i =0; i<256; i++) {
//    *(histArr+i) = 0;
//}
//
//void fillArray(cv::Mat_<uchar> _hist){
//    for (int i =0; i<_hist.rows; i++) {
//        for (int j = 0; j < _hist.cols; j++) {
//            *(histArr+_hist(i,j))+=1;
//        }
//    }
//}
//
//void printHistArray(cv::Mat_<uchar> _ptr){
//    for (int i =0; i<256; i++) {
//        cout<<*(histArr+i)<<" - "<<i<<endl;
//    }
//}
//
//int findMin(cv::Mat_<uchar> _ptr) {
//    for (int i =0; i<256; i++) {
//        if (*(histArr+i) < tempMin ) {
//            tempMin = *(histArr+i);
//        }
//        
//    }
//    return tempMin;
//}
//
//    
//    
//    
//    
//    
