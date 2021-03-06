////
////  Find the best lines.cpp
////
////  Created by Chienfu Huang on 2014/5/22.
////  Copyright (c) 2014年 Chienfu Huang. All rights reserved.
////
#include "stdafx.h"
//#include "Find the best lines.h"
//#include "Vanishing Point.h"
//
//
//using namespace std;
//
//#define Line_Group_Range 35
//
////find_the_best_line回傳資料結構
//FTBL::FTBL()
//{
//    FTBL_Point_L = cvPoint(0, 0);
//    FTBL_Point_R = cvPoint(0, 0);
//}
//FTBL::FTBL(CvPoint Point_data_L, CvPoint Point_data_R) : FTBL_Point_L(Point_data_L), FTBL_Point_R(Point_data_R){}
//
////線段分群類別
//line_group::line_group(CvPoint firstPoint)
//{
//	angle = 0.0;
//	group_line_slope = 0.0;
//    group_slope = 0.0;
//	GroupPoint = firstPoint;
//	GroupScore = 1;
//}
//line_group::line_group(CvPoint firstPoint,double firstslope)
//{
//    angle = 0.0;
//    group_line_slope = 0.0;
//    group_slope = firstslope;
//    GroupPoint = firstPoint;
//    GroupScore = 1;
//}
//
//
//void line_group::update(CvPoint newPoint)
//{
//	GroupPoint.x = (GroupPoint.x + newPoint.x) / 2;
//	GroupPoint.y = (GroupPoint.y + newPoint.y) / 2;
//	GroupScore++;
//}
//
//void line_group::update(CvPoint newPoint,double newslope)
//{
//    GroupPoint.x = (GroupPoint.x + newPoint.x) / 2;
//    GroupPoint.y = (GroupPoint.y + newPoint.y) / 2;
//    group_slope = (group_slope + newslope) /2.0;
//    GroupScore++;
//}
//
//double line_group::calculate_the_angle(CvPoint Vanishing_Point)
//{
//	group_line_slope = line_property(Vanishing_Point, this->GroupPoint).line_slope;
//    if (group_line_slope == -1)
//    {
//        angle = 90;
//        return angle;
//    }
//	this->angle = atan(group_line_slope)*180/3.1415;
//	//cout << "\t\t\t" << "angle is : " << angle*180/3.1415 << ","<< GroupScore <<endl;
//    return angle;
//}
//
//bool sort_for_line_group_class(const line_group a, const line_group b)
//{
//	return a.GroupScore < b.GroupScore;
//}
//
//bool sort_for_line_group_class_ANGLE(const line_group a, const line_group b)
//{
//	return a.angle < b.angle;
//}
//
////計算延伸線段座標
//CvPoint Calculation_extension(CvPoint Vanishing_Point,double slope,int y)
//{
//	return cvPoint(((Vanishing_Point.y - y) - (slope*Vanishing_Point.x)) / -(slope),y);
//}
////算截距
//double calculate_intercept(CvPoint point_1,double line_slope)
//{
//    return (double)(point_1.y - line_slope * point_1.x);
//}
////畫出範圍框
//void draw_VPoint(IplImage* img, int x, int y, int vp_range)
//{
//	CvPoint VPoint, vline[4];
//	VPoint.x = x;
//	VPoint.y = y;
//	cvCircle(img, VPoint, 4, CV_RGB(0, 255, 255), 1);
//	vline[0].x = x - vp_range;
//	vline[0].y = y - vp_range;
//	vline[1].x = x + vp_range;
//	vline[1].y = y - vp_range;
//	vline[2].x = x - vp_range;
//	vline[2].y = y + vp_range;
//	vline[3].x = x + vp_range;
//	vline[3].y = y + vp_range;
//	cvLine(img, vline[0], vline[1], CV_RGB(255, 0, 255), 2);
//	cvLine(img, vline[1], vline[3], CV_RGB(255, 0, 255), 2);
//	cvLine(img, vline[0], vline[2], CV_RGB(255, 0, 255), 2);
//	cvLine(img, vline[2], vline[3], CV_RGB(255, 0, 255), 2);
//}
//
//
////找出最佳車道線
//FTBL FindTheBestLines(IplImage* Ori_pic,vector<line_property> *AllHLineSlope, CvPoint vpfnpoint, int vp_range)
//{
//	//線段分群
//	vector <line_group> line_group_data_l;
//	vector <line_group> line_group_data_r;
//    
//    for (int AHLSNum = 0; AHLSNum < (*AllHLineSlope).size(); AHLSNum++)
//    {
//        //左邊
//        if ((*AllHLineSlope)[AHLSNum].line_slope < 0)
//        {
//            CvPoint left_low_point;
//            if ((*AllHLineSlope)[AHLSNum].line_point_1->y > (*AllHLineSlope)[AHLSNum].line_point_2->y)
//                left_low_point = *(*AllHLineSlope)[AHLSNum].line_point_1;
//            else
//                left_low_point = *(*AllHLineSlope)[AHLSNum].line_point_2;
//            
//            if (line_group_data_l.size() < 1)
//            {
//                line_group tmp(left_low_point,(*AllHLineSlope)[AHLSNum].line_slope);
//                line_group_data_l.push_back(tmp);
//            }
//            else
//            {
//                //左邊群
//                bool isPass = false;
//                for (int i = 0; i < line_group_data_l.size(); i++)
//                {
//                    isPass = false;
//                    if (abs(line_group_data_l[i].GroupPoint.x - left_low_point.x) > Line_Group_Range
//                        || abs(line_group_data_l[i].GroupPoint.y - left_low_point.y) > Line_Group_Range
//                        || abs(line_group_data_l[i].group_slope - (*AllHLineSlope)[AHLSNum].line_slope) > 0.1)
//                    {
//                        continue;
//                    }
//                    else
//                    {
//                        line_group_data_l[i].update(left_low_point,(*AllHLineSlope)[AHLSNum].line_slope);
//                        isPass = true;
//                        break;
//                    }
//                }
//                if (isPass == false)
//                {
//                    line_group tmp(left_low_point,(*AllHLineSlope)[AHLSNum].line_slope);
//                    line_group_data_l.push_back(tmp);
//                }
//            }
//
//        }
//        else //右邊
//        {
//            CvPoint right_low_point;
//            if ((*AllHLineSlope)[AHLSNum].line_point_1->y > (*AllHLineSlope)[AHLSNum].line_point_2->y)
//                right_low_point = *(*AllHLineSlope)[AHLSNum].line_point_1;
//            else
//                right_low_point = *(*AllHLineSlope)[AHLSNum].line_point_2;
//            
//            if (line_group_data_r.size() < 1)
//            {
//                line_group tmp(right_low_point,(*AllHLineSlope)[AHLSNum].line_slope);
//                line_group_data_r.push_back(tmp);
//            }
//            else
//            {
//                //右邊群
//                bool isPass = false;
//                for (int i = 0; i < line_group_data_r.size(); i++)
//                {
//                    isPass = false;
//                    if (abs(line_group_data_r[i].GroupPoint.x - right_low_point.x) > Line_Group_Range
//                        || abs(line_group_data_r[i].GroupPoint.y - right_low_point.y) > Line_Group_Range
//                        || abs(line_group_data_r[i].group_slope - (*AllHLineSlope)[AHLSNum].line_slope) > 0.1)
//                    {
//                        continue;
//                    }
//                    else
//                    {
//                        line_group_data_r[i].update(right_low_point,(*AllHLineSlope)[AHLSNum].line_slope);
//                        isPass = true;
//                        break;
//                    }
//                }
//                if (isPass == false)
//                {
//                    line_group tmp(right_low_point,(*AllHLineSlope)[AHLSNum].line_slope);
//                    line_group_data_r.push_back(tmp);
//                }
//            }
//
//        }
//        
//    }
//    
//	CvPoint maxLeft, maxRight;
//	if (line_group_data_l.size() < 1 || line_group_data_r.size() < 1 )
//	{
//		cout << "沒有車道線對應資料!!" << endl;
//		return FTBL(cvPoint(0,0),cvPoint(0,0));
//	}
//	else
//	{
//		//分群計算與消失點的個別角度
//		vector<line_group>::iterator lgd_first = line_group_data_l.begin();
//		for (lgd_first; lgd_first != line_group_data_l.end(); lgd_first++)
//			lgd_first->calculate_the_angle(vpfnpoint);
//		lgd_first = line_group_data_r.begin();
//		for (lgd_first; lgd_first != line_group_data_r.end(); lgd_first++)
//			lgd_first->calculate_the_angle(vpfnpoint);
//        
////#define a
//
//		//以角度排序
//		sort(line_group_data_l.begin(), line_group_data_l.end(), sort_for_line_group_class_ANGLE);
//		//maxLeft = line_group_data_l[0].GroupPoint;
//#ifdef a
//		maxLeft = Calculation_extension(vpfnpoint, line_group_data_l[0].group_line_slope, Ori_pic->height);
//#else
//        maxLeft = Calculation_extension(vpfnpoint, line_group_data_l[0].group_slope, Ori_pic->height);
//#endif
//        for (int i = 0; i<line_group_data_l.size();i++)
//        {
//            cvCircle(Ori_pic, line_group_data_l[i].GroupPoint,4,CV_RGB(255,255,0), 10);
//        }
//        cout << "A "<< line_group_data_l[0].angle<<endl;
//        
//		sort(line_group_data_r.begin(), line_group_data_r.end(), sort_for_line_group_class_ANGLE);
//		//maxRight = line_group_data_r[line_group_data_r.size()-1].GroupPoint;
//#ifdef a
//        maxRight = Calculation_extension(vpfnpoint, line_group_data_r[line_group_data_r.size() - 1].group_line_slope, Ori_pic->height);
//#else
//        maxRight = Calculation_extension(vpfnpoint, line_group_data_r[line_group_data_r.size() - 1].group_slope, Ori_pic->height);
//        
//#endif
//        for (int i = 0; i<line_group_data_r.size();i++)
//        {
//            cvCircle(Ori_pic, line_group_data_r[i].GroupPoint,4,CV_RGB(255,255,0), 10);
//        }
//        cout << "B "<< line_group_data_r[line_group_data_r.size() - 1].angle<<endl;
//        //cvWaitKey();
//        
//		/*
//         //以分數排序
//         sort(line_group_data_l.begin(), line_group_data_l.end(), sort_for_line_group_class);
//         maxLeft = line_group_data_l[line_group_data_l.size() - 1].GroupPoint;
//         
//         sort(line_group_data_r.begin(), line_group_data_r.end(), sort_for_line_group_class);
//         maxRight = line_group_data_r[line_group_data_r.size() - 1].GroupPoint;
//         */
//        
//		/*
//         vector<line_group>::iterator psfirst = line_group_data_l.begin();
//         for (psfirst; psfirst != line_group_data_l.end(); psfirst++)
//         cout <<"左線分數" <<psfirst->GroupScore << endl;
//         vector<line_group>::iterator psfirst2 = line_group_data_r.begin();
//         for (psfirst2; psfirst2 != line_group_data_r.end(); psfirst2++)
//         cout << "右線分數" << psfirst2->GroupScore << endl;
//         */
//	}
//    
//    /*=======================線段配對==============================*/
//    //計算交點
//    line_crosspoint vPoint(line_group_data_l[0].group_slope,
//                           calculate_intercept(line_group_data_l[0].GroupPoint,
//                                               line_group_data_l[0].group_slope),
//                           line_group_data_r[line_group_data_r.size() - 1].group_slope,
//                           calculate_intercept(line_group_data_r[line_group_data_r.size() - 1].GroupPoint,
//                                               line_group_data_r[line_group_data_r.size() - 1].group_slope));
//    cvCircle(Ori_pic, vPoint.LC_point,4,CV_RGB(150,0,255), 10);
//
//    //cvWaitKey();
//    
//    /*=======================畫出車道線============================*/
//    //點
//    cvCircle(Ori_pic, vpfnpoint, 4, CV_RGB(255, 0, 255), 2);
//    //左
//    cvLine(Ori_pic, vpfnpoint, maxLeft, CV_RGB(0, 0, 255), 2);
//    cvLine(Ori_pic, vPoint.LC_point, maxLeft, CV_RGB(0, 255, 255), 2);
//    
//    //右
//    cvLine(Ori_pic, vpfnpoint, maxRight, CV_RGB(0, 0, 255), 2);
//    cvLine(Ori_pic, vPoint.LC_point, maxRight, CV_RGB(0, 255, 255), 2);
//    
//	cout << "左群有: " << line_group_data_l.size() << "\t右群有: " << line_group_data_r.size() << endl;
//	cout << "左群最大點: " << maxLeft.x << "," << maxLeft.y << "\t右群最大點: " << maxRight.x << "," << maxRight.y << endl;
//	//cvWaitKey();
//	//清除車道線斜率記錄vector
//	/*vector <line_property> Nls, Nrs;
//     newleftSlope.clear();
//     newrightSlope.clear();
//     newleftSlope.swap(Nls);
//     newrightSlope.swap(Nrs);*/
//    
//	//清除線段分群記錄vector
//	vector <line_group> Nllgd,Nlrgd;
//	line_group_data_l.clear();
//	line_group_data_l.swap(Nllgd);
//	line_group_data_r.clear();
//	line_group_data_r.swap(Nlrgd);
//    
//	return FTBL(maxLeft ,maxRight);
//}
//
//
#include <math.h>
#include "Find the best lines.h"
#include "Vanishing Point.h"


