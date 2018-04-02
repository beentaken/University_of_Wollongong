/*------------------------------------------------------
Student's Name: Yixiang Fan
Student's number: 5083898
Student's email address: yf874@uowmail.edu.au
-------------------------------------------------------*/
#include<iostream>
#include<cstdlib>
#include<core.hpp>
#include<highgui.hpp>
#include<imgproc.hpp>
#include<cmath>
#include<time.h>
using namespace std;
using namespace cv;

const char* srcWindowTitle = "Original";
const char* dstWindowTitle = "Scale_Down.jpg";
const char* dstWindowTitle2 = "Edge_Detection_Gradient_Operator.jpg";
const char* dstWindowTitle4 = "Edge_Detection_Binary_Morphology.jpg";

IplImage* srcImage = NULL;
IplImage* dstImage = NULL;		//scale down
IplImage* dstImage1 = NULL;		//replace dstImage in some occasion
IplImage* dstImage2 = NULL;		//edge detection - gradient operator

void on_trackbar(int threshold)
{
	cvCanny(dstImage1, dstImage2, threshold, threshold, 3);
	cvShowImage(dstWindowTitle2, dstImage2);
}

void main() {
	clock_t rbStart1, rbStart2, rbEnd1, rbEnd2;		//time the running time

	char srcImageName[100];
	cout << "Input a image file name : ";
	cin >> srcImageName;
	srcImage = cvLoadImage(srcImageName, CV_LOAD_IMAGE_UNCHANGED);
	double ratio = 0.5;
	CvSize size;
	size.width = srcImage->width * ratio;
	size.height = srcImage->height * ratio;
	int flag = 0;		//flag for LPF

	//stage 1 - scale down
	dstImage = cvCreateImage(size, srcImage->depth, srcImage->nChannels);
	cvResize(srcImage, dstImage, CV_INTER_AREA);
	//create window and display
	cvNamedWindow(srcWindowTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(dstWindowTitle, CV_WINDOW_AUTOSIZE);
	cvShowImage(srcWindowTitle, srcImage);
	cvShowImage(dstWindowTitle, dstImage);
	cvWaitKey();
	//save image
	cvSaveImage(dstWindowTitle, dstImage);
	dstImage1 = cvCloneImage(dstImage);

	//stage 2 - edge detection - gradient operator
	//LPF - applying LPF will be horrible...
	char option;
	cout << "Would you like to apply LPF? (Y/N) : ";
	cin >> option;
	if (option == 'Y' || option == 'y') {
		flag = 1;
		static Mat dstMat, lpfMat;
		dstMat = cvarrToMat(dstImage, 1);
		blur(dstMat, lpfMat, Size(3, 3));
		static IplImage lpfImage = IplImage(lpfMat);
		dstImage1 = &lpfImage;
		cvNamedWindow("LPF", CV_WINDOW_AUTOSIZE);
		cvShowImage("LPF", dstImage1);
		cvWaitKey();
		cvDestroyWindow("LPF");
	}
	dstImage2 = cvCreateImage(size, dstImage->depth, dstImage->nChannels);
	cvNamedWindow(dstWindowTitle2, CV_WINDOW_AUTOSIZE);
	int nThresholdEdge = 1;
	cvCreateTrackbar("Track Bar", dstWindowTitle2, &nThresholdEdge, 255, on_trackbar);
	//create window and display
	on_trackbar(1);
	cvWaitKey();
	//save image
	cvSaveImage("gradient.bmp", dstImage2);

	//stage 3 - line detection - gradient
	CvMemStorage *pcvMStorage3 = cvCreateMemStorage();
	double fRho = 1;
	double fTheta = CV_PI / 60;
	int nMaxLineNumber = 5;
	double fMinLineLen = 112;
	double fMinLineGap = 20;

	CvSeq *pcvSeqLines = NULL;
	//for (int i = 0; i < 200; i++) {
	//	for (int j = 0; j < 50; j++) {
	//		pcvSeqLines = cvHoughLines2(dstImage2, pcvMStorage3, CV_HOUGH_PROBABILISTIC, fRho, fTheta, nMaxLineNumber, i, j);
	//		if (pcvSeqLines->total == 2) {
	//			CvPoint* line1 = (CvPoint*)cvGetSeqElem(pcvSeqLines, 0);
	//			int l1 = cvRound(((double)(line1[1].y - line1[0].y) / (double)(line1[1].x - line1[0].x)) * 100);

	//			CvPoint* line2 = (CvPoint*)cvGetSeqElem(pcvSeqLines, 1);
	//			int l2 = cvRound(((double)(line2[1].y - line2[0].y) / (double)(line2[1].x - line2[0].x)) * 100);
	//			
	//			if (l1 == -16 && l2 == -16) {
	//				cout << i << " : " << j << endl;
	//			}
	//		}
	//			
	//	}
	//}
	
	int ht = 0;
	cout << "How many times would you like to execute Hough Transform based on gradient operator ? ";
	cin >> ht;
	
	rbStart1 = clock();		//start timing - gradient

	for (int i = 0; i < ht; i++) {
		if (flag == 1)
			pcvSeqLines = cvHoughLines2(dstImage2, pcvMStorage3, CV_HOUGH_PROBABILISTIC, fRho, fTheta, nMaxLineNumber, 106, 20);
		else
			pcvSeqLines = cvHoughLines2(dstImage2, pcvMStorage3, CV_HOUGH_PROBABILISTIC, fRho, fTheta, nMaxLineNumber, fMinLineLen, fMinLineGap);
	}
	
	rbEnd1 = clock();
	cout << "Hough Transform(gradient) " << ht << " times takes " << (double)(rbEnd1 - rbStart1) / CLOCKS_PER_SEC << " seconds." << endl;


	//calculate the angle of line
	if (pcvSeqLines->total > 0) {
		cout << "Line detection in a b/w image produced by gradient operators:" << endl;
		for (int i = 0; i < pcvSeqLines->total; i++)
		{
			CvPoint* line = (CvPoint*)cvGetSeqElem(pcvSeqLines, i);
			double y = line[1].y - line[0].y;
			double x = line[1].x - line[0].x;
			cout << "Line " << i + 1 << " is detected. Orientation = "
				<< (atan(y / x) * 180 / CV_PI) << " degrees" << endl;
		}
	}
	else {
		cout << "No straight lines detected" << endl;
	}

	//stage4 - Edge Detection - Binary Morphology
	IplImage* binaryImage = NULL;		//edge detection - binary morphology
	binaryImage = cvCreateImage(size, dstImage->depth, dstImage->nChannels);
	cvThreshold(dstImage1, binaryImage, 100, 255, CV_THRESH_BINARY);
		//display binary image
	cvNamedWindow("Binary Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Binary Image", binaryImage);
	cvWaitKey();
	cvDestroyWindow("Binary Image");

	CvMemStorage *pcvMStorage4 = cvCreateMemStorage();
	CvSeq *pcvSeq = NULL;
	cvFindContours(binaryImage, pcvMStorage4, &pcvSeq);				//find the contour
	IplImage *dstImage4 = cvCreateImage(size, IPL_DEPTH_8U, 1);
	//CvContourScanner scanner = cvStartFindContours(binaryImage, pcvMStorage4, sizeof(CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	//while (cvFindNextContour(scanner));
	//pcvSeq = cvEndFindContours(&scanner);
	cvZero(dstImage4);
	cvDrawContours(dstImage4, pcvSeq, 255, 255, 1);					//drao contour
	//I hope the system do not regard the edges of the whole picture as outline, but I failed. So I have to use cvLine to erase these 4 lines
	cvLine(dstImage4, CvPoint(0, 0), CvPoint(0, dstImage4->height - 1), 0, 2);
	cvLine(dstImage4, CvPoint(0, 0), CvPoint(dstImage4->width - 1, 0), 0, 2);
	cvLine(dstImage4, CvPoint(0, dstImage4->height - 1), CvPoint(dstImage4->width - 1, dstImage4->height - 1), 0, 2);
	cvLine(dstImage4, CvPoint(dstImage4->width - 1, 0), CvPoint(dstImage4->width - 1, dstImage4->height - 1), 0, 2);
	//create window and display
	cvNamedWindow(dstWindowTitle4, CV_WINDOW_AUTOSIZE);
	cvShowImage(dstWindowTitle4, dstImage4);
	cvSaveImage("morphology.bmp", dstImage4);
	//line detection - binary morphology
	
	//test - this part is used to find appropriate parameter for cvHoughLines2
	//for (int i = 0; i < 320; i++) {
	//	for (int j = 0; j < 320; j++) {
	//		pcvSeqLines = cvHoughLines2(dstImage2, pcvMStorage3, CV_HOUGH_PROBABILISTIC, fRho, fTheta, nMaxLineNumber, i, j);
	//		if (pcvSeqLines->total == 2) {
	//			CvPoint* line1 = (CvPoint*)cvGetSeqElem(pcvSeqLines, 0);
	//			int l1 = cvRound(((double)(line1[1].y - line1[0].y) / (double)(line1[1].x - line1[0].x)) * 100);
	//
	//			CvPoint* line2 = (CvPoint*)cvGetSeqElem(pcvSeqLines, 1);
	//			int l2 = cvRound(((double)(line2[1].y - line2[0].y) / (double)(line2[1].x - line2[0].x)) * 100);
	//			
	//			if (l1 == -16 && l2 == -16) {
	//				cout << i << " : " << j << endl;
	//			}
	//		}
	//			
	//	}
	//}
	//test end
	
	//calculate the angle of line

	cout << "How many times would you like to execute Hough Transform based on binary morphology ? ";
	cin >> ht;

	rbStart2 = clock();		//start timing - binary
	for (int i = 0; i < ht; i++) {
		if (flag == 1)
			pcvSeqLines = cvHoughLines2(dstImage2, pcvMStorage3, CV_HOUGH_PROBABILISTIC, fRho, fTheta, nMaxLineNumber, 106, 20);
		else
			pcvSeqLines = cvHoughLines2(dstImage2, pcvMStorage3, CV_HOUGH_PROBABILISTIC, fRho, fTheta, nMaxLineNumber, fMinLineLen, fMinLineGap);
	}

	rbEnd2 = clock();
	cout << "Hough Transform(binary) " << ht << " times takes " << (double)(rbEnd2 - rbStart2) / CLOCKS_PER_SEC << " seconds." << endl;

	if (pcvSeqLines->total > 0) {
		cout << "Line detection in a b/w image produced by binary morphology:" << endl;
		for (int i = 0; i < pcvSeqLines->total; i++)
		{
			CvPoint* line = (CvPoint*)cvGetSeqElem(pcvSeqLines, i);
			double y = line[1].y - line[0].y;
			double x = line[1].x - line[0].x;
			cout << "Line " << i + 1 << " is detected. Orientation = "
				<< (atan(y / x) * 180 / CV_PI) << " degrees" << endl;
		}
	}
	else {
		cout << "No straight lines detected" << endl;
	}
	cvWaitKey();

	//destroy
	cvDestroyWindow(srcWindowTitle);
	cvDestroyWindow(dstWindowTitle);
	cvDestroyWindow(dstWindowTitle2);
	cvDestroyWindow(dstWindowTitle4);
	cvReleaseImage(&srcImage);
	cvReleaseImage(&dstImage);
	cvReleaseImage(&dstImage2);
	cvReleaseImage(&binaryImage);
	cvReleaseImage(&dstImage4);

	//=====================The implementation of scaling down and edge detection(gradient operator & binary morphology) by my own code=============
	
	//char filename[100] = "D:\\asm2.bmp";
	//char saveFileName[100];
	//const char* srcWindowTitle = "Original";
	//const char* dstWindowTitle = "Scaling Down";
	//const char* dst2WindowTitle = "Edge Detection - Gradient Operator";
	//const char* dst3WindowTitle = "Edge Detection - Binary Morphology";
	//
	//IplImage *srcImage, *dstImage, *dstImage2, *dstImage3, *binaryImage;
	//srcImage = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED);

	////stage 1 - scale down
	//double scale = 0.5;
	//CvSize czSize;
	//czSize.width = srcImage->width * scale;
	//czSize.height = srcImage->height * scale;

	//dstImage = cvCreateImage(czSize, srcImage->depth, srcImage->nChannels);
	////cvResize(srcImage, dstImage, CV_INTER_AREA);		//I can use this method, but I want to test my own code
	//for (int i = 0; i < czSize.height; i++) {
	//	for (int j = 0; j < czSize.width; j++) {
	//		int v1 = cvGet2D(srcImage, 2 * i, 2 * j).val[0];
	//		int v2 = cvGet2D(srcImage, 2 * i, 2 * j + 1).val[0];
	//		int v3 = cvGet2D(srcImage, 2 * i + 1, 2 * j).val[0];
	//		int v4 = cvGet2D(srcImage, 2 * i + 1, 2 * j + 1).val[0];
	//		cvSet2D(dstImage, i, j, (v1 + v2 + v3 + v4) / 4);
	//		//cvSet2D(dstImage, i, j, cvGet2D(srcImage, 2 * i, 2 * j).val[0]); //another method
	//	}
	//}
	////display
	//cvNamedWindow(srcWindowTitle, CV_WINDOW_AUTOSIZE);
	//cvNamedWindow(dstWindowTitle, CV_WINDOW_AUTOSIZE);
	//cvShowImage(srcWindowTitle, srcImage);
	//cvShowImage(dstWindowTitle, dstImage);
	//cvWaitKey();

	////stage 2 - edge detection - gradient Operator
	//int threshold2 = 150;		//You can change this threshold to adjust the precision
	//dstImage2 = cvCreateImage(czSize, dstImage->depth, dstImage->nChannels);
	//for (int i = 1; i < czSize.height - 1; i++) {
	//	for (int j = 1; j < czSize.width - 1; j++) {
	//		int v11 = cvGet2D(dstImage, i - 1, j - 1).val[0];
	//		int v12 = cvGet2D(dstImage, i - 1, j).val[0];
	//		int v13 = cvGet2D(dstImage, i - 1, j + 1).val[0];
	//		int v21 = cvGet2D(dstImage, i, j - 1).val[0];
	//		int v22 = cvGet2D(dstImage, i, j).val[0];
	//		int v23 = cvGet2D(dstImage, i, j + 1).val[0];
	//		int v31 = cvGet2D(dstImage, i + 1, j - 1).val[0];
	//		int v32 = cvGet2D(dstImage, i + 1, j).val[0];
	//		int v33 = cvGet2D(dstImage, i + 1, j + 1).val[0];
	//		if(abs(v13+v23+v33-v11-v12-v13) + abs(v31+v32+v33-v11-v12-v13) > threshold2)
	//			cvSet2D(dstImage2, i, j, 255);
	//		else 
	//			cvSet2D(dstImage2, i, j, 0);
	//	}
	//}
	////display
	//cvNamedWindow(dst2WindowTitle, CV_WINDOW_AUTOSIZE);
	//cvShowImage(dst2WindowTitle, dstImage2);
	//cvWaitKey();

	////stage 3 - edge detection - binary morphology
	//dstImage3 = cvCreateImage(czSize, dstImage->depth, dstImage->nChannels);
	//binaryImage = cvCreateImage(czSize, dstImage->depth, dstImage->nChannels);
	////binary image processing
	//for (int i = 0; i < czSize.height; i++) {
	//	for (int j = 0; j < czSize.width; j++) {
	//		int v = cvGet2D(dstImage, i, j).val[0];
	//		if(v < 96)
	//			cvSet2D(dstImage3, i, j, 255);
	//		else
	//			cvSet2D(dstImage3, i, j, 0);
	//	}
	//}
	////erosion
	//for (int i = 0; i < czSize.height; i++) {
	//	for (int j = 0; j < czSize.width; j++) {
	//		if (i == 0 || i == czSize.height - 1 || j == 0 || j == czSize.width - 1) {
	//			cvSet2D(binaryImage, i, j, 0);
	//			continue;
	//		}
	//		int v = cvGet2D(dstImage3, i - 1, j - 1).val[0]
	//				+ cvGet2D(dstImage3, i - 1, j).val[0]
	//				+ cvGet2D(dstImage3, i - 1, j + 1).val[0]
	//				+ cvGet2D(dstImage3, i, j - 1).val[0]
	//				+ cvGet2D(dstImage3, i, j).val[0]
	//				+ cvGet2D(dstImage3, i, j + 1).val[0]
	//				+ cvGet2D(dstImage3, i + 1, j - 1).val[0]
	//				+ cvGet2D(dstImage3, i + 1, j).val[0]
	//				+ cvGet2D(dstImage3, i + 1, j + 1).val[0];
	//		if (v < 2295)
	//			cvSet2D(binaryImage, i, j, 0);
	//		else
	//			cvSet2D(binaryImage, i, j, 255);
	//	}
	//}
	////Boundary Extraction
	//for (int i = 0; i < czSize.height; i++) {
	//	for (int j = 0; j < czSize.width; j++) {
	//		int v1 = cvGet2D(dstImage3, i, j).val[0];
	//		int v2 = cvGet2D(binaryImage, i, j).val[0];
	//		if (v1 != v2)
	//			cvSet2D(dstImage3, i, j, 255);
	//		else
	//			cvSet2D(dstImage3, i, j, 0);
	//	}
	//}
	////display
	//cvNamedWindow(dst3WindowTitle, CV_WINDOW_AUTOSIZE);
	//cvShowImage(dst3WindowTitle, dstImage3);
	//cvWaitKey();

	////destroy windows
	//cvDestroyWindow(srcWindowTitle);
	//cvDestroyWindow(dstWindowTitle);
	//cvDestroyWindow(dst2WindowTitle);
	//cvDestroyWindow(dst3WindowTitle);
	////destroy image
	//cvReleaseImage(&srcImage);
	//cvReleaseImage(&dstImage);
	//cvReleaseImage(&dstImage2);
	//cvReleaseImage(&dstImage3);
	//cvWaitKey();
}
