//------------ c++ counterpart of python function "join" --------------  
// make시 -std=c++11 또는 -std=gnu++11 옵션을 주어야 함.
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
	return 2 >= strin.size() && in_only_number(strin) 	
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
//   OpenCV related
/////////////////////////////////////////////////////////////////////////////////////////////////


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
		im_bgr_padded = Mat::zeros(im_bgr.rows + pad_t + pad_b, im_bgr.cols + pad_l + pad_r, im_bgr.type());
 		im_bgr.copyTo(im_bgr_padded(Rect(pad_l, pad_t, im_bgr.cols, im_bgr.rows)));
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
	
		