using namespace std;

#define Line_Group_Range 35
#define Line_Group_lenRange 100

//find_the_best_line回傳資料結構
FTBL::FTBL()
{
    FTBL_Point_L = cvPoint(0, 0);
    FTBL_Point_R = cvPoint(0, 0);
}
FTBL::FTBL(CvPoint Point_data_L, CvPoint Point_data_R) : FTBL_Point_L(Point_data_L), FTBL_Point_R(Point_data_R){}

//線段分群類別
line_group::line_group(CvPoint firstPoint)
{
	angle = 0.0;
	group_line_slope = 0.0;
    group_slope = 0.0;
	GroupPoint = firstPoint;
	GroupScore = 1;
}

line_group::line_group(CvPoint firstPoint,double firstslope)
{
    angle = 0.0;
    group_line_slope = 0.0;
    group_slope = firstslope;
    GroupPoint = firstPoint;
    GroupScore = 1;
}

line_group::line_group(vector<line_property> *line,int LineNum)
{
    LineNumTable.push_back(LineNum);
    OmniLineData = line;
    angle = 0.0;
    group_line_slope = 0.0;
    group_slope = (*OmniLineData)[LineNum].line_slope;
    //記錄點為最低點
    if ((*OmniLineData)[LineNum].line_point_1->y > (*OmniLineData)[LineNum].line_point_2->y)
    {
        GroupPoint.x += (*OmniLineData)[LineNum].line_point_1->x;
        GroupPoint.y += (*OmniLineData)[LineNum].line_point_1->y;
        GroupPoint_up.x += (*OmniLineData)[LineNum].line_point_2->x;
        GroupPoint_up.y += (*OmniLineData)[LineNum].line_point_2->y;
    }
    else
    {
        GroupPoint.x += (*OmniLineData)[LineNum].line_point_2->x;
        GroupPoint.y += (*OmniLineData)[LineNum].line_point_2->y;
        GroupPoint_up.x += (*OmniLineData)[LineNum].line_point_1->x;
        GroupPoint_up.y += (*OmniLineData)[LineNum].line_point_1->y;
    }
    GroupScore = 1;
}

