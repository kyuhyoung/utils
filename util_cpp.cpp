//------------ c++ counterpart of python function "join" -------------- 
//	experimental::filesystem linker error 시
//	Makefile에 -lstdc++fs 옵션을 주어야 함.
//	https://stackoverflow.com/questions/33149878/experimentalfilesystem-linker-error
//
//	cout << python_join_equivalent("/home/someuser/", "/somefolder/somefile.somext");
//	=> /home/someuser/somefolder/somefile.somext

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
bool is_this_existing_directory(const char *direc)
{
    bool is_folder_exist = false;
    struct stat st;
    if(0 == stat(direc, &st))
    {
        if(0 != (st.st_mode & S_IFDIR))
        {
            is_folder_exist = true;
            printf("%s DOES exist. \n", direc);
        } 
    }
    return is_folder_exist;	
}

//------------ Create a directory if it does not exist --------------  
#include <sys/stat.h>
#include <stdio.h>
bool mkdir_if_not_exist(const char *direc)
{
    bool is_folder_exist = is_this_existing_directory(direc);
    if(!is_folder_exist)
    {
        int nError = 0;
#if defined(_WIN32)
        nError = _mkdir(direc);
#else
        mode_t nMode = 0733;    //UNIX style permission
        nError = mkdir(direc, nMode);
#endif
        if(0 != nError)
        {
            // handle your error
            printf("Can NOT make a directory %s\n", direc);
        }
        else
        {
            is_folder_exist = true;
            printf("Just created a directory %s\n", direc);
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
//	cout << is_only_number("001234");
//	=> true
#include <algorithm>
bool is_only_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}


//------------ Check if the string is camera index --------------  
//	cout << is_this_camera_index("04");
//	=> true
bool is_this_camera_index(const std::string& strin)
{
	return 2 >= strin.size() && is_only_number(strin);	
}

//------------ Check parse string by delimiter into a vector of strings --------------  
//	vector<string> li_str = split_string_by_delimiter("10,abc,234,3rf");
//	for(int i = 0; i < li_str.size(); i++) cout << li_str[i] << " ";
//	=> 10 abc 234 3rf
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

//------------ Check if the first integer is one of factors of the second integer --------------  
//	cout << is_first_a_factor_of_second(3, 15) << endl;
//	=> true
//	cout << is_first_a_factor_of_second(2, 15) << endl;
//	=> false
bool is_first_a_factor_of_second(int first, int second)
{
    return 0 == second % first;
}

//------------ Integer to string with formatting --------------  
//	cout << itos_formatted(278, 5) << endl;
//	=> 00278

#include <sstream>
#include <iomanip>
string itos_formatted(int ii, int n_digit)
{	
	std::stringstream ss;
	ss << std::setw(n_digit) << std::setfill('0') << ii;
	return ss.str();
}	

//------------ Capitialized a string --------------  
//	cout << make_string_lowercase("abcDEfGhijK") << endl;
//	=> ABCDEFGHIJK

#include <algorithm>
#include <string>
string make_string_uppercase(string input)
{
	transform(input.begin(), input.end(), input.begin(), ::toupper);
	return input;
}

//------------ Make a string lowercase --------------  
//	cout << make_string_lowercase("abcDEfGhijK") << endl;
//	=> abcdefghijk

#include <algorithm>
#include <string>
string make_string_lowercase(string input)
{
	transform(input.begin(), input.end(), input.begin(), ::tolower);
 	return input;
}

//------------ Check if a file is a image. -------------- 
//	cout << is_image_file("/home/someuser/flower.png") << endl;
//	=> true
//	cout << is_image_file("/home/someuser/poet.txt") << endl;
//	=> false

bool is_image_file(const string& filename)
{
	size_t pos = filename.rfind('.');
 	if (pos == string::npos) return false;
 	string ext = make_string_lowercase(filename.substr(pos + 1));
 	if (ext == "jpg" || ext == "jpeg" || ext == "gif" || ext == "bmp" || ext == "png" ||
 		ext == "pgm" || ext == "tif" || ext == "ppm" || ext == "tiff" || ext == "pnm")
 			return true;
 	return false;
 }


//------------ From a string extract the last number which occurs in that string. --------------
//	cout << get_last_integer_substring("my234st8_abc56.bmp") << endl;
//	=> 56
int get_last_integer_substring(const string& str_ori)
{
	string str = str_ori;
	// For atoi, the input string has to start with a digit, so lets search for the first digit
 	size_t i = str.length() - 1;
	int idx_first = -1, idx_last = -1;
	bool last_found = false;
	for (; i >= 0; i--)
	{
		if(last_found)
		{
			if(!isdigit(str[i])) break;
			idx_first = i;
		}
		else
		{
			if(isdigit(str[i]))
			{
				last_found = true;
				idx_last = i;
				idx_first = i;
			}
		}
	}
	// remove the first chars, which aren't digits
	str = str.substr(idx_first, idx_last - idx_first + 1);
	// convert the remaining text to an integer
	return stoi(str);
}

//------------ It is the counterpart of basename() in Python. --------------
//	cout << get_exa_exact_file_name_from_path("/home/someuser/somefolder/somefile.someext") << endl;
//	=> somefile
string get_exact_file_name_from_path(const string& str_path)
{
	string filename = str_path;
	// Remove directory if present.
	// Do this before extension removal incase directory has a period character.
	const size_t last_slash_idx = filename.find_last_of("\\/");
	if (std::string::npos != last_slash_idx) filename.erase(0, last_slash_idx + 1);
	// Remove extension if present.
	const size_t period_idx = filename.rfind('.');
	if (std::string::npos != period_idx) filename.erase(period_idx);
	return filename;
}

//------------ get_id_of_file_as_number --------------
//	cout << get_last_integer_substring("my_image_000023.bmp") << endl;
//	=> 23
int get_id_of_file_as_number(const string& fn)
{
	string fn_wo_ext = get_exact_file_name_from_path(fn);
	return get_last_integer_substring(fn_wo_ext);
}


//---------------------------------------------------------------------
//	vector<vector<string>> li_li_path;
//	vector<string> li_path_1({ "/home/dir1/001.bmp", "/home/dir1/002.bmp", "/home/dir1/003.bmp" });	
//	vector<string> li_path_2({ "/home/dir2/000.bmp", "/home/dir2/002.bmp", "/home/dir2/003.bmp" });	
//	vector<string> li_path_3({ "/home/dir3/002.bmp", "/home/dir3/003.bmp", "/home/dir3/004.bmp" });
//	li_li_path.push_back(li_path_1);	li_li_path.push_back(li_path_2);	li_li_path.push_back(li_path_3);
//	vector<vector<int>> li_li_id = get_list_of_list_of_ids_as_number(li_li_path);
//	for(int i1 = 0; i1 < li_li_id.size(); i1++) 
//	{ 
//		for(int i2 = 0; i2 < li_li_id[i1].size(); i2++) cout << li_li_id[i1][i2] << ", ";
//		cout << endl; 
//	}
//	=> 1, 2, 3 
//	=> 0, 2, 3 
//	=> 2, 3, 4 

vector< vector<int> > get_list_of_list_of_ids_as_number(const vector< vector<string> >& li_li_path)
{
	vector< vector<int> > li_li_id;
 	for(int iL = 0; iL < li_li_path.size(); iL++)
 	{
 		vector<int> li_id;
 		for(int iP = 0; iP < li_li_path[iL].size(); iP++) li_id.push_back(get_id_of_file_as_number(li_li_path[iL][iP]));
 		li_li_id.push_back(li_id);
 	}
 	return li_li_id;
}



//------------ get_list_of_image_path_under_this_directory --------------
//	vector<string> li_fn_img = li_get_list_of_image_path_under_this_directory("/home/someuser/somefolder/", 412, 414);
//	for(int i = 0; i < li_fn_img.size(); i++) cout << li_fn_img[i] << " ";
//	=> /home/someuser/somefolder/img412.bmp /home/someuser/somefolder/img413.png /home/someuser/somefolder/img414.jpg 
#include <experimental/filesystem>  // this requires to use "-lstdc++fs" as a library in Makefile.
namespace fs = std::experimental::filesystem;
vector<string> get_list_of_image_path_under_this_directory(const string& dir_img, int id_frm_start, int id_frm_last)
{
	vector<string> li;
	for(auto& p: fs::recursive_directory_iterator(dir_img))
	{
		string str_path = p.path().string();
		if(!is_image_file(str_path)) continue;
		if(id_frm_start >= 0 &&  get_id_of_file_as_number(str_path) < id_frm_start) continue;
		if(id_frm_last >= 0 &&  get_id_of_file_as_number(str_path) > id_frm_last) continue;
		li.push_back(str_path);
	}
	sort(li.begin(), li.end());
	return li;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//   math related
/////////////////////////////////////////////////////////////////////////////////////////////////

//------------ C++ function equivalent to Matlab's mod function --------------  
//	cout << matlab_mod_equivalent(-0.5, 10) << endl;
//	=> 9.5
#include <math.h>
double matlab_mod_equivalent(double x, double y)
{
  double result = fmod(x, y);
  return result >= 0 ? result : result + y;
}

//------------ Convert radians to degrees --------------  
//	cout << rad2deg(PI) << endl;
//	=> 180
#define PI 3.14159265
double rad2deg(double radian)
{
    return radian*180/PI;
}

//------------ Convert degrees to radians --------------  
//	cout << deg2rad(180) << endl;
//	=> 3.14159265
#define PI 3.14159265
double deg2rad(double degree)
{
    return degree*PI/180;
}

//------------ Calculate distance between two 2D points --------------  
//	cout << dist_two_points(0, 0, 2, 0) << endl;
//	=> 2
float dist_two_points(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2, dy = y1 - y2;
	return sqrt(dx * dx + dy * dy);
}

//------------ Calculate the area of triangle defined by three points --------------  
//	cout << calc_area_triangle(0, 0, 3, 0, 3, 2) << endl;
//	=> 3
float calc_area_triangle(float x0, float y0, float x1, float y1, float x2, float y2)
{
	return std::abs(x0 * (y1 - y2) + x1 * (y2 - y0) + x2 * (y0 - y1)) / 2.0;	
}	

//------------ Calculate the area of quadrangle defined by four points --------------  
//	cout << calc_area_quadrangle(0, 0, 4, 0, 3, 2, 0, 2) << endl;
//	=> 7
float calc_area_quadrangle(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3)
{
	float a012 = calc_area_triangle(x0, y0, x1, y1, x2, y2), a023 = calc_area_triangle(x0, y0, x2, y2, x3, y3);
	return a012 + a023;
}	

//------------ Calculate determinant of 2 by 2 matrix --------------
//	[a b]
//	[c d]
//	cout << Det(1, 2, 3, 4) << endl;
//	=> -2
double Det(double a, double b, double c, double d)
{
	return a*d - b*c;
}
 
//------------ Calculate intersection of two lines --------------
//	return true if found, false if not found or error
//	double ix = -1.0, iy = -1.0;
//	bool result = LineLineIntersect(4.0, 0.0, 6.0, 10.0, 0.0, 3.0, 10.0, 7.0, ix, iy);
//	cout << "result : " <<  result << ", " << ix << ", " << iy << endl;
// => result : 1, 5, 5
//	bool result = LineLineIntersect(0.0, 0.0, 1.0, 1.0, 1.0, 3.0, 3.0, 1.0, ix, iy);
//	cout << "result : " <<  result << ", " << ix << ", " << iy << endl;
// => result : 1, 2, 2
bool LineLineIntersect(double x1, double y1, //Line 1 start
	double x2, double y2, //Line 1 end
	double x3, double y3, //Line 2 start
	double x4, double y4, //Line 2 end
	double &ixOut, double &iyOut) //Output 
{
	double detL1 = Det(x1, y1, x2, y2);
	double detL2 = Det(x3, y3, x4, y4);
	double x1mx2 = x1 - x2;
	double x3mx4 = x3 - x4;
	double y1my2 = y1 - y2;
	double y3my4 = y3 - y4;
 
	double xnom = Det(detL1, x1mx2, detL2, x3mx4);
	double ynom = Det(detL1, y1my2, detL2, y3my4);
	double denom = Det(x1mx2, y1my2, x3mx4, y3my4);
	if(denom == 0.0)//Lines don't seem to cross
	{
		ixOut = NAN;
		iyOut = NAN;
		return false;
	} 
	ixOut = xnom / denom;	
	iyOut = ynom / denom;
	if(!isfinite(ixOut) || !isfinite(iyOut)) //Probably a numerical issue
		return false;
 	return true; //All OK
}

//------------ Compute where is a point wrt a line defined by two points --------------
//	If the point is on the line, the output is 0.
//	cout << which_side_this_point_is_on_of_line_with_two_points(2, 1, 0, 0, 4, 2) << endl;
//	=> 0
float which_side_this_point_is_on_of_line_with_two_points(float xx, float yy, float x1, float y1, float x2, float y2)
{
	//	line equation : (y1 - y2) * xx + (x2 - x1) * yt + (x1 - x2) * y1 + (y2 - y1) * x1 = 0
	return (y1 - y2) * xx + (x2 - x1) * yt + (x1 - x2) * y1 + (y2 - y1) * x1	
}	

//------------ Check if a point is on a line defined by two points --------------
//	cout << is_this_point_on_the_line_of_two_points(2, 1, 0, 0, 4, 2) << endl;
//	=> true
bool is_this_point_on_the_line_of_two_points(float xx, float yy, float x1, float y1, float x2, float y2)
{
	return std::abs(which_side_this_point_is_on_of_line_with_two_points(xx, yy, x1, y1, x2, y2)) < 0.000001	
}


//------------ Calculate angle between three points --------------
//	cout << calc_angle_deg_three_points(0, 2, 0, 0, 3, 0) << endl;
//	=> 90
#define PI 3.14159265
float calc_angle_deg_three_points(float ax, float ay, float bx, float by, float cx, float cy)
{
    float x_ab = bx - ax, y_ab = by - ay, x_cb = bx - cx, y_cb = by - cy;
    float dot = x_ab * x_cb + y_ab * y_cb; // dot product
    float cross = x_ab * y_cb - y_ab * x_cb); // cross product
    float rad = atan2(cross, dot);
    return rad * 180. / PI;
}

//------------ Calculate angle between two lines defined by end points --------------
//	cout << compute_angle_deg_between_two_lines(0, 0, 1, 1, 3, 1, 1, 3) << endl;
//	=> 90
double compute_angle_deg_between_two_lines(double x1a, double y1a, double x2a, double y2a, double x1b, double y1b, double x2b, double y2b)
{
	double x_int, y_int;
	bool are_they_not_parallel = LineLineIntersect(x1a, y1a, x2a, y2a, x1b, y1b, x2b, y2b, x_int, y_int);
	if(are_they_not_parallel) return 0;
	float side_1a = which_side_this_point_is_on_of_line_with_two_points(x1a, y1a, x1b, y1b, x2b, y2b),
		side_2a = which_side_this_point_is_on_of_line_with_two_points(x2a, y2a, x1b, y1b, x2b, y2b),
		side_1b = which_side_this_point_is_on_of_line_with_two_points(x1b, y1b, x1a, y1a, x2a, y2a),
		side_2b = which_side_this_point_is_on_of_line_with_two_points(x2b, y2b, x1a, y1a, x2a, y2a);
	bool is_a_crossing_b = side_1b * side_2b < 0, is_b_crossing_a = side_1a * side_2a < 0;
	float xa = x1a, ya = y1a, xb = x1b, yb = y1b;
	if(is_a_crossing_b)		
	{
		float d_1b_int = dist_two_points(x_int, y_int, x1b, y1b), d_2b_int = dist_two_points(x_int, y_int, x2b, y2b);
		if(d_1b_int > d_2b_int) 
		{
			xb = x1b;	yb = y1b;
		}
		else
		{
			xb = x2b;	yb = y2b;			
		}		
	}
	if(is_b_crossing_a)
	{
		float d_1a_int = dist_two_points(x_int, y_int, x1a, y1a), d_2a_int = dist_two_points(x_int, y_int, x2a, y2a);
		if(d_1a_int > d_2a_int) 
		{
			xa = x1a;	ya = y1a;
		}
		else
		{
			xa = x2a;	ya = y2a;			
		}		
	}
	return calc_angle_deg_three_points(xa, ya, x_int, y_int, xb, yb);	
} //end-ComputeAngleBetweenTwoLines




/////////////////////////////////////////////////////////////////////////////////////////////////
//   OpenCV related
/////////////////////////////////////////////////////////////////////////////////////////////////

//------------ pad_image  -------------- 
Mat pad_image(const Mat& im_ori, int pad_l, int pad_r, int pad_t, int pad_b)
{
	if(0 >= pad_l || 0 >= pad_r || 0 >= pad_t || 0 >= pad_b) 
	{	cout << "Padding is NOT applied due to inappropriate margins given" << endl; return im_ori;	}
	Mat im_padded = Mat::zeros(im_ori.rows + pad_t + pad_b, im_ori.cols + pad_l + pad_r, im_ori.type());
 	im_ori.copyTo(im_padded(Rect(pad_l, pad_t, im_ori.cols, im_ori.rows)));
	return im_padded;
}	


//------------ Generalized version of draw rectangle  -------------- 
//	'pt_ul' and 'pt_lr' are updated variables to determine 'pad_l', 'pad_r', 'pad_t' and 'pad_b'. 
//	Once 'pt_ul' and 'pt_lr' are computed, we can put 'NULL' and 'NULL' in their position.
//	When 'pt's are NULL and 'pad's are 0, it becomes just a regular draw_rectangle function.

Mat draw_rect_with_padding(Point *pt_ul, Point *pt_lr, const Mat& im_bgr, const Rect& roi, const Scalar& color_bgr, 
						   int thick, int pad_l, int pad_r, int pad_t, int pad_b)
{
	bool need_absolute_padding = 0 != pad_l + pad_r + pad_t + pad_b, 
		need_relative_padding = (-1 == pad_l) && (-1 == pad_r) && (-1 == pad_t) && (-1 == pad_b);
	bool need_padding = need_absolute_padding || need_relative_padding;
	if(need_relative_padding)
	{
		pad_l = MAX(0, -roi.x);	pad_r = roi.x + roi.width - im_bgr.cols;
		pad_t = MAX(0, -roi.y);	pad_r = roi.y + roi.height - im_bgr.rows;
	}		
	if(pt_ul)
 	{
 		if(roi.x < pt_ul->x) pt_ul->x = roi.x;
 		if(roi.y < pt_ul->y) pt_ul->y = roi.y;
 	}
	if(pt_lr)
 	{
 		if(roi.x + roi.width - 1 > pt_lr->x) pt_lr->x = roi.x + roi.width - 1;
 		if(roi.y + roi.height - 1 > pt_lr->y) pt_lr->y = roi.y + roi.height - 1;
 	}
 	//cout << "left : " << pt_ul.x << ", right : " << pt_lr.x - im_bgr.cols + 1 << ", up : " << pt_ul.y << ", down : " << pt_lr.y - im_bgr.rows + 1 << endl;
	Mat im_bgr_padded;
	if(need_padding)
 	{
		im_bgr_padded = pad_image(im_bgr, pad_l, pad_r, pad_t, pad_b);
		/*
		im_bgr_padded = Mat::zeros(im_bgr.rows + pad_t + pad_b, im_bgr.cols + pad_l + pad_r, im_bgr.type());
 		im_bgr.copyTo(im_bgr_padded(Rect(pad_l, pad_t, im_bgr.cols, im_bgr.rows)));
 		*/
		rectangle(im_bgr_padded, Rect(roi.x + pad_l, roi.y + pad_t, roi.width, roi.height), color_bgr, thick, 8);
 	}
 	else
 	{
		im_bgr_padded = im_bgr.clone();
 		rectangle(im_bgr_padded, roi, color_bgr, thick, 8);
	}
 	return im_bgr_padded;
}
	
	
	
//------------ Initialized VideoCapture from either of camera or video file --------------  
//	init_from_cam_or_video_or_directory("0") //	for camera
//	init_from_cam_or_video_or_directory("/home/folder/aaa.avi") //	for video file
//	init_from_cam_or_video_or_directory("/home/folder/%03.bmp") //	for image sequence /home/folder/001.bmp, /home/folder/002.bmp, etc.

#include "opencv2/highgui.hpp"
using namespace cv;
VideoCapture init_from_cam_or_video_or_directory(const std::string& strin)
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

//------------ Crop a image as a bunding box of a circle --------------  	
Mat crop_with_center_and_radius(const Mat& im, const Point2f& p_center, float radius)
{
	Point pt1(cvRound(p_center.x - radius), cvRound(p_center.y - radius)),
  		pt2(cvRound(p_center.x + radius), cvRound(p_center.y + radius));
  	int side = MIN(pt2.x - pt1.x + 1, pt2.y - pt1.y + 1);
  	Rect rect(pt1, Size(side, side));
  	return crop_image(im, rect);
}


//------------ Crop two images either horizontally or vetically	--------------  	
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


//------------ Rotatae an image by a given degrees either with resizing or not	--------------  
// Note that for binary case, thru "warpAffine" the image becomes blurred. So "threshold" function should be applied again.	
/* Usage
cv::Mat src = cv::imread("im.png");
double angle = -45;
cv::Point2f center((src.cols-1)/2.0, (src.rows-1)/2.0);
cv::Mat im_rotated = roatate_image_by_degree(src, center, angle, true, is_binary, 255);
*/
Mat rotate_image_by_degree(const Mat& im_src, const Point2f& p_center, double angle_deg, bool shall_resize, bool is_binary, int max_binary)
{
	Mat im_dst, mat_rot = getRotationMatrix2D(p_center, angle_deg, 1.0);
 	if(shall_resize)
 	{
 		Rect2f bbox = RotatedRect(Point2f(), im_src.size(), angle_deg).boundingRect2f();
 		mat_rot.at<double>(0, 2) += (bbox.width - im_src.cols) / 2.0;
 		mat_rot.at<double>(1, 2) += (bbox.height - im_src.rows) / 2.0;
		warpAffine(im_src, im_dst, mat_rot, bbox.size());
	}
 	else warpAffine(im_src, im_dst, mat_rot, im_src.size());
 	if(is_binary) threshold(im_dst, im_dst, 0, max_binary, THRESH_OTSU);
 	return im_dst;
}
		

//------------ Rotatae an image by a given degrees either with resizing or not	--------------  	
vector<Mat> make_set_of_rotated_square_images(const Mat& im, int resol_deg, bool is_binary, int max_binary)
{
	vector<Mat> li_im_rotated;
 	Point2f p_center((im.cols - 1.0) / 2.0, (im.rows - 1.0) / 2.0);
 	for(int rot_deg = 0; rot_deg < 360; rot_deg += resol_deg)
 	{
 		//cout << "rot_deg : " << rot_deg << endl;
		li_im_rotated.push_back(rotate_image_by_degree(im, p_center, rot_deg, false, is_binary, max_binary));
    }
	return li_im_rotated;
}

//------------ When a circle is in the image, compute the margin from which we can take the object inside circle.	--------------  	

int compute_circle_margin(const Mat& im_bin0255, float ratio_circle, float th_nz, float th_ratio, float              portion_center, int lrtb_0123, const string& str_side)
{
	int margin = 0, iP, wid = im_bin0255.cols, hei = im_bin0255.rows;
 	int x_center = 0.5 * (wid - 1), y_center = 0.5 * (hei - 1),
 		max_nz_search = MIN(cvRound(wid * ratio_circle), cvRound(hei * ratio_circle)),
 		w_half = 0.5 * portion_center * wid, h_half = 0.5 * portion_center * hei;
	int max_margin_search = MIN(MIN(x_center, y_center), max_nz_search * 3.0);
 	float nz_pre;
	
	Rect2f rect;
 	bool is_end_of_search = false, is_margin_detected = false, is_circle_detected = false;
 	if(0 == lrtb_0123 || 1 == lrtb_0123)
 	{
 		rect.y = y_center - h_half;
 		rect.width = 1;
 		rect.height = 2.0 * h_half;
 	}
 	else
 	{
		rect.x = x_center - w_half;
 		rect.width = 2.0 * w_half;
 		rect.height = 1;
 	}
 	for(iP = 0, nz_pre = 0; !is_end_of_search && !is_margin_detected; iP++)
 	{
 		if(0 == lrtb_0123) rect.x = iP;
 		else if(1 == lrtb_0123) rect.x = wid - 1 - iP;
 		else if(2 == lrtb_0123) rect.y = iP;
	
		else rect.y = hei - 1 - iP;
		float nz_cur = float(sum(im_bin0255(rect))[0] / 255);
 		if(!is_circle_detected)
 		{
 			if(th_nz < nz_cur)
 			{
 				nz_pre = nz_cur;
 				is_circle_detected = true;
 			}
			else if(iP > max_nz_search)
			{
				is_end_of_search = true;
			}
		}
		else
		{
			float r_nz = nz_cur / nz_pre;
			if(r_nz < th_ratio)
			{
				margin = iP;
				is_margin_detected = true;
			}
			if(iP > max_margin_search)
			{
				margin = iP;
				is_end_of_search = true;
			}
           	nz_pre = nz_cur;
		}
	}
	return margin;
}
				
//------------ When a circle is in the image, get the image of obeject inside the circle.	--------------  
Mat image_inside_circle(const Mat& im_bin0255, float portion_center, float th_ratio, float ratio_circle, int side)
{
	Mat im_bin0255_inside_circle;
	int wid = im_bin0255.cols, hei = im_bin0255.rows;
	int x_center = 0.5 * (wid - 1), y_center = 0.5 * (hei - 1),
		thick_circle = MIN(cvRound(wid * ratio_circle), cvRound(hei * ratio_circle)),	
		margin_l = 0, margin_r = 0, margin_t = 0, margin_b = 0, w_half = 0.5 * portion_center * wid, h_half = 0.5 * portion_center * hei;
	int iX, iY;
	float nz_pre, th_nz;
	bool is_circle_detected;
	//show_image("im_bin0255_w_circle", im_bin0255);
	margin_l = compute_circle_margin(im_bin0255, ratio_circle, h_half, th_ratio, portion_center, 0, "left");
	margin_r = compute_circle_margin(im_bin0255, ratio_circle, h_half, th_ratio, portion_center, 1, "right");
	margin_t = compute_circle_margin(im_bin0255, ratio_circle, w_half, th_ratio, portion_center, 2, "top");
	margin_b = compute_circle_margin(im_bin0255, ratio_circle, w_half, th_ratio, portion_center, 3, "bottom");
	Rect rect(margin_l, margin_t, im_bin0255.cols - margin_r - margin_l, im_bin0255.rows - margin_b - margin_t);
	if(0 == side)
	{
		im_bin0255(rect).copyTo(im_bin0255_inside_circle);
	}
	else
	{
		if(0 > side) side = MIN(wid - margin_l - margin_r, hei - margin_t - margin_b);
		im_bin0255_inside_circle = resize_image(im_bin0255(rect), Size(side, side), 0, 0,                            "im_bin0255_inside_circle");
		//show_image("im_bin0255_inside_circle_b4", im_bin0255_inside_circle);
		threshold(im_bin0255_inside_circle, im_bin0255_inside_circle, 0, 255, THRESH_OTSU);
		//show_image("im_bin0255_inside_circle_after", im_bin0255_inside_circle); //waitKey();  //exit(0);
	}	
	Point2f p_center(0.5 * (im_bin0255_inside_circle.cols - 1), 0.5 * (im_bin0255_inside_circle.rows - 1));
	Mat im_bin0255_circle = Mat::zeros(im_bin0255_inside_circle.size(), im_bin0255_inside_circle.type());
	float radius = MIN(im_bin0255_inside_circle.rows * 0.5 - 2, im_bin0255_inside_circle.cols * 0.5 - 2);
	circle(im_bin0255_circle, p_center, radius, Scalar(255, 255, 255), -1);
	Mat im_bin0255_inside_circle_wo_circle;
	im_bin0255_inside_circle.copyTo(im_bin0255_inside_circle_wo_circle, im_bin0255_circle);
	//show_image("im_bin0255_inside_circle", im_bin0255_inside_circle);
	//show_image("im_bin0255_inside_circle_wo_circle", im_bin0255_inside_circle_wo_circle);
	//waitKey();  //exit(0);
	return im_bin0255_inside_circle_wo_circle;
}


//-----------------------------------------------------------------------------------------------------  
//	vector<int> li_int({4, 1, 3, 2});
//	vector<string> li_string({"aa", "bb", "cc", "dd"});
//	sort_two_seqs_as_first_seq_sorted(li_int, li_string, true);
//	=> li_int : 1, 2, 3, 4 and li_string : "bb", "dd", "cc", "aa" 
//	sort_two_seqs_as_first_seq_sorted(li_int, li_string, false);
//	=> li_int : 4, 3, 2, 1 and li_string : "aa", "cc", "dd", "bb"  
	
void sort_two_seqs_as_first_seq_sorted(vector<int>& li_int, vector<string>& li_string, bool is_descending)
{
	auto p = sort_permutation(li_int, [](int const& a, int const& b) {return is_descending ? a < b : a > b;});
	apply_permutation_in_place(li_int, p);
	apply_permutation_in_place(li_string, p);
}

//-----------------------------------------------------------------------------------------------------  
//	vector<int> li_idx({ 1, 3, 2 });	
//	vector<vector<int> li_li_id;
//	vector<int> li_id_1({ 3, 5, 7, 9, 11 });	
//	vector<int> li_id_1({ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });	
//	vector<int> li_id_3({ 1, 4, 5, 8, 9, 11, 13 });
//	li_li_id.push_back(li_id_1);	li_li_id.push_back(li_id_2);	li_li_id.push_back(li_id_3);
//	get_next_index(li_idx, li_li_id);
//	=> li_idx becomes from { 1, 3, 2 } to { 3, 7, 4 } which are indices of the common element "9"
//	get_next_index(li_idx, li_li_id);
//	=> li_idx becomes from { 3, 7, 4 } to { 4, 9, 5 } which are index of the common element "11"

bool get_next_index(vector<int>& li_idx, const vector<vector<int>>& li_li_id)
{
	bool is_the_end = false;
	int is_max = -1, id_max = -1000000, n_seq = li_idx.size();
	while(!is_the_end)
	{
		int id_min = 1000000;
		for(int iS = 0; iS < n_seq; iS++)
		{
			if(iS == is_max) continue;
			int idx_cur = li_idx[iS] + 1, n_elem = li_li_id[iS].size();
			if(idx_cur == n_elem)
			{
				is_the_end = true;  break;
			}
			li_idx[iS] = idx_cur;
			int id_cur = li_li_id[iS][idx_cur];
			if(id_cur < id_min) id_min = id_cur;
			if(id_cur > id_max)
			{
				id_max = id_cur;
				is_max = iS;
			}
		}
		if(is_the_end) break;
		cout << "id_max : " << id_max << ", id_min : " << id_min << endl;
		if(id_max == id_min) break;
	}
	cout << "is_the_end : " << is_the_end << endl;  //exit(0);
	return !is_the_end;
}
			
			
//-----------------------------------------------------------------------------------------------------  
//	vector<vector<string>> li_li_path;
//	vector<string> li_path_1({ "/home/dir1/001.bmp", "/home/dir1/002.bmp", "/home/dir1/003.bmp" });	
//	vector<string> li_path_2({ "/home/dir2/000.bmp", "/home/dir2/002.bmp", "/home/dir2/003.bmp" });	
//	vector<string> li_path_3({ "/home/dir3/002.bmp", "/home/dir3/003.bmp", "/home/dir3/004.bmp" });
//	li_li_path.push_back(li_path_1);	li_li_path.push_back(li_path_2);	li_li_path.push_back(li_path_3);
//	concatenate_images_from_seqeunces_into_video_or_sequence(li_li_path, -1, true, "/home/dir4/");
//	=> The video of concatenated images are saved at : /home/dir4/output.avi
//	=> The first frame of the video is composed of "/home/dir1/002.bmp", "/home/dir2/002.bmp" and "/home/dir2/002.bmp".   
//	=> The second(which is the last) frame of the video is composed of "/home/dir1/003.bmp", "/home/dir2/003.bmp" and "/home/dir3/003.bmp".   

void concatenate_images_from_seqeunces_into_video_or_sequence(vector< vector<string> >& li_li_path, 
							      int hori_minus_vert_plus, bool save_as_video, const string& dir_save)
{
	vector<vector<int> > li_li_id = get_list_of_list_of_ids_as_number(li_li_path);
	for(int iS = 0; iS < li_li_id.size(); iS++) sort_two_seqs_as_first_seq_sorted(li_li_id[iS], li_li_path[iS], true);
	int iF = 0, n_seq = li_li_path.size(), cv_read_flag =
		is_all_seq_gray(li_li_path) ? CV_LOAD_IMAGE_GRAYSCALE : CV_LOAD_IMAGE_COLOR;
	vector<int> li_idx(n_seq, -1);
	VideoWriter vw;
	mkdir_if_not_exist(dir_save.c_str());
	string path_vid = python_join_equivalent(dir_save, "output.avi");
     	while(get_next_index(li_idx, li_li_id))
	{
		int idx = li_idx[0];
		string fn = li_li_path[0][idx];
		Mat im_cur = imread(fn, cv_read_flag);
		for(int iS = 1; iS < n_seq; iS++)
		{
			idx = li_idx[iS];
			fn = li_li_path[iS][idx];
			im_cur = concatenate_images(im_cur, imread(fn, cv_read_flag), hori_minus_vert_plus);
		}
         	if(save_as_video) vw = write_one_frame_to_video(vw, im_cur, 0 == iF, path_vid, 30, 1000);
		else save_one_image_under_directory(im_cur, dir_save, "comparision_");
		iF++;
	}
	if(save_as_video) { cout << "concatenated video has just saved at : " << path_vid << endl;  vw.release(); }
}

//-----------------------------------------------------------------------------------------------------  
//	Mat im = imread("aaa.bmp");
//	save_one_image_under_directory(im, "/home/folder", "bbb.bmp");
//	=> An image is saved at /home/folder/bbb.bmp".

void save_one_image_under_directory(const Mat& im, const string& dir_save, const string& fn_img)
{
	mkdir_if_not_exist(dir_save.c_str());
	string path_res = python_join_equivalent(dir_save, fn_img);
	imwrite(path_res, im);
}


//-----------------------------------------------------------------------------------------------------  
//	VideoWriter vw = init_video_writer("/home/folder/aaa.avi", 30, Size(640, 480));

VideoWriter init_video_writer(const string& fn_path, double fps, const Size& saiz)
{
	VideoWriter writer;
	writer.open(fn_path, VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, saiz, true);
	if (!writer.isOpened())
	{
		cout << "동영상을 저장하기 위한 초기화 작업 중 에러 발생" << endl;	exit(0);
	}
	return writer;
}



//-----------------------------------------------------------------------------------------------------  
//	VideoWriter vw;
//	Mat im = imread("/home/folder/bbb.bmp");
//	vw = write_one_frame_to_video(vw, im, true, "/home/folder/aaa.avi");
//	im = imread("/home/folder/ccc.bmp");
//	vw = write_one_frame_to_video(vw, im, false, "/home/folder/aaa.avi");
//	vw.realese();
//	=> A video is saved at "/home/folder/aaa.avi" whose first frame is "/home/folder/bbb.bmp" and the second (last) frame is "/home/folder/ccc.bmp".

VideoWriter write_one_frame_to_video(VideoWriter& vw, Mat& im, bool is_first_frame, const string& path_vid,          double fps, int max_side)
{
	if(max_side > 0) im = resize_image(im, 0, 0, 0, 0, max_side);
	if(is_first_frame) vw = init_video_writer(path_vid, fps, im.size());
	vw.write(im);
	return vw;
}

//----------------------------------------------------------------------------------------------------- 
//	cout << compute_size_smaller_than(Size(1920, 720), Size(640, 480)) << endl;
//	=> [960 x 360]	
//	cout << compute_size_smaller_than(Size(1280, 960), Size(640, 480)) << endl;
//	=> [640 x 480]
//	cout << compute_size_smaller_than(Size(960, 720), Size(640, 480)) << endl;
//	=> [480 x 360]
//	cout << compute_size_smaller_than(Size(640, 480), Size(640, 480)) << endl;
//	=> [640 x 480]
Size compute_size_smaller_than(const Size& size_src, const Size& size_tgt)
{
    Size size_smaller_than(size_src);
    if((size_src.width > size_tgt.width && size_src.height > size_tgt.height) || 
        (size_src.width < size_tgt.width && size_src.height < size_tgt.height))
    {   
        bool shall_shrink = size_src.width > size_tgt.width;
        for(int iS = 2; iS < 10000; iS++)
        {
            if(shall_shrink)
            {
                if(is_first_a_factor_of_second(iS, size_src.width) && is_first_a_factor_of_second(iS, size_src.height))
                {
                    int wid = size_src.width / iS, hei = size_src.height / iS;
                    if(wid <= size_tgt.width || hei <= size_tgt.height)
                    {
                        size_smaller_than.width = wid;  size_smaller_than.height = hei;
                        break;
                    }
                }       
            }
            else
            {
                int wid = size_src.width * iS,  hei = size_src.height * iS;
                if(wid >= size_tgt.width && hei >= size_tgt.height)
                {
                    size_smaller_than.width = size_src.width * (iS - 1);
                    size_smaller_than.height = size_src.height * (iS - 1);
                    break;
                }
                else if(wid >= size_tgt.width || hei >= size_tgt.height)
                {
                    size_smaller_than.width = wid;  size_smaller_than.height = hei;
                    break;
                }
            }
        }
    
    }
    return size_smaller_than;
}


//-----------------------------------------------------------------------------------------------------  
//	Mat im = imread("/home/folder/im_1280_720.bmp");
//	=> The size of im is (1280, 720)
//	Mat im_resized_1 = resize_image(im, 640, 480, 0, 0, 0);
//	=> The size of im_resized_1 is (640, 480)
//	Mat im_resized_2 = resize_image(im, 0, 0, 0.5, 0.25, 0);
//	=> The size of im_resized_2 is (640, 180)
//	Mat im_resized_3 = resize_image(im, 0, 0, 0, 0, 320);
//	=> The size of im_resized_3 is (320, 180)
Mat resize_image(const Mat& im_ori, int w_new, int h_new, float fx, float fy, int max_side)
{
	Mat im_resized;
	int max_wh = MAX(im_ori.cols, im_ori.rows);
	if(w_new > 0 && h_new > 0) resize(im_ori, im_resized, Size(w_new, h_new), 0, 0);
	else if(fx > 0 && fy > 0) resize(im_ori, im_resized, Size(0, 0), fx, fy);
	else if(max_side < max_wh)
	{
		float ratio = float(max_side) / float(max_wh);
		resize(im_ori, im_resized, Size(0, 0), ratio, ratio);
	}
	else if(max_side > 0)
	{
		im_resized = im_ori.clone();
		cout << "Resize is NOT applied since does NOT have to !!" << endl;
	}
	else { cout << "Can NOT resize image since NO guide is given !!" << endl; exit(0); };
	return im_resized;
}


//-----------------------------------------------------------------------------------------------------  
//	vector<vector<string>> li_li_path;
//	vector<string> li_path_1({ "/home/dir1/001.bmp", "/home/dir1/002.bmp", "/home/dir1/003.bmp" });	
//	vector<string> li_path_2({ "/home/dir2/000.bmp", "/home/dir2/002.bmp", "/home/dir2/003.bmp" });	
//	vector<string> li_path_3({ "/home/dir3/002.bmp", "/home/dir3/003.bmp", "/home/dir3/004.bmp" });
//	li_li_path.push_back(li_path_1);	li_li_path.push_back(li_path_2);	li_li_path.push_back(li_path_3);
//	if(are_all_seqs_gray(li_li_path))
//	{
//		....		

bool are_all_seqs_gray(const vector<vector<string> >& li_li_path)
{
	bool is_all_gray = true;
 	for(int iL = 0; iL < li_li_path.size(); iL++)
 	{
 		Mat im = imread(li_li_path[iL][0], CV_LOAD_IMAGE_UNCHANGED);
 		if(im.channels() > 1) { is_all_gray = false; break; }
 	}
	return is_all_gray;
}

	
		

