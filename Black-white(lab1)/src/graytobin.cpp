//
//  graytobin.cpp
//  Black-white(lab1)
//
//  Created by артем on 03.03.17.
//  Copyright © 2017 артем. All rights reserved.
//

#include <stdio.h>

// init arr
void initHistArr(uint *_histArr){
    for (int i =0; i<256; i++) {
        *(_histArr + i) = 0;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void fillArrayWithValuesFromGI(uint *_histArr ,Mat _grayScaleImageMatrix){
    Mat_<uchar> grayScaleImageMatrixPtr = _grayScaleImageMatrix;
    for (int i =0; i<_grayScaleImageMatrix.rows; i++) {
        for (int j = 0; j < _grayScaleImageMatrix.cols; j++) {
            *(_histArr+grayScaleImageMatrixPtr(i,j))+=1;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void printHistArray(uint *_histArr){
    for (int i =0; i<256; i++) {
        std::cout<<*(_histArr+i)<<" - "<<i<<std::endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
uint findMinValueInHistArrayAndFixIndex(uint *_histArr,uint *_ptrToTheFlagVariable) {
    uint tempMin = *(_histArr);
    for (int i =0; i<256; i++) {
        if (*(_histArr+i) <= tempMin ) {
            tempMin = *(_histArr+i);
            *(_ptrToTheFlagVariable) = i;
        }
        
    }
    return tempMin;
}
//////////////////////////////////////////////////////////////////////////////////////////
uint findMaxValueInHistArrayAndFixIndex(uint* _histArr,uint *_ptrToTheFlagVariable) {
    uint tempMax = *(_histArr);
    for (int i =0; i<256; i++) {
        if (*(_histArr+i) > tempMax ) {
            tempMax = *(_histArr+i);
            *(_ptrToTheFlagVariable) = i;
        }
        
    }
    return tempMax;
}
//////////////////////////////////////////////////////////////////////////////////////////
//leave this for the sufferings when you  will think that your english is good
// find max distance from line that connecting 2 points to some point from the set
//ushort findMaxDistanceFromLineToSomePoint(int _firstPoint,int _secondPoint,uint *_histArr) {
//    double maxDistance = 0;
//    int barrierObtainedByTheMethodOfTheTriangle = -1;
//    double tempValue = -1  ;
//    double numerator = -1 ,denominator = -1 ;
//    double fis,ses,ths,fos;
//    double sum;
//    for (int i = 0; i < _secondPoint - _firstPoint; i++) {
//        //числитель - numerator
//        //знаменатель - denomirator
//        
//        
//        fis = (double(_firstPoint + i) / double(_secondPoint - _firstPoint));
//        ses = -(double (*(_histArr+_firstPoint+i)) / double(*(_histArr+_secondPoint) - *(_histArr+_firstPoint) ));
//        ths = -(double(_firstPoint) / double(_secondPoint-_firstPoint));
//        fos = (double(*(_histArr+_firstPoint)) / double(*(_histArr+_secondPoint) - *(_histArr + _firstPoint) ));
//
//        sum =abs(fis+ses+ths+fos);
//        denominator = sqrt(
//                           (1 / double(pow(_secondPoint - _firstPoint, 2) )) +
//                           (1 / double(pow((*(_histArr + _secondPoint)) - *(_histArr + _firstPoint),2) ))
//                           );
////        std::cout << denominator <<" - den" << std::endl;
////        std::cout << sum <<" - sum" << std::endl;
////        std::cout<< denominator / sum << std::endl << std::endl;
//        tempValue =
//        abs(
//            (double(_firstPoint + i) / double(_secondPoint - _firstPoint)) -
//            (double (*(_histArr + _firstPoint + i)) / double(*(_histArr+_secondPoint) - *(_histArr+_firstPoint) )) -
//            (double(_firstPoint) / double(_secondPoint-_firstPoint)) +
//            (double(*(_histArr+_firstPoint)) / double(*(_histArr+_secondPoint) - *(_histArr + _firstPoint) ))
//            )  /
//        sqrt(
//             (1 / double(pow(_secondPoint - _firstPoint, 2) )) +
//             (1 / double(pow((*(_histArr + _secondPoint)) - *(_histArr + _firstPoint),2) ))
//             );
////       std::cout << tempValue << " - tempvalue"<<std::endl;
//        
//        if (  tempValue > maxDistance ){
//            maxDistance = tempValue;
//            barrierObtainedByTheMethodOfTheTriangle = _firstPoint + i ;
////            std::cout << maxDistance<<std::endl;
//        }
//        
//        if (tempValue == -1) {
////            std::cout<<"ERROR IN THE MATH" <<std::endl;
//        }
//    }
//    return barrierObtainedByTheMethodOfTheTriangle;
//}
//////////////////////////////////////////////////////////////////////////////////////////
int checkCorrect(int _value,int min,int max){
    if ( (_value <= max) && (_value >= min) ) {
        return true;
    }
    else return false;
}
//////////////////////////////////////////////////////////////////////////////////////////
void ConvertImageToBinaryWithBarrier(Mat_<uchar> _imagePtr,int _barrier ) {
    for (int i  = 0 ; i < _imagePtr.rows; i++) {
        for (int j = 0 ; j < _imagePtr.cols; j++) {
            if (_imagePtr(i,j) > _barrier) {
                _imagePtr(i,j)= 255;
            }else {
                _imagePtr(i,j)= 0;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void compareTwoMat(const Mat firstMat, const Mat secondMat) {
    Mat differenceImage = firstMat.clone();
    for (int i = 0; i < differenceImage.rows; i++) {
        for (int j = 0; j < differenceImage.cols; j++) {
            if (firstMat.at<Vec3b>(i, j) != secondMat.at<cv::Vec3b>(i, j)) {
                differenceImage.at<cv::Vec3b>(i, j) = Vec3b(255, 0, 0);
            } else {
                differenceImage.at<cv::Vec3b>(i, j) = firstMat.at<cv::Vec3b>(i, j);
            }
        }
    }
    
    imshow("Image difference", differenceImage);
}

//////////////////////////////////////////////////////////////////////////////////////////

ushort findBarrierByTriangeMethod(const int _leftPoint,const int _rightPoint, const uint * _matArr ) {
    uint desiredBarrier = _leftPoint;
    //add some aliases for more easily "for"
    double valueInTheLeftPoint = *(_matArr + _leftPoint);
    double valueInTheRightPoint = *(_matArr + _rightPoint);
    double valueInThePointFromTheSection = _leftPoint;
    double maxDistance = 0, tempDistance = 0;
    //add new double variables for a accurate calc
    double leftPoint = _leftPoint, rightPoint = _rightPoint;
    //under this line you can see some from hell
    //if you want to understand this you must read formula of line by two points
    //and formula of distance from the point to the line and combine them
    for (int i = _leftPoint ; i <= _rightPoint; i++) {
        valueInThePointFromTheSection = *(_matArr + i);
        tempDistance =
            abs(
                (1 / (rightPoint - leftPoint) ) * i +
                (-1 / (valueInTheRightPoint - valueInTheLeftPoint) * valueInThePointFromTheSection) +
                valueInTheLeftPoint / (valueInTheRightPoint - valueInTheLeftPoint) -
                leftPoint / ( rightPoint - leftPoint)
            ) /
            sqrt(
                1 / (pow(rightPoint - leftPoint, 2)) +
                1 / (pow(valueInTheRightPoint - valueInTheLeftPoint, 2) )
            );
        
        if (tempDistance > maxDistance) {
            maxDistance = tempDistance;
            desiredBarrier = i;
        }
    }
    // if you need to some debug and show intermediate values then move cout in if scope
    std::cout <<"new barrier is - " << desiredBarrier << " distance to him = " << tempDistance << std::endl;
    return desiredBarrier;
}