void line_group::update(CvPoint newPoint)
{
	GroupPoint.x = (GroupPoint.x + newPoint.x) / 2;
	GroupPoint.y = (GroupPoint.y + newPoint.y) / 2;
	GroupScore++;
}

void line_group::update(CvPoint newPoint,double newslope)
{
    GroupPoint.x = (GroupPoint.x + newPoint.x) / 2;
    GroupPoint.y = (GroupPoint.y + newPoint.y) / 2;
    group_slope = (group_slope + newslope) /2.0;
    GroupScore++;
}

void line_group::update(int LineNum)
{
    LineNumTable.push_back(LineNum);
    GroupPoint.x = 0;
    GroupPoint.y = 0;
    group_slope = 0.0;

    for (vector<int>::iterator lnt_first = LineNumTable.begin();
         lnt_first != LineNumTable.end();
         lnt_first++)
    {
        //記錄點為最低點
        if ((*OmniLineData)[*lnt_first].line_point_1->y > (*OmniLineData)[*lnt_first].line_point_2->y)
        {
            GroupPoint.x += (*OmniLineData)[*lnt_first].line_point_1->x;
            GroupPoint.y += (*OmniLineData)[*lnt_first].line_point_1->y;
            GroupPoint_up.x += (*OmniLineData)[*lnt_first].line_point_2->x;
            GroupPoint_up.y += (*OmniLineData)[*lnt_first].line_point_2->y;
        }
        else
        {
            GroupPoint.x += (*OmniLineData)[*lnt_first].line_point_2->x;
            GroupPoint.y += (*OmniLineData)[*lnt_first].line_point_2->y;
            GroupPoint_up.x += (*OmniLineData)[*lnt_first].line_point_1->x;
            GroupPoint_up.y += (*OmniLineData)[*lnt_first].line_point_1->y;
        }
        group_slope += (*OmniLineData)[*lnt_first].line_slope;
    }
    
    GroupPoint.x /= LineNumTable.size();
    GroupPoint.y /= LineNumTable.size();
    group_slope /= (float)LineNumTable.size();

    GroupScore++;
}

