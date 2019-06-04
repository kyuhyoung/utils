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


bool is_this_camera_index(const std::string& strin)
{
	return 2 >= strin.size() && in_only_number(strin) 	
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


