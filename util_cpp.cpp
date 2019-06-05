//------------ c++ counterpart of python function "join" --------------  
// make시 -std=c++11 또는 -std=gnu++11 옵션을 주어야 함.
#include <experimental/filesystem>
string python_join_equivalent(const string& dir_to_file, const string& filename)
{
  std::experimental::filesystem::path dir(dir_to_file);
  std::experimental::filesystem::path fn(filename);    
  std::experimental::filesystem::path full_path = dir / fn;
  return full_path.u8string();                                                                               
}

//------------ Get the current time in the unit of second --------------  
//  original code : https://github.com/pjreddie/darknet/blob/master/src/utils.c
#include <sys/time.h>
#include <unistd.h>
double what_time_in_seconds_is_it_now()                                                                       
{                                   
	struct timeval time;
	if (gettimeofday(&time,NULL)) 
	{
		return 0;
	}
	return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

//------------ Check if the given directory is the existing one --------------  
#include <sys/stat.h>
bool is_this_existing_diretory(const char *direc)
{
    bool is_folder_exist = false;
    struct stat st;
    if(0 == stat(direc, &st))
    {
        if(0 != (st.st_mode & S_IFDIR))
        {
            is_folder_exist = true;
            printf("%s DOES exist. \n", dir);
        } 
    }
    return is_folder_exist;	
}

//------------ Create a directory if it does not exist --------------  
#include <sys/stat.h>
#include <stdio.h>
bool mkdir_if_not_exist(const char *direc)
{
    bool is_folder_exist = is_this_existing_folder(direc);
    if(!is_folder_exist)
    {
        int nError = 0;
#if defined(_WIN32)
        nError = _mkdir(dir);
#else
        mode_t nMode = 0733;    //UNIX style permission
        nError = mkdir(dir, nMode);
#endif
        if(0 != nError)
        {
            // handle your error
            printf("Can NOT make a directory %s\n", dir);
        }
        else
        {
            is_folder_exist = true;
            printf("Just created a directory %s\n", dir);
        }
    }
    return is_folder_exist;
}

//------------ Display error message and die --------------  
#include <stdlib.h>
#include <cstdio>
#include <cassert>
void error(const char *s)
{
    perror(s);
    assert(0);
    exit(-1);
}

//------------ Check if the string is number --------------  
bool is_only_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}


//------------ Check if the string is camera index --------------  
bool is_this_camera_index(const std::string& strin)
{
	return 2 >= strin.size() && in_only_number(strin) 	
}

//------------ Check parse string by delimiter into a vector of strings --------------  
using namespace std;
vector<string> split_string_by_delimiter(const string& strin, const string& delimiter)
{
	vector<string> li_str;
	size_t last = 0, next = 0;
	 while ((next = strin.find(delimiter, last)) != string::npos)
	 {
	 	//cout << strin.substr(last, next - last) << endl;
	 	li_str.push_back(strin.substr(last, next - last));
	 	last = next + 1;
	 }
	 //cout << strin.substr(last) << endl;
	 li_str.push_back(strin.substr(last));
	 return li_str;
}

	

/////////////////////////////////////////////////////////////////////////////////////////////////
//   OpenCV related
/////////////////////////////////////////////////////////////////////////////////////////////////

//------------ Initialized VideoCapture from either of camera or video file --------------  
#include "opencv2/highgui.hpp"
using namespace cv;
VideoCapture init_from_cam_or_video(const std::string& strin)
{
	VideoCapture cap;
	if(is_this_camera_index(strin))
   	{
		int idx_cam = std::stoi(strin);
		cap.open(idx_cam);
	}
	else
    {
		cap.open(strin);	
	}
	return cap;
}

//------------ Set the camera resolution and FPS --------------  
#include "opencv2/highgui.hpp"
using namespace cv;
void set_cam_properties_ocv(VideoCapture *cap, const int& wid, const int& hei, const int& fps)
{
	cap->grab();
	if(wid > 0) cap->set(CV_CAP_PROP_FRAME_WIDTH, wid);
	if(hei > 0) cap->set(CV_CAP_PROP_FRAME_HEIGHT, hei);
	if(fps > 0) cap->set(CV_CAP_PROP_FPS, fps);	
	return;
}


//------------ Crop a image then return the subimage --------------  	
Mat crop_image(const Mat& im_ori, const Rect& rect)	
{	
	Mat im_cropped = im_ori(rect);	
	return im_cropped;	
}	


Mat concatenate_images(const Mat& img1, const Mat& img2, int horizontal_or_vertical)	
{	
	Mat res;	
	//  Check if the two image have the same # of channels and type	
	//  If # channels or type is different	
	if(img1.type() != img2.type() || img1.channels() != img2.channels())    return res;	
	int rows = img1.rows + img2.rows, cols = img1.cols + img2.cols;	
	bool is_horizontal = true;	
	if(horizontal_or_vertical >= 0)	
	{	
		if(horizontal_or_vertical > 0)	
		{	
			is_horizontal = false;	
		}	
		else if(cols > rows)	
		{	
			is_horizontal = false;	
		}	
	}	
	// Get dimension of final image	
	if(is_horizontal)	
	{	
		rows = max(img1.rows, img2.rows);	
	}	
	else	
	{	
		cols = max(img1.cols, img2.cols);	
 	}	
 	// Create a black image	
 	//res = Mat3b(rows, cols, Vec3b(0,0,0));	
 	res = Mat::zeros(rows, cols, img1.type());	
 	// Copy images in correct position	
 	img1.copyTo(res(Rect(0, 0, img1.cols, img1.rows)));	
	if(is_horizontal)	
 	{	
 		img2.copyTo(res(Rect(img1.cols, 0, img2.cols, img2.rows)));	
 	}	
 	else	
 	{	
 		img2.copyTo(res(Rect(0, img1.rows, img2.cols, img2.rows)));	
 	}	
 	//imshow("img1", img1);waitKey();   imshow("img2", img2);   imshow("res", res); waitKey();  exit(0);	
 	return res;	
}	