double line_group::calculate_the_angle(CvPoint Vanishing_Point)
{
	group_line_slope = line_property(Vanishing_Point, this->GroupPoint).line_slope;
    if (group_line_slope == -1)
    {
        angle = 90;
        return angle;
    }
	this->angle = atan(group_line_slope)*180/3.1415;
	//cout << "\t\t\t" << "angle is : " << angle*180/3.1415 << ","<< GroupScore <<endl;
    return angle;
}


//確認是否為該群線段
bool line_group::CompareLine2Group (int LineNum, int range, double lenRange)
{
    if ((*OmniLineData)[LineNum].line_point_1->y > (*OmniLineData)[LineNum].line_point_2->y)
    {
        //比較點位置(line_point_1在下)
        if(abs(GroupPoint.x - (*OmniLineData)[LineNum].line_point_1->x) <= range
            && abs(GroupPoint.y - (*OmniLineData)[LineNum].line_point_1->y) <= range
            && abs(GroupPoint_up.x - (*OmniLineData)[LineNum].line_point_2->x) <= range
            && abs(GroupPoint_up.y - (*OmniLineData)[LineNum].line_point_2->y) <= range
           )
        {
            if(!(group_slope - (*OmniLineData)[LineNum].line_slope > 0.1))
            {
                double GroupLineDistance = countDistance(GroupPoint, GroupPoint_up);
                double NewLineDeatance = countDistance(*(*OmniLineData)[LineNum].line_point_1, *(*OmniLineData)[LineNum].line_point_2);
                if (abs(GroupLineDistance - NewLineDeatance) <= lenRange) {
                    return true;
                }
            }
        }
        return false;
    }
    else
    {
        //比較點位置(line_point_2在下)
        if(abs(GroupPoint.x - (*OmniLineData)[LineNum].line_point_2->x) <= range
           && abs(GroupPoint.y - (*OmniLineData)[LineNum].line_point_2->y) <= range
           && abs(GroupPoint_up.x - (*OmniLineData)[LineNum].line_point_1->x) <= range
           && abs(GroupPoint_up.y - (*OmniLineData)[LineNum].line_point_1->y) <= range
           )
        {
            if(!(group_slope - (*OmniLineData)[LineNum].line_slope > 0.1))
            {
                double GroupLineDistance = countDistance(GroupPoint, GroupPoint_up);
                double NewLineDeatance = countDistance(*(*OmniLineData)[LineNum].line_point_1, *(*OmniLineData)[LineNum].line_point_2);
                if (abs(GroupLineDistance - NewLineDeatance) <= lenRange) {
                    return true;
                }
            }
        }
        return false;
    }
}

//計算長度
double line_group::countDistance (CvPoint line1,CvPoint line2)
{
    return sqrt((pow((double)(line2.x-line1.x),2.0)+pow((double)(line2.y-line1.y),2.0)));
}

//自訂排序演算法
bool sort_for_line_group_class(const line_group a, const line_group b)
{
	return a.GroupScore < b.GroupScore;
}

bool sort_for_line_group_class_ANGLE(const line_group a, const line_group b)
{
	return a.angle < b.angle;
}

//計算延伸線段座標
CvPoint Calculation_extension(CvPoint Vanishing_Point,double slope,int y)
{
	return cvPoint(((Vanishing_Point.y - y) - (slope*Vanishing_Point.x)) / -(slope),y);
}
//算截距
double calculate_intercept(CvPoint point_1,double line_slope)
{
    return (double)(point_1.y - line_slope * point_1.x);
}
//畫出範圍框
void draw_VPoint(IplImage* img, int x, int y, int vp_range)
{
	CvPoint VPoint, vline[4];
	VPoint.x = x;
	VPoint.y = y;
	cvCircle(img, VPoint, 4, CV_RGB(0, 255, 255), 1);
	vline[0].x = x - vp_range;
	vline[0].y = y - vp_range;
	vline[1].x = x + vp_range;
	vline[1].y = y - vp_range;
	vline[2].x = x - vp_range;
	vline[2].y = y + vp_range;
	vline[3].x = x + vp_range;
	vline[3].y = y + vp_range;
	cvLine(img, vline[0], vline[1], CV_RGB(255, 0, 255), 2);
	cvLine(img, vline[1], vline[3], CV_RGB(255, 0, 255), 2);
	cvLine(img, vline[0], vline[2], CV_RGB(255, 0, 255), 2);
	cvLine(img, vline[2], vline[3], CV_RGB(255, 0, 255), 2);
}


//找出最佳車道線
FTBL FindTheBestLines(IplImage* Ori_pic,vector<line_property> *AllHLineSlope, CvPoint vpfnpoint, int vp_range)
{
	//線段分群
	vector <line_group> line_group_data_l;
	vector <line_group> line_group_data_r;
    
    for (int AHLSNum = 0; AHLSNum < (*AllHLineSlope).size(); AHLSNum++)
    {
        //左邊
        if ((*AllHLineSlope)[AHLSNum].line_slope < 0)
        {
            if (line_group_data_l.size() < 1)
            {
                line_group tmp(AllHLineSlope,AHLSNum);
                line_group_data_l.push_back(tmp);
            }
            else
            {
                bool isPass = false;
                for (int i = 0; i < line_group_data_l.size(); i++)
                {
                    isPass = line_group_data_l[i].CompareLine2Group(AHLSNum, Line_Group_Range,Line_Group_lenRange);
                    if (isPass)
                    {
                        line_group_data_l[i].update(AHLSNum);
                        break;
                    }
                }
                if (isPass == false)
                {
                    line_group tmp(AllHLineSlope,AHLSNum);
                    line_group_data_l.push_back(tmp);
                }
            }

        }
        else //右邊
        {
            if (line_group_data_r.size() < 1)
            {
                line_group tmp(AllHLineSlope,AHLSNum);
                line_group_data_r.push_back(tmp);
            }
            else
            {
                bool isPass = false;
                for (int i = 0; i < line_group_data_r.size(); i++)
                {
                    isPass = line_group_data_r[i].CompareLine2Group(AHLSNum, Line_Group_Range,Line_Group_lenRange);
                    if (isPass)
                    {
                        line_group_data_r[i].update(AHLSNum);
                        break;
                    }
                }
                if (isPass == false)
                {
                    line_group tmp(AllHLineSlope,AHLSNum);
                    line_group_data_r.push_back(tmp);
                }
            }

        }
        
    }
    
	CvPoint maxLeft, maxRight;
	if (line_group_data_l.size() < 1 || line_group_data_r.size() < 1 )
	{
		cout << "沒有車道線對應資料!!" << endl;
		return FTBL(cvPoint(0,0),cvPoint(0,0));
	}
	else
	{
		//分群計算與消失點的個別角度
		vector<line_group>::iterator lgd_first = line_group_data_l.begin();
		for (lgd_first; lgd_first != line_group_data_l.end(); lgd_first++)
			lgd_first->calculate_the_angle(vpfnpoint);
		lgd_first = line_group_data_r.begin();
		for (lgd_first; lgd_first != line_group_data_r.end(); lgd_first++)
			lgd_first->calculate_the_angle(vpfnpoint);
        
//#define a

		//以角度排序
		sort(line_group_data_l.begin(), line_group_data_l.end(), sort_for_line_group_class_ANGLE);
		//maxLeft = line_group_data_l[0].GroupPoint;
#ifdef a
		maxLeft = Calculation_extension(vpfnpoint, line_group_data_l[0].group_line_slope, Ori_pic->height);
#else
        maxLeft = Calculation_extension(vpfnpoint, line_group_data_l[0].group_slope, Ori_pic->height);
#endif
        for (int i = 0; i<line_group_data_l.size();i++)
        {
            cvCircle(Ori_pic, line_group_data_l[i].GroupPoint,4,CV_RGB(255,255,0), 10);
        }
        cout << "A "<< line_group_data_l[0].angle<<endl;
        
		sort(line_group_data_r.begin(), line_group_data_r.end(), sort_for_line_group_class_ANGLE);
		//maxRight = line_group_data_r[line_group_data_r.size()-1].GroupPoint;
#ifdef a
        maxRight = Calculation_extension(vpfnpoint, line_group_data_r[line_group_data_r.size() - 1].group_line_slope, Ori_pic->height);
#else
        maxRight = Calculation_extension(vpfnpoint, line_group_data_r[line_group_data_r.size() - 1].group_slope, Ori_pic->height);
        
#endif
        for (int i = 0; i<line_group_data_r.size();i++)
        {
            cvCircle(Ori_pic, line_group_data_r[i].GroupPoint,4,CV_RGB(255,255,0), 10);
        }
        cout << "B "<< line_group_data_r[line_group_data_r.size() - 1].angle<<endl;
        //cvWaitKey();
        
		/*
         //以分數排序
         sort(line_group_data_l.begin(), line_group_data_l.end(), sort_for_line_group_class);
         maxLeft = line_group_data_l[line_group_data_l.size() - 1].GroupPoint;
         
         sort(line_group_data_r.begin(), line_group_data_r.end(), sort_for_line_group_class);
         maxRight = line_group_data_r[line_group_data_r.size() - 1].GroupPoint;
         */
        
		/*
         vector<line_group>::iterator psfirst = line_group_data_l.begin();
         for (psfirst; psfirst != line_group_data_l.end(); psfirst++)
         cout <<"左線分數" <<psfirst->GroupScore << endl;
         vector<line_group>::iterator psfirst2 = line_group_data_r.begin();
         for (psfirst2; psfirst2 != line_group_data_r.end(); psfirst2++)
         cout << "右線分數" << psfirst2->GroupScore << endl;
         */
	}
    
    /*=======================線段配對==============================*/
    //計算交點
    /*line_crosspoint vPoint(line_group_data_l[0].group_slope,
                           calculate_intercept(line_group_data_l[0].GroupPoint,
                                               line_group_data_l[0].group_slope),
                           line_group_data_r[line_group_data_r.size() - 1].group_slope,
                           calculate_intercept(line_group_data_r[line_group_data_r.size() - 1].GroupPoint,
                                               line_group_data_r[line_group_data_r.size() - 1].group_slope));
    cvCircle(Ori_pic, vPoint.LC_point,4,CV_RGB(150,0,255), 10);
     */
    //cvWaitKey();
    
    /*=======================畫出車道線============================*/
    //點
    cvCircle(Ori_pic, vpfnpoint, 4, CV_RGB(255, 0, 255), 2);
    //左
    cvLine(Ori_pic, vpfnpoint, maxLeft, CV_RGB(0, 0, 255), 2);
    
    //右
    cvLine(Ori_pic, vpfnpoint, maxRight, CV_RGB(0, 0, 255), 2);
    
	cout << "左群有: " << line_group_data_l.size() << "\t右群有: " << line_group_data_r.size() << endl;
	cout << "左群最大點: " << maxLeft.x << "," << maxLeft.y << "\t右群最大點: " << maxRight.x << "," << maxRight.y << endl;
	//cvWaitKey();
	//清除車道線斜率記錄vector
	/*vector <line_property> Nls, Nrs;
     newleftSlope.clear();
     newrightSlope.clear();
     newleftSlope.swap(Nls);
     newrightSlope.swap(Nrs);*/
    
	//清除線段分群記錄vector
	vector <line_group> Nllgd,Nlrgd;
	line_group_data_l.clear();
	line_group_data_l.swap(Nllgd);
	line_group_data_r.clear();
	line_group_data_r.swap(Nlrgd);
    
	return FTBL(maxLeft ,maxRight);
}



