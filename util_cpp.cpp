//------------ print something with indent --------------  
//	std::stringstream ss;
//	ss << "I am " << 5 << " years old.";
//	cout_indented(2, ss.str());
//	=>   I am 5 years old.
//	cout_indented(2, "I am " + std::to_string(5) + " years old.");
//	=>   I am 5 years old.


void cout_indented(int n_space, const string& str)
{
    if(n_space >= 0) std::cout << std::string(n_space * 2, ' ') << str << std::endl;
}


std::vector<std::string> get_file_paths_of_given_extension_under_this_directory( const std::string& str_root, const  std::string& ext )
{
    boost::filesystem::path root( str_root );
    std::vector<std::string> paths;

    if ( boost::filesystem::exists( root ) && boost::filesystem::is_directory( root ) )
    {
        for ( auto const& entry : boost::filesystem::recursive_directory_iterator( root ) )
        {
            if ( boost::filesystem::is_regular_file( entry ) && entry.path().extension() == ext )
            {
                paths.emplace_back( entry.path().string() );
            }
        }
    }
    return paths;
}


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

/*
#include <time.h>
struct timespec t_begin, t_end;
clock_gettime(CLOCK_MONOTONIC, &t_begin);
//	do something
clock_gettime(CLOCK_MONOTONIC, &t_end);
double lap_ms = lap_time(t_begin, t_end, true);
*/
double lap_time(struct timespec& t_begin, struct timespec& t_end, bool is_millisecond)
{
    double lap_sec = (t_end.tv_sec - t_begin.tv_sec) + (t_end.tv_nsec - t_begin.tv_nsec) / 1000000000.0;
    return is_millisecond ? 1000.0 * lap_sec : lap_sec;
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
bool is_this_directory_existing(const char *direc)
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

//------------ Check if the given file is the existing one --------------  
#include <sys/stat.h> 
bool is_this_file_existing(const char *fileName)	//	takes 0.134 sec
{
	struct stat buffer;   
  	return (stat (fileName, &buffer) == 0); 
}
//bool is_this_file_existing(const char *fileName)	//	takes 0.485 sec
//{
//    std::ifstream infile(fileName);
//    return infile.good();
//}
bool is_this_file_existing(const std::string& fileName)
{
	return is_this_file_existing(fileName.c_str());	
}


//------------ Check if the current process is running inside a docker --------------  
bool is_inside_docker()
{
	return is_this_file_existing("/.dockerenv");
}



//------------ Create a directory if it does not exist --------------  
#include <sys/stat.h>
#include <stdio.h>
/*
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
*/

#include <string.h>
#include <limits.h>     /* PATH_MAX */
#include <sys/stat.h>   /* mkdir(2) */
#include <errno.h>

int mkdir_p(const char *path)
{
    /* Adapted from http://stackoverflow.com/a/2336245/119527 */
    const size_t len = strlen(path);
    char _path[PATH_MAX];
    char *p; 

    errno = 0;

    /* Copy string so its mutable */
    if (len > sizeof(_path)-1) {
        errno = ENAMETOOLONG;
        return -1; 
    }   
    strcpy(_path, path);

    /* Iterate the string */
    for (p = _path + 1; *p; p++) {
        if (*p == '/') {
            /* Temporarily truncate */
            *p = '\0';

            if (mkdir(_path, S_IRWXU) != 0) {
                if (errno != EEXIST)
                    return -1; 
            }

            *p = '/';
        }
    }   

    if (mkdir(_path, S_IRWXU) != 0) {
        if (errno != EEXIST)
            return -1; 
    }   

    return 0;
}


int mkdirs(const char *path, mode_t mode = 0733)	// another candidate : 0766  
{ 
	char tmp_path[2048]; 
	const char *tmp = path; 
	int len = 0, ret; 
	if(path == NULL || strlen(path) >= 2048) return -1; 
	while((tmp = strchr(tmp, '/')) != NULL) 
	{ 
		len = tmp - path; 
		tmp++; 
		if(len == 0) continue; 
		strncpy(tmp_path, path, len); 
		tmp_path[len] = 0x00; 
		if((ret = mkdir(tmp_path, mode)) == -1) 
		{ 
			if(errno != EEXIST) return -1; 
		} 
	} 
	return mkdir(path, mode); 
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
//	cout << is_only_number("+1234");
//	=> false
//	cout << is_only_number("-0.1234");
//	=> true
//	cout << is_only_number(".1234");
//	=> true
bool is_only_number(const std::string& s)
{
	bool is_number = true;
	int n_pure_num = 0, n_dot = 0;
	if(s.empty()) is_number = false;
	else
	{
		for(auto it = s.begin(); it != s.end(); it++)
		{
			//std::cout << "*it : " << *it << std::endl;
			if(s.begin() == it)
			{
				if(!(std::isdigit(*it) || '-' == *it || '.' == *it)) {    is_number = false;  break; }
				if(std::isdigit(*it)) n_pure_num++;
				else
				{
					if('.' == *it) n_dot++;
				}
			}
			else
			{
				if('.' == *it) {
					if(++n_dot > 1) { is_number = false;  break; }
				}
				else
				{
					if(std::isdigit(*it)) n_pure_num++;
					else { is_number = false;  break; }
				}
			}
		}
	}
	if(0 == n_pure_num) is_number = false;
	std::cout << "s : " << s << ", is_number : " << is_number << std::endl;
	//exit(0);
	return is_number;
}


//------------ Check if the string is camera index --------------  
//	cout << is_this_camera_index("04");
//	=> true
bool is_this_camera_index(const std::string& strin)
{
	return 2 >= strin.size() && is_only_number(strin);	
}


bool is_this_string_empty(const string& strin)
{
	return strin.empty();
}

//------------ Check parse string by delimiter into a vector of strings -------------- 
//	string str = "10 ,abc ;234 %:3rf >"
//	string const delims{ " ,;%:>" };
//	vector<string> li_str = split_string_by_delimiter(str, delims);
//	for(int i = 0; i < li_str.size(); i++) cout << li_str[i] << " ";
//	=> 10 abc 234 3rf
using namespace std;
vector<string> split_string_by_delimiter(const string& strin, string const& delims)
{
	//std::string const delims{ " .,:;!?" };
	std::vector<std::string> li_str;
	size_t beg, pos = 0;
	while ((beg = strin.find_first_not_of(delims, pos)) != std::string::npos)
	{
		pos = strin.find_first_of(delims, beg + 1);
		li_str.push_back(strin.substr(beg, pos - beg));
		std::cout << li_str.back() << std::endl;
	}
	return li_str;
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




//------------ get_list_of_image_path_under_this_directory --------------
//	vector<string> li_fn_img = li_get_list_of_image_path_under_this_directory("/home/someuser/somefolder/", 412, 414);
//	for(int i = 0; i < li_fn_img.size(); i++) cout << li_fn_img[i] << " ";
//	=> /home/someuser/somefolder/img412.bmp /home/someuser/somefolder/img413.png /home/someuser/somefolder/img414.jpg 
#include <experimental/filesystem>  // this requires to use "-lstdc++fs" as a library in Makefile.
namespace fs = std::experimental::filesystem;
vector<string> get_list_of_image_path_under_this_directory(const string& dir_img, int id_frm_start, int id_frm_last)
{
    //cout << "dir_img : " << dir_img << endl;    //exit(0);
	vector<string> li;
	for(auto& p: fs::recursive_directory_iterator(dir_img))
	{
		string str_path = p.path().string();
        //cout << "id_frm_start : " << id_frm_start << endl; 
        //cout << "id_frm_last : " << id_frm_last << endl;    //exit(0);
		if(!is_image_file(str_path)) continue;
		int aidi = get_id_of_file_as_number(str_path);// < id_frm_start) continue;
        //cout << "aidi : " << aidi << endl;    //exit(0);
		if(id_frm_start >= 0 &&  aidi < id_frm_start) 
        {
            continue;
        }     
		if(id_frm_last >= 0 && id_frm_last >= id_frm_start &&  aidi > id_frm_last)
        {
            continue;
        }     
		li.push_back(str_path);
	}
	sort(li.begin(), li.end());
    //cout << "li.size() : " << li.size() << endl;    exit(0);
	return li;
}


vector<vector<string> > file_2_list_of_list_of_string(const string& fn)
{
    vector<vector<string> > li_li_str;
    std::ifstream input(fn);
    if(input.is_open())
    {
        std::string line, delimiter = " =[],;";
        std::string const delims{ delimiter };
        while(std::getline(input, line))
        {
            if(line.empty() || 0 == line.rfind("#", 0))
            {
                continue;
            }
            vector<string> li_str = split_string_by_delimiter(line, delims);
            li_li_str.push_back(li_str);
        }
        input.close();
    }
    else
    {
        cout << "Can NOT open the text file : " << fn << endl;   exit(0);
    }
    return li_li_str;
}


Mat string_list_2_homogeneous_matrix( const vector<string>& li_str_pose )
{
    double  x_meter, y_meter, z_meter;
    Mat vec_rot_aa;
    x_meter = stof( li_str_pose[0] );
    y_meter = stof( li_str_pose[1] );
    z_meter = stof( li_str_pose[2] );
    double  aax = stof( li_str_pose[3] ),
    aay = stof( li_str_pose[4] ),
    aaz = stof( li_str_pose[5] );
    vec_rot_aa = ( Mat_<double>( 3, 1 ) << aax, aay, aaz );
    Mat vec_tra = ( Mat_<double>( 3, 1 ) << x_meter, y_meter, z_meter );
    Mat mat_bme = combine_rotation_translation_into_homogeneous_matrix( vec_rot_aa, vec_tra );
    return mat_bme;
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


//---------------------------------------------------------------------
//	std::string str_float = to_string_with_precision<float>(123.456789, 4);
//	cout << "str_float : " << str_float << endl;
//	=> str_float : 123.4567

#include <sstream>
template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
//   math related
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


//------------ Check if the first integer is one of factors of the second integer --------------  
//	cout << is_first_a_factor_of_second(3, 15) << endl;
//	=> true
//	cout << is_first_a_factor_of_second(2, 15) << endl;
//	=> false
bool is_first_a_factor_of_second(int first, int second)
{
	return 0 == compute_remainder( second, first );
}



float rotation_degree_of_euler_degrees(Vec3f& euler_deg)
{
    Mat r_vec_rad, r_mat = eulerDegrees2RotationMatrix(euler_deg);
    Rodrigues(r_mat, r_vec_rad);
    double rad_rot = norm(r_vec_rad);
    return rad_2_deg_2(rad_rot);
}

Vec3f rotationMatrix2EulerRadians(Mat& r_mat)
{
    return rotationMatrixToEulerAngles(r_mat);
}

Vec3f rotationMatrix2EulerDegrees(Mat& r_mat)
{
    Vec3f rad_euler = rotationMatrix2EulerRadians(r_mat);
    return Vec3f(   rad_2_deg_2( rad_euler[0] ),
                    rad_2_deg_2( rad_euler[1] ),
                    rad_2_deg_2( rad_euler[2] ) );
}

Mat eulerRadians2RotationMatrix(Vec3f& euler_rad)
{
    return eulerAnglesToRotationMatrix(euler_rad);
}

Mat eulerDegrees2RotationMatrix(Vec3f& euler_deg)
{
    Vec3f euler_rad (   deg_2_rad(euler_deg[0]),
                        deg_2_rad(euler_deg[1]),
                        deg_2_rad(euler_deg[2]) );
    return eulerAnglesToRotationMatrix(euler_rad);
}

Mat combine_euler_degree_translation_into_homogeneous_matrix(Vec3f& euler_deg, const Mat& t_vec)
{
    Mat r_mat = eulerDegrees2RotationMatrix(euler_deg);
    return combine_rotation_translation_into_homogeneous_matrix(r_mat, t_vec);
}


float normal_pdf(float x, float m, float s)
{
    static const float inv_sqrt_2pi = 0.3989422804014327;
    float a = (x - m) / s;
    return inv_sqrt_2pi / s * std::exp(-0.5f * a * a);
}


bool closeEnough(const float& a, const float& b, const float& epsilon = std::numeric_limits<float>::epsilon())
{
    return (epsilon > std::abs(a - b));
}

float3 eulerAngles(const float3x3& R) {

    //check for gimbal lock
    if (closeEnough(R[0][2], -1.0f))
    {
        float x = 0; //gimbal lock, value of x doesn't matter
        float y = PI / 2;
        float z = x + atan2(R[1][0], R[2][0]);
        return { x, y, z };
    }
    else if (closeEnough(R[0][2], 1.0f))
    {
        float x = 0;
        float y = -PI / 2;
        float z = -x + atan2(-R[1][0], -R[2][0]);                                                                            return { x, y, z };
    }
    else
    { //two solutions exist
        float x1 = -asin(R[0][2]);
        float x2 = PI - x1;
        float y1 = atan2(R[1][2] / cos(x1), R[2][2] / cos(x1));                                                              float y2 = atan2(R[1][2] / cos(x2), R[2][2] / cos(x2));                                                              float z1 = atan2(R[0][1] / cos(x1), R[0][0] / cos(x1));                                                              float z2 = atan2(R[0][1] / cos(x2), R[0][0] / cos(x2));
        cout << "two solutions : " << endl;
        cout << "1. : (" << rad2deg(x1) << ", " << rad2deg(y1) << ", " << rad2deg(z1) << ")" << endl;
        cout << "2. : (" << rad2deg(x2) << ", " << rad2deg(y2) << ", " << rad2deg(z2) << ")" << endl;                        //choose one solution to return
        //for example the "shortest" rotation
        if ((std::abs(x1) + std::abs(y1) + std::abs(z1)) <= (std::abs(x2) + std::abs(y2) + std::abs(z2)))
        {
            return { x1, y1, z1 };
        }
        else
        {
            return { x2, y2, z2 };
        }
    }
}

//	cout << IsExp2(4) << endl;
//	=> 1
//	cout << IsExp2(3) << endl;
//	=> 0

static bool IsExp2(unsigned int value)
{
    return (value > 0 && (value & (value - 1)) == 0);
}


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
    return degree * PI / 180;
}


//------------ Generate a list of possible rotation angles(degree) larger than 'min_deg' --------------
//	vector<float> li_deg = compute_list_of_possible_rotation_degree(70);
//	for(int iD = 0; iD < li_deg.size(); iD++) cout << li_deg[iD] << ", "; cout << endl;
//	=> 180, 120, 90, 72
vector<float> compute_list_of_possible_rotation_degree(float min_deg)
{
    vector<float> li_deg_possible;
    int divider = 1;
    float deg = 360.0 / float(++divider);
    while(deg > min_deg)
    {
        li_deg_possible.push_back(deg);
        deg = 360.0 / float(++divider);
    }
    sort(li_deg_possible.begin(), li_deg_possible.end());
    return li_deg_possible;
}

vector<Scalar> generate_random_color_list(unsigned int n_color)
{
    vector<Scalar> li_color;
    li_color.push_back(Scalar(255, 0, 0));
    li_color.push_back(Scalar(0, 255, 0));
    li_color.push_back(Scalar(0, 0, 255));
    if(li_color.size() < n_color)
    {
        li_color.push_back(Scalar(255, 255, 0));
        li_color.push_back(Scalar(0, 255, 255));
        li_color.push_back(Scalar(255, 0, 255));
        if(li_color.size() < n_color)
        {
            li_color.push_back(Scalar(255, 128, 0));
            li_color.push_back(Scalar(0, 255, 128));
            li_color.push_back(Scalar(128, 0, 255));
            if(li_color.size() < n_color)
            {
                li_color.push_back(Scalar(128, 255, 0));
                li_color.push_back(Scalar(0, 128, 255));
                li_color.push_back(Scalar(255, 0, 128));
                if(li_color.size() < n_color)
                {
                    li_color.push_back(Scalar(128, 128, 0));
                    li_color.push_back(Scalar(0, 128, 128));
                    li_color.push_back(Scalar(128, 0, 128));
                    
                    while(li_color.size() < n_color)
                    {
                        li_color.push_back(Scalar(
                            random_number_in_between(100, 255),
                            random_number_in_between(100, 255),
                            random_number_in_between(100, 255)));
                    }
                }
            }
        }
    }
    return li_color;
}

//------------ Normalize to [-180,180) --------------
#define     M_PI   3.1415926535897932384626433832795
#define     M_2PI  M_PI * 2.0
inline double constrainAngle(double ang_rad)
{
    ang_rad = fmod(ang_rad + M_PI, M_2PI);
    if(ang_rad < 0) ang_rad += M_2PI;
    return ang_rad - M_PI;
}
                   

//------------ convert to [-360, 360] --------------                    
inline double angleConv(double ang_rad)
{ 
    return fmod(constrainAngle(ang_rad), M_2PI);    
}

inline double angleDiff(double a_rad, double b_rad)
{
    double dif_rad = fmod(b_rad - a_rad + M_PI, M_2PI);
    if (dif_rad < 0) dif_rad += M_2PI;
    return dif_rad - M_PI;
}

inline double unwrap(double ang_rad_pre, double ang_rad_new)
{
    return ang_rad_pre - angleDiff(ang_rad_new, angleConv(ang_rad_pre));
}


Mat eulerAnglesToRotationMatrix( const Vec3f& angle, bool from_degree )
{
    Vec3f theta = angle;
    if(from_degree)
    {
        theta[0] = deg2rad(angle[0]);   theta[1] = deg2rad(angle[1]);   theta[2] = deg2rad(angle[2]);
    }
    // Calculate rotation about x axis
    Mat R_x = ( Mat_<double>( 3, 3 ) <<
                1,       0,              0,
                0,       cos( theta[0] ),   -sin( theta[0] ),
                0,       sin( theta[0] ),   cos( theta[0] )
              );
    // Calculate rotation about y axis
    Mat R_y = ( Mat_<double>( 3, 3 ) <<
                cos( theta[1] ),    0,      sin( theta[1] ),
                0,               1,      0,
                -sin( theta[1] ),   0,      cos( theta[1] )
              );
    // Calculate rotation about z axis
    Mat R_z = ( Mat_<double>( 3, 3 ) <<
                cos( theta[2] ),    -sin( theta[2] ),      0,
                sin( theta[2] ),    cos( theta[2] ),       0,
                0,               0,                  1 );
    // Combined rotation matrix
    Mat R = R_z * R_y * R_x;
    return R;
}


// Calculates rotation matrix to euler angles
// The result is the same as MATLAB except the order
// of the euler angles ( x and z are swapped ).
Vec3f rotationMatrixToEulerAngles( const Mat& R, bool to_degree )
{
    assert( isRotationMatrix( R ) );
    float sy = sqrt( R.at<double>( 0, 0 ) * R.at<double>( 0, 0 ) +  R.at<double>( 1, 0 ) * R.at<double>( 1, 0 ) );
    bool singular = sy < 1e-6; // If
    float x, y, z;

    if ( !singular )
    {
        x = atan2( R.at<double>( 2, 1 ), R.at<double>( 2, 2 ) );
        y = atan2( -R.at<double>( 2, 0 ), sy );
        z = atan2( R.at<double>( 1, 0 ), R.at<double>( 0, 0 ) );
    }
    else
    {
        x = atan2( -R.at<double>( 1, 2 ), R.at<double>( 1, 1 ) );
        y = atan2( -R.at<double>( 2, 0 ), sy );
        z = 0;
    }
    if(to_degree)
    {
        return Vec3f( rad2deg(x), rad2deg(y), rad2deg(z) );
    }
    else
    {
        return Vec3f( x, y, z );
    }
}



//------------ Distribute weights among the four neighbors a point according to the distance --------------  
//	float px, py, w_x0_y0, w_x1_y0, w_x0_y1, w_x1_y1;
//	px = 10.5;	py = 20.5;
//	compute_bilnear_weight(w_x0_y0, w_x1_y0, w_x0_y1, w_x1_y1, px, py);
//	cout << "(" << int(px) + 0 << ", " << int(py) + 0 << ") : " << w_x0_y0 << ",\t(" << int(px) + 1 << ", " << int(py) + 0 << ") : " << w_x1_y0 << endl;
//	cout << "(" << int(px) + 0 << ", " << int(py) + 1 << ") : " << w_x0_y1 << ",\t(" << int(px) + 1 << ", " << int(py) + 1 << ") : " << w_x1_y1 << endl;
//	=> (10, 20) : 0.25,	(11, 20) : 0.25
//	   (10, 21) : 0.25,	(11, 21) : 0.25
//	px = 30.5;	py = 40.0;
//	compute_bilnear_weight(w_x0_y0, w_x1_y0, w_x0_y1, w_x1_y1, px, py);
//	cout << "(" << int(px) + 0 << ", " << int(py) + 0 << ") : " << w_x0_y0 << ",\t(" << int(px) + 1 << ", " << int(py) + 0 << ") : " << w_x1_y0 << endl;
//	cout << "(" << int(px) + 0 << ", " << int(py) + 1 << ") : " << w_x0_y1 << ",\t(" << int(px) + 1 << ", " << int(py) + 1 << ") : " << w_x1_y1 << endl;
//	=> (30, 40) : 0.5,	(31, 40) : 0.5
//	   (30, 41) : 0,	(31, 41) : 0
void compute_bilinear_weight(float& w_x0_y0, float& w_x1_y0, float& w_x0_y1, float& w_x1_y1, float px, float py)
{
    int x0 = int(px), y0 = int(py);
    float dx0 = px - (float)x0, dy0 = py - (float)y0;
    float dx1 = 1.0 - dx0, dy1 = 1.0 - dy0;
    w_x1_y1 = dx0 * dy0;
    w_x0_y0 = dx1 * dy1;
    w_x0_y1 = dx1 * dy0;
    w_x1_y0 = dx0 * dy1;
    return;   
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
    //float cross = x_ab * y_cb - y_ab * x_cb; // cross product
    float cross = x_ab * y_cb - y_ab * x_cb; // cross product
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


// refernce site : https://www.december.com/html/spec/colorhsl.html
//	float hue_0360 = 357, sat_0100 = 50, lig_0100 = 50;
//	cout << hls_01_to_color_name(hue_0360 / 360, lig_0100 / 100, sat_0100 / 100) << endl;	
//	=> red
//	hue_0360 = 95;	sat_0100 = 50, lig_0100 = 50;
//	cout << hls_01_to_color_name(hue_0360 / 360, lig_0100 / 100, sat_0100 / 100) << endl;	
//	=> green
string hls_01_2_color_name(float hue_01, float lig_01, float sat_01, int n_sp)
{
	cout_indented(n_sp, "hls_01_2_color_name");
	string color_name = "some";
	if(0.000 <= hue_01 && hue_01 <= 1.000 && 0.000 <= lig_01 && lig_01 <= 0.100 && 0.000 <= sat_01 <= 1.000)
	{
		color_name = "black"
	}
	else if(0.000 <= hue_01 && hue_01 <= 1.000 && 0.850 <= lig_01 && lig_01 <= 1.000 && 0.000 <= sat_01 <= 1.000)
	{
		color_name = "white"
	}
	else if((1.0 - 0.03) <= hue_01 || hue_01 <= 0.040 && 0.400 <= lig_01 && lig_01 <= 0.600 && 0.450 <= sat_01 <= 1.000)
	{	//	Note hue value of red is between minus something to plus something. So it is not "&&" but "||".
		color_name = "red"
	}
	else if(0.250 <= hue_01 && hue_01 <= 0.437 && 0.200 <= lig_01 && lig_01 <= 0.550 && 0.450 <= sat_01 <= 1.000)
	{
		color_name = "green"
	}
	else if(0.527 <= hue_01 && hue_01 <= 0.708 && 0.280 <= lig_01 && lig_01 <= 0.650 && 0.550 <= sat_01 <= 1.000)
	{
		color_name = "blue"
	}
	else if(0.133 <= hue_01 && hue_01 <= 0.167 && 0.450 <= lig_01 && lig_01 <= 0.700 && 0.800 <= sat_01 <= 1.000)
	{
		color_name = "yellow"
	}
	else if(0.495 <= hue_01 && hue_01 <= 0.505 && 0.450 <= lig_01 && lig_01 <= 0.700 && 0.750 <= sat_01 <= 1.000)
	{
		color_name = "cyan"
	}
	else if(0.820 <= hue_01 && hue_01 <= 0.920 && 0.450 <= lig_01 && lig_01 <= 0.700 && 0.460 <= sat_01 <= 1.000)
	{
		color_name = "magenta"
	}
	else if(0.889 <= hue_01 && hue_01 <= 0.986 && 0.700 <= lig_01 && lig_01 <= 1.000 && 0.650 <= sat_01 <= 1.000)
	{
		color_name = "pink"
	}
	else if(0.044 <= hue_01 && hue_01 <= 0.111 && 0.450 <= lig_01 && lig_01 <= 0.600 && 0.800 <= sat_01 <= 1.000)
	{
		color_name = "orange"
	}
	else if(0.000 <= hue_01 && hue_01 <= 0.072 && 0.200 <= lig_01 && lig_01 <= 0.400 && 0.550 <= sat_01 <= 1.000)
	{
		color_name = "brown"
	}
	cout_indented(n_sp + 1, color_name);
	return color_name;
}


//	vector<int> li{ 10, 20, 30 };
//	average_of_vector<int>(li, 0);
//	=> average_of_vector START
//	=> agv : 20
//	=> average_of_vector END

template <typename T> 
double average_of_vector(vector<T> &v, int n_sp)
{
    cout_indented(n_sp, "average_of_vector START");  
    double avg = double(accumulate(v.begin(), v.end(), 0.0)) / double(v.size());
    cout_indented(n_sp + 1, "agv : " + to_string(avg));  
    cout_indented(n_sp, "average_of_vector END");  
    return avg;
} 


//	int x = -2, y = 3;
//	cout << func_add_absolute<int>(x, y) : " << func_add_absolute<int>(x, y) << endl;
//	=> func_add_absolute<int>(x, y) : 1

template<typename T> 
double func_add_absolute(T x, T y)
{
    return double(x + fabs(y));
}


//	vector<int> li_1{ 10, 20, 30 };
//	mean_absolute_of_vector<int>(li_1, true, 0);
//	=> mean_absolute_of_vector START
//	=> agv_abs : 20
//	=> mean_absolute_of_vector END
//	vector<int> li_2{ -10, -20, 30 };
//	mean_absolute_of_vector<int>(li_2, false, 0);
//	=> mean_absolute_of_vector START
//	=> agv_abs : 20
//	=> mean_absolute_of_vector END

template <typename T> 
double mean_absolute_of_vector(vector<T> &v, bool are_all_positive, int n_sp)
{
    cout_indented(n_sp, "mean_absolute_of_vector START");
    double avg_abs = are_all_positive ? average_of_vector(v, n_sp + 1) : double(std::accumulate(v.begin(), v.end(), float(0), func_add_absolute<T>)) / double(v.size());
    cout_indented(n_sp + 1, "avg_abs : " + to_string(avg_abs));
    cout_indented(n_sp, "mean_absolute_of_vector END");
    return avg_abs;
}

//	vector<int> li{ 10, 20, 30 };
//	int med = median_of_vector<int>(li, 0);
//	=> median_of_vector START
//	=> median : 20
//	=> median_of_vector END

template <typename T> 
T median_of_vector(vector<T> &v, int n_sp)
{
    cout_indented(n_sp, "median_of_vector START");
    size_t n = v.size() / 2;
    nth_element(v.begin(), v.begin()+n, v.end());
    cout_indented(n_sp + 1, "median : " + to_string(v[n]));
    cout_indented(n_sp, "median_of_vector END");
    return v[n];
}



template <typename T>
struct dist_func {
    double operator()(T& a, T& b)
    {
        //return (a-b).lpNorm<2>();
        return cv::norm(a, b, NORM_L2);
    }
};

//	vector<Vec2f> li_pt = {Vec2f(10, 10), Vec2f(20, 20), Vec2f(30, 30)};
//	Vec2f p_center_vec;
//	geometric_median<float>(li_pt, p_center_vec, dist_func<Vec2f>(), 2, 0);
//	=> geometric_median START
//	==>  geo_median : (20, 20)
//	=> geometric_median END

template<typename Scalar, typename Vector, typename Container, typename distFunciton>
Vector geometric_median(Container& XX, distFunciton distance, int dim, /*int n_sp,*/ int iterations = 200)
{
    Vector geo_median;| |
    size_t N = XX.size();
    if(1 == N)
    {
        geo_median = XX[0];
    }
    else
    {
        // initial guess
        bool is_early_stopped = false;
        Scalar th_delta;
        std::vector<Vector> AA (2, (XX[0] + XX[1]) / Scalar(2));
        for(int it = 0; it < iterations; it++)
        {
            Vector numerator;
            for(size_t i = 0; i < dim; i++) numerator[i] = 0;
            Scalar denominator = 0;
            int t = it % 2;
            for (int n = 0; n < N; n++)
            {
                Scalar dist = distance(XX[n], AA[t]);
                if (dist != 0)
                {
                    numerator += XX[n] / dist;
                    denominator += 1.0 / dist;
                }
            }
            AA[1 - t] = numerator / denominator;
            Scalar d_delta = distance(AA[t], AA[1 - t]);
            if(it)
            {
                if(d_delta < th_delta)
                {
                    is_early_stopped = true;
                    geo_median = AA[1 - t];
                    break;
                }
            }
            else th_delta = d_delta * 0.001;
        }
        if(!is_early_stopped) geo_median = AA[iterations % 2];
    }
    return geo_median;
}


#define RAD_MIN_MC      2.5e-4
double mcosc(double cosx, double x)
{
  //if (fabs(x) < ang_min_mc)
  if (fabs(x) < RAD_MIN_MC)
      return 0.5;
        else
            return ((1.0 - cosx) / x / x);
            }

#define RAD_MIN_MC      2.5e-4
double msinc(double sinx, double x)
{
  //if (fabs(x) < ang_min_mc)
  if (fabs(x) < RAD_MIN_MC)
      return (1. / 6.0);
        else
            return ((1.0 - sinx / x) / x / x);
            }

//------------ Generate a random number between 'minV' and 'maxV' --------------
//srand(time(NULL)); // Seed the time
inline int random_number_in_between(int minV, int maxV)
{
   	static bool init = false;
	if (!init) 
	{
		srand(time(NULL));
		init = true;
	}	
    return rand() % (maxV - minV + 1) + minV;
}    

#define RAD_MIN_SINC    1.0e-8
double sinc(double sinx, double rad)
{
  if (fabs(rad) < RAD_MIN_SINC)
      return 1.0;
        else
            return sinx / rad;
            }

#define RAD_MIN_SINC    1.0e-8
double sinc(double rad)
{
  if (fabs(rad) < RAD_MIN_SINC)
      return 1.0;
        else
            return sin(rad) / rad;
            }




Mat cameraPoseFromHomography(const Mat& H)
{
    Mat pose = Mat::eye(3, 4, CV_64FC1); //3x4 matrix
    float norm1 = (float)norm(H.col(0));
    float norm2 = (float)norm(H.col(1));
    float tnorm = (norm1 + norm2) / 2.0f;

    Mat v1 = H.col(0);
    Mat v2 = pose.col(0);

    cv::normalize(v1, v2); // Normalize the rotation

    v1 = H.col(1);
    v2 = pose.col(1);

    cv::normalize(v1, v2);

    v1 = pose.col(0);
    v2 = pose.col(1);

    Mat v3 = v1.cross(v2);  //Computes the cross-product of v1 and v2
    Mat c2 = pose.col(2);
    v3.copyTo(c2);
    pose.col(3) = H.col(2) / tnorm; //vector t [R|t]
    return pose;
}

cv::Mat homography_dlt(const std::vector< cv::Point2d > &x1, const std::vector< cv::Point2d > &x2)
{
    int npoints = (int)x1.size();
    cv::Mat A(2*npoints, 9, CV_64F, cv::Scalar(0));
    // We need here to compute the SVD on a (n*2)*9 matrix (where n is
    // the number of points). if n == 4, the matrix has more columns
    // than rows. The solution is to add an extra line with zeros
    if (npoints == 4)
        A.resize(2*npoints+1, cv::Scalar(0));
    // Since the third line of matrix A is a linear combination of the first and second lines
    // (A is rank 2) we don't need to implement this third line
    for(int i = 0; i < npoints; i++)
    {              // Update matrix A using eq. 23
        A.at<double>(2*i,3) = -x1[i].x;               // -xi_1
        A.at<double>(2*i,4) = -x1[i].y;               // -yi_1
        A.at<double>(2*i,5) = -1;                     // -1
        A.at<double>(2*i,6) =  x2[i].y * x1[i].x;     //  yi_2 * xi_1
        A.at<double>(2*i,7) =  x2[i].y * x1[i].y;     //  yi_2 * yi_1
        A.at<double>(2*i,8) =  x2[i].y;               //  yi_2
        A.at<double>(2*i+1,0) =  x1[i].x;             //  xi_1
        A.at<double>(2*i+1,1) =  x1[i].y;             //  yi_1
        A.at<double>(2*i+1,2) =  1;                   //  1
        A.at<double>(2*i+1,6) = -x2[i].x * x1[i].x;   // -xi_2 * xi_1
        A.at<double>(2*i+1,7) = -x2[i].x * x1[i].y;   // -xi_2 * yi_1
        A.at<double>(2*i+1,8) = -x2[i].x;             // -xi_2
    }
    // Add an extra line with zero.
    if (npoints == 4)
    {
        for (int i=0; i < 9; i ++) A.at<double>(2*npoints,i) = 0;
    }
    cv::Mat w, u, vt;
    cv::SVD::compute(A, w, u, vt);
    double smallestSv = w.at<double>(0, 0);
    unsigned int indexSmallestSv = 0 ;
    for (int i = 1; i < w.rows; i++)
    {
        if ((w.at<double>(i, 0) < smallestSv) )
        {
            smallestSv = w.at<double>(i, 0);
            indexSmallestSv = i;
        }
    }
    cv::Mat h = vt.row(indexSmallestSv);
    if (h.at<double>(0, 8) < 0) // tz < 0
    h *=-1;
    cv::Mat _2H1(3, 3, CV_64F);
    for (int i = 0 ; i < 3 ; i++)
        for (int j = 0 ; j < 3 ; j++)
            _2H1.at<double>(i,j) = h.at<double>(0, 3*i+j);
    return _2H1;
}

void pose_from_homography_dlt(const std::vector< cv::Point2d > &xw, const std::vector< cv::Point2d > &xo,
							  cv::Mat &otw, cv::Mat &oRw)
{
	cv::Mat oHw = homography_dlt(xw, xo);
	Mat mat_pose = cameraPoseFromHomography(oHw);
	oRw = mat_pose(Rect(0, 0, 3, 3)).clone();
	otw = mat_pose(Rect(3, 0, 1, 3)).clone();
}
	    
Mat orthonormalize(const Mat inMat)
{
  Mat _, U, V, V_, R;  
  int minLoc[2], maxLoc[2];
  double minVal, maxVal;
  SVDecomp(inMat, _, U, V);
  V_ = V.t();
  U.at<double>(0,0) *= -1; U.at<double>(0,1) *= -1; U.at<double>(1,0) *= -1; U.at<double>(1,1) *= -1; U.at<double>(2,0) *= -1; U.at<double>(2,1) *= -1;
  V_.at<double>(0,0) *= -1;V_.at<double>(0,1) *= -1; V_.at<double>(1,0) *= -1; V_.at<double>(1,1) *= -1; V_.at<double>(2,0) *= -1; V_.at<double>(2,1) *= -1;
  //cout << "V_" << endl << V_.t() << endl;
  R = U*V_.t();
  if (determinant(R)<0)
  {
    V_.at<double>(0,2) *= -1;V_.at<double>(1,2) *= -1; V_.at<double>(2,2) *= -1;
    R = U*V_.t();
  }
    
  return R;
}



Mat logarithm_map(const Mat& rot_mat)
{
    Mat rot_vec;
    Rodrigues(rot_mat, rot_vec);
    return rot_vec;    
}


Mat SkewSymmetricMatrix(const Mat& vec)
{
    return cv::sfm::skew(vec);
} 

Mat RotationFromUnitAxisAngle(const Mat& unit_axis, double angle)
{
    Mat rot_mat;
    Rodrigues(angle * unit_axis, rot_mat);
    return rot_mat;
}    

Mat GeodesicL1Mean_of_rotation(vector<Mat> R_input, bool b_outlier_rejection, int n_iterations, float thr_convergence)
{
    int n_samples = R_input.size();
    int idx_firstQ = ceil(float(n_samples) / 4.0);
    Mat s = zeros_like(R_input[0]);
    for(int iR = 0; iR < 3; iR++)
    {
        for(int iC = 0; iC < 3; iC++)
        {
            vector<double> li_val(n_samples);
            for(int iS = 0; iS < n_samples; iS++)
            {
                li_val[iS] = R_input[iS].at<double>(iR, iC);
            }
            double val_med = median_of_vector<double>(li_val, -100);
            s.at<double>(iR, iC) = val_med;
        }
    }     
    
    //Mat R = ProjectOntoSO3(s);
    Mat R = orthonormalize(s);	
    //cout << "R : " << endl << R << endl;    exit(0);
    for(int iI = 0; iI < n_iterations; iI++)
    {
        vector<Mat> vs(n_samples);
        vector<double> v_norms(n_samples);
        for(int iS = 0; iS < n_samples; iS++)
        {
            Mat v = logarithm_map(R_input[iS] * R.t());
            double v_norm = norm(v);
            vs[iS] = v;
            v_norms[iS] = v_norm;
        }
        double thr = 100000000000000000000.0;
        if(b_outlier_rejection)
        {
            vector<double> sorted_v_norms(v_norms);
            sort(sorted_v_norms.begin(), sorted_v_norms.end());
            double v_norm_firstQ = sorted_v_norms[idx_firstQ];
            thr = n_samples <= 50 ? MAX(v_norm_firstQ, 1.0) : MAX(v_norm_firstQ, 0.5);
        }
        #if 0
        cout << "thr : " << thr << endl;
        cout << "vs : " << endl;
        for(auto v : vs)
        {
            cout << v << endl;
        }
        cout << "v_norms : " << endl;
        for(auto v_norm : v_norms) 
        {
            cout << v_norm << ", ";
        }
        cout << endl;
        exit(0);
        #endif  //  0

        Mat step_num = zeros_like(vs[0]);
        double step_den = 0;
        for(int iS = 0; iS < n_samples; iS++)
        {
            Mat v = vs[iS];
            double v_norm = v_norms[iS];
            if(v_norm > thr)
            {
                continue;
            }
            step_num += v / v_norm;
            step_den += 1.0 / v_norm;
        }
        Mat delta = step_num / step_den;
        double delta_angle_rad = norm(delta);
        Mat delta_axis = delta / delta_angle_rad;
        Mat R_delta = RotationFromUnitAxisAngle(delta_axis, delta_angle_rad);
        R = R_delta * R;
        if(delta_angle_rad < thr_convergence)
        {
            break;
        }
    }
    return R;
}


Mat avoid_median_to_be_the_same_as_one_of_samples(const vector<Mat>& R_input, const Mat& s_ori)
{
    bool is_current_median_the_same_as_one_or_more_of_samples = false;
    for(auto R : R_input)
    {
        double sum_dif = norm(R - s_ori);
        if(sum_dif < 0.001)
        {
            is_current_median_the_same_as_one_or_more_of_samples = true;
            break;
        }     
    }
    if(is_current_median_the_same_as_one_or_more_of_samples)
    {
        Mat mat_rand = zeros_like(s_ori);
        randu(mat_rand, Scalar(-0.001), Scalar(0.001));
        Mat s_new = s_ori + mat_rand;
        return s_new;
    }
    else
    {
        return s_ori;
    }
}

Mat ChordalL1Mean_of_rotation(vector<Mat> R_input, bool b_outlier_rejection, int n_iterations, float thr_convergence)
{
    int n_samples = R_input.size();
    int idx_firstQ = ceil(float(n_samples) / 4.0);
    Mat s = zeros_like(R_input[0]);
    for(int iR = 0; iR < 3; iR++)
    {
        for(int iC = 0; iC < 3; iC++)
        {
            vector<double> li_val(n_samples);
            for(int iS = 0; iS < n_samples; iS++)
            {
                li_val[iS] = R_input[iS].at<double>(iR, iC);
            }
            double val_med = median_of_vector<double>(li_val, -100);
            s.at<double>(iR, iC) = val_med;
        }
    }     
    //cout << "s : " << endl << s << endl;    exit(0); 
    for(int iI = 0; iI < n_iterations; iI++)
    {
        //cout << "iI : " << iI << endl;    //exit(0); 
        s = avoid_median_to_be_the_same_as_one_of_samples(R_input, s);
        vector<double> v_norms(n_samples);
        for(int iS = 0; iS < n_samples; iS++)
        {
            Mat v = R_input[iS] - s;
            double v_norm = norm(v);
            v_norms[iS] = v_norm;
        }
        
        double thr = 100000000000000000000.0;
        if(b_outlier_rejection)
        {
            vector<double> sorted_v_norms(v_norms);
            sort(sorted_v_norms.begin(), sorted_v_norms.end());
            double v_norm_firstQ = sorted_v_norms[idx_firstQ];
            thr = n_samples <= 50 ? MAX(v_norm_firstQ, 1.356) : MAX(v_norm_firstQ, 0.7);
            //  2*sqrt(2)*sin(1/2) is approximately 1.356
            //  2*sqrt(2)*sin(0.5/2) is approximately 0.7
        }
        //cout << "thr : " << thr << endl;    exit(0);
        Mat step_num = zeros_like(s);
        double step_den = 0;
        for(int iS = 0; iS < n_samples; iS++)
        {
            double v_norm = v_norms[iS];
            if(v_norm > thr)
            {
                continue;
            }
            step_num += R_input[iS] / v_norm;
            step_den += 1.0 / v_norm;
        }
        Mat s_prev = s.clone();
        s = step_num / step_den;
        //cout << "s : " << endl << s << endl;    //exit(0); 
        Mat update_medvec = s - s_prev;
        //cout << "update_medvec : " << update_medvec << endl;
        //cout << "thr_convergence : " << thr_convergence << endl;
        //double t1 = norm(update_medvec);
        //cout << "t1 : " << t1 << endl;
        //cout << endl;
        if(norm(update_medvec) < thr_convergence)
        {
            break;
        }     
    }  
    //exit(0);
    Mat R = ProjectOntoSO3(s);
    return R;
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//   OpenCV related
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


Mat alpha_blend(Mat& img1, Mat& img2, Mat& mask_0255)
{
    // Blend img1 and img2 (of CV_8UC3) with mask (CV_8UC1)
    assert(img1.size() == img2.size() && img1.size() == mask.size());
    Mat blended = cv::Mat(img1.size(), img1.type());
    for (int y = 0; y < blended.rows; ++y){
        for (int x = 0; x < blended.cols; ++x){
            float alpha = mask_0255.at<unsigned char>(y, x) / 255.0f;
            blended.at<cv::Vec3b>(y, x) = alpha * img1.at<cv::Vec3b>(y, x) + (1 - alpha) * img2.at<cv::Vec3b>(y, x);
        }
    }
	return blended;	
}


//------------ Concatenate two images either horizontally or vetically	--------------  	
Mat concatenate_images(const Mat& img1, const Mat& img2, int minus_hori_plus_vert_zero_auto, int neg_left_or_top_0_center_pos_right_or_bottom, float factor_margin, const Scalar& color_margin)	
{	
	Mat res;	
	//  Check if the two image have the same # of channels and type	
	//  If # channels or type is different	
	//if(img1.type() != img2.type() || img1.channels() != img2.channels())    return res;	
	assert(img1.type() == img2.type() && img1.channels() == img2.channels());	
	int sum_row = img1.rows + img2.rows, sum_col = img1.cols + img2.cols;	
	int rows = img1.rows + img2.rows, cols = img1.cols + img2.cols, margin;	
	bool is_horizontal = true;
	Point offset_1(0, 0), offset_2(0, 0);
	if(minus_hori_plus_vert_zero_auto >= 0)	
	{	
		if(minus_hori_plus_vert_zero_auto > 0)	
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
		margin = sum_col * factor_margin;
		cols = sum_col + margin;
		rows = max(img1.rows, img2.rows);
		offset_2.x = img1.cols + margin;
		if(img1.rows > img2.rows)
		{
			int dif_row = img1.rows - img2.rows;
			rows = img1.rows;
			if(neg_left_or_top_0_center_pos_right_or_bottom > 0)
			{
				offset_2.y = dif_row;
			}
			else if(0 == neg_left_or_top_0_center_pos_right_or_bottom)
			{
				offset_2.y = dif_row * 0.5;
			}
		}
		else if(img1.rows < img2.rows)
		{
			int dif_row = img2.rows - img1.rows;
			rows = img2.rows;
			if(neg_left_or_top_0_center_pos_right_or_bottom > 0)
			{
				offset_1.y = dif_row;
			}
			else if(0 == neg_left_or_top_0_center_pos_right_or_bottom)
			{
				offset_1.y = dif_row * 0.5;
			}
		}			
	}	
	else	
	{	
		margin = sum_row * factor_margin; 
		cols = max(img1.cols, img2.cols);	
		rows = sum_row + margin;		
		offset_2.y = img1.rows + margin;		
		if(img1.cols > img2.cols)			
		{
			int dif_col = img1.cols - img2.cols;
			cols = img1.cols;
			if(neg_left_or_top_0_center_pos_right_or_bottom > 0)
			{
				offset_2.x = dif_col;
			}
			else if(0 == neg_left_or_top_0_center_pos_right_or_bottom)
			{
				offset_2.x = dif_col * 0.5;
			}
		}
		else if(img1.cols < img2.cols)
		{
			int dif_col = img2.cols - img1.rows;
			cols = img2.cols;
			if(neg_left_or_top_0_center_pos_right_or_bottom > 0)
			{
				offset_1.x = dif_col;
			}
			else if(0 == neg_left_or_top_0_center_pos_right_or_bottom)
			{
				offset_1.x = dif_col * 0.5;
			}
		}					
 	}	
 	// Create a black image	
 	//res = Mat3b(rows, cols, Vec3b(0,0,0));	
 	res = Mat::zeros(rows, cols, img1.type());	res = color_margin;
 	// Copy images in correct position	
 	img1.copyTo(res(Rect(offset_1.x, offset_1.y, img1.cols, img1.rows)));	
	img2.copyTo(res(Rect(offset_2.x, offset_2.y, img2.cols, img2.rows)));	
 	//imshow("img1", img1);waitKey();   imshow("img2", img2);   imshow("res", res); waitKey();  exit(0);	
 	return res;	
}	





//	Mat locations, im_255_edge, im_gray = imread("im_gray.bmp", CV_LOAD_GRAYSCALE);
//	Canny(im_gray, im_255_edge, 50, 150);
//	connect_broken_contour(im_255_edge, Size(5, 5), 0);

#include "opencv2/ximgproc.hpp"
Mat connect_broken_contour(const Mat& im_255_edge, const Size& knl_gauss, int n_sp)     
{
    cout_indented(n_sp, "complete_broken_contour START");      
    Mat im_thinning, im_edge_blurred, im_edge_threshold;   
    GaussianBlur(im_255_edge, im_edge_blurred, knl_gauss, 0);    
    threshold(im_edge_blurred, im_edge_threshold, 0, 255, THRESH_BINARY);      
    ximgproc::thinning(im_edge_threshold, im_thinning, ximgproc::THINNING_ZHANGSUEN);    
    //ximgproc::thinning(im_edge_threshold, im_thinning, ximgproc::THINNING_GUOHALL);             
    //imwrite("im_thinning.bmp", im_thinning);    //exit(0);                     
    cout_indented(n_sp, "complete_broken_contour END");         
    return im_thinning;       
}          



//	Mat locations, im_255_edge, im_gray = imread("im_gray.bmp", CV_LOAD_GRAYSCALE);
//	Canny(im_gray, im_255_edge, 50, 150);
//	findNonZero(im_255_edge, locations);
//	locations = locations.reshape(1);
//	vector<Vec2f> li_pt = Mat_to_vector_Vec2f(locations, 0);

std::vector<cv::Vec2f> Mat_to_vector_Vec2f(const Mat& mat, int n_sp)
{
    cout_indented(n_sp, "Mat_to_vector_Vec2f START");
    if(!(
        2 == mat.channels() * mat.cols
    )) exit(0);

    Mat2f matt = (mat.cols == 2) ? mat.reshape(2) : mat.clone(); 
    
    std::vector<cv::Vec2f> li_vec2f(matt.begin(), matt.end());
    cout_indented(n_sp, "Mat_to_vector_Vec2f END");
    return li_vec2f;
}


vector<int> compute_indice_of_no_hole_contour(const vector<Vec4i>& hierarchy, int n_sp)
{
    cout_indented(n_sp, "compute_indice_of_no_hole_contour");
    int iC, idx_nex = 0, n_cnt = hierarchy.size();
    vector<int> li_idx_no_hole_cnt = {idx_nex};
    for(iC = 0; iC < n_cnt; iC++)
    {
        if(idx_nex != iC) continue;
        idx_nex = hierarchy[iC][0];
        if(idx_nex < 0) break;
        li_idx_no_hole_cnt.push_back(idx_nex);
        cout_indented(n_sp + 1, "idx_nex : " + to_string(idx_nex));
    }
    return li_idx_no_hole_cnt;
}


Mat init_mat_with_one_value(const Size& sz, int mat_type, const Scalar& val)
{
    return Mat(sz, mat_type, val);
}



cv::Mat combine_rotation_translation_into_homogeneous_matrix(const cv::Mat& rot, const cv::Mat& tra)
{
	cv::Mat rot_mat;
	bool is_rot_valid = true;
	int n_elem_rot = rot.rows * rot.cols;
	if(3 == n_elem_rot)
	{
		cv::Rodrigues(rot, rot_mat);
	}
	else if(9 == n_elem_rot)
	{
		if(is_rotation_matrix(rot)) rot_mat = rot;
		else is_rot_valid = false;
	}
	else is_rot_valid = false;
	if(!is_rot_valid) { std::cout << "The given rotation matirx is NOT a real rotation matrix." << std::endl;        exit(0); }
	cv::Mat mat_homo = cv::Mat::eye(4, 4, CV_32F);
	rot_mat.copyTo(mat_homo(cv::Rect(0, 0, 3, 3)));
	tra.copyTo(mat_homo(cv::Rect(3, 0, 1, 3)));
	return mat_homo;
}


float compute_ratio_of_largest_blob(const Mat& im_255_blob, int n_sp)
{
    cout_indented(n_sp, "compute_ratio_of_largest_blob");
    vector<vector<Point> > li_cnt;
    findContours(im_255_blob, li_cnt, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    int n_cnt = li_cnt.size();
    double area_max = 0;
    if(n_cnt > 1)
    {
        for(auto cnt : li_cnt)
        {
            //double area = contourArea(cnt);
            double area = compute_area_of_contour(cnt, n_sp + 2);
            //cout_indented(n_sp + 2, "area : " + to_string(area));
            if(area > area_max) area_max = area;
        }
    }
    else
    {
        area_max = countNonZero(im_255_blob);
    }
    cout_indented(n_sp + 1, "area_max : " + to_string(area_max) + " / " + to_string(im_255_blob.cols *               im_255_blob.rows));
    return area_max / float(im_255_blob.cols * im_255_blob.rows);
}

float emd_btn_histograms(const Mat& sig1, const Mat& sig2, int n_sp)    
{
	cout_indented(n_sp, "emd_btn_histograms");           
	float dist = EMD(sig1, sig2, cv::DIST_L2);       
	cout_indented(n_sp + 1, "dist : " + to_string(dist));     
	return dist;           
}           



float distance_btn_histograms(const Mat& h1, const Mat& h2, int n_sp)                                      
{                                                                                                          
    cout_indented(n_sp, "distance_btn_histograms");                                                        
    float dist;                                                                                            
    //normalize(h1, h1, 1, 0, cv::NORM_L1);    normalize(h1, h1, 1, 0, cv::NORM_L1);                       
    int n_bin_1 = h1.rows, n_bin_2 = h1.cols;                                                              
    vector<Vec3f> sigv1, sigv2;                                                                            
    float sum1 = 0, sum2 = 0;                                                                              
    for(int h = 0; h < n_bin_1; h++)                                                                       
    {                                                                                                      
        //cout_indented(n_sp + 1, "h : " + to_string(h) + " / " + to_string(n_bin_1));                     
        for(int s = 0; s < n_bin_2; s++)                                                                   
        {                                                                                                  
            //cout_indented(n_sp + 2, "s : " + to_string(s) + " / " + to_string(n_bin_2));                 
            float bin_val_1 = h1.at<float>(h, s), bin_val_2 = h2.at<float>(h, s);                          
            if( bin_val_1 != 0 ) sigv1.push_back( cv::Vec3f(bin_val_1, (float)h, (float)s));               
            if( bin_val_2 != 0 ) sigv2.push_back( cv::Vec3f(bin_val_2, (float)h, (float)s));               
            sum1 += bin_val_1;  sum2 += bin_val_2;                                                         
        }                                                                                                  
    }                                                                                                      
    //cout << "sum1 : " << sum1 << ", sum2 : " << sum2 << endl;                                            
    // make Nx3 32fC1 matrix, where N is the number of nonzero histogram bins                              
    cout_indented(n_sp + 1, "sigv1.size() : " + to_string(sigv1.size()));                                  
    cout_indented(n_sp + 1, "sigv2.size() : " + to_string(sigv2.size()));                                  
    Mat sig1 = cv::Mat(sigv1).clone().reshape(1), sig2 = cv::Mat(sigv2).clone().reshape(1);                
    //dist = EMD(sig1, sig2, cv::DIST_L2);                                                                 
    dist = emd_btn_histograms(sig1, sig2, n_sp + 1)    
	cout_indented(n_sp + 1, "dist : " + to_string(dist));                                                  
    return dist;                                                                                           
}                       



 bool cluster_histograms(int& id_last, vector<int>& li_id, Mat& hash_table_dist, vector<vector<int> >&      
     li_cluster_id, vector<Mat>& li_hist, float th_dist, bool is_hsv, int n_sp)                                 
{                                                                                                          
    cout_indented(n_sp, "cluster_histograms");                                                             
    cout_indented(n_sp + 1, "li_hist.size() : " + to_string(li_hist.size()));                              
    bool is_something_merged = false;                                                                      
    while(1)                                                                                               
    {                                                                                                      
        int i1, i2, n_cluster = li_id.size();                                                              
        cout_indented(n_sp + 1, "n_cluster : " + to_string(n_cluster));                                    
        float min_dist = 10000000000000, max_dist = -1;                                                    
        int idx1_closest = -1, idx2_closest = -1;                                                          
        vector<Mat> li_hist_emd;                                                                           
        for(int iC = 0; iC < n_cluster; iC++)                                                              
        {                                                                                                  
            cout_indented(n_sp + 2, "iC : " + to_string(iC) + " / " + to_string(n_cluster));               
            li_hist_emd.push_back(compute_histogram_4_emd(li_hist[iC], is_hsv, n_sp + 3));                 
        }                                                                                                  
        for(i1 = 0; i1 < n_cluster - 1; i1++)                                                              
        {                                                                                                  
            int id_1 = li_id[i1];                                                                          
            for(i2 = i1 + 1; i2 < n_cluster; i2++)                                                         
            {                                                                                              
                int id_2 = li_id[i2];                                                                      
                float dist = hash_table_dist.at<float>(id_1, id_2);                                        
                if(0 == dist)                                                                              
                {                                                                                          
                    dist = emd_btn_histograms(li_hist_emd[i1], li_hist_emd[i2], -100);                     
                    hash_table_dist.at<float>(id_1, id_2) = dist; hash_table_dist.at<float>(id_2, id_1) =  
dist;                                                                                                      
                }                                                                                          
                if(dist < min_dist)                                                                        
                {                                                                                          
                    min_dist = dist;                                                                       
                    if(dist < th_dist) { idx1_closest = i1;  idx2_closest = i2; }                          
                }                                                                                          
                if(dist > max_dist) max_dist = dist;                                                       
            }                                                                                              
        }                           
        if(idx1_closest + idx2_closest < 0) break;                                                         
        is_something_merged = true;                                                                        
        int id_1 = li_id[idx1_closest], id_2 = li_id[idx2_closest];                                        
        float n_member_1 = li_cluster_id[idx1_closest].size(), n_member_2 = li_cluster_id[idx2_closest].   
size();                                                                                                    
        float w1 = n_member_1 / (n_member_1 + n_member_2), w2 = n_member_2 / (n_member_1 + n_member_2);    
        cout_indented(n_sp + 2, "w1 : " + to_string(w1) + ", w2 : " + to_string(w2));  //exit(0);          
        li_hist[idx1_closest] = w1 * li_hist[idx1_closest] + w2 * li_hist[idx2_closest];                   
        li_hist.erase(li_hist.begin() + idx2_closest);                                                     
        for(int iS = 0; iS < li_cluster_id[idx2_closest].size(); iS++)                                     
        {                                                                                                  
            li_cluster_id[idx1_closest].push_back(li_cluster_id[idx2_closest][iS]);                        
        }                                                                                                  
        li_cluster_id.erase(li_cluster_id.begin() + idx2_closest);                                         
        for(auto cluster_id : li_cluster_id)                                                               
        {                                                                                                  
            for(auto id : cluster_id) cout_indented(n_sp + 4, "id : " + to_string(id));                    
        }                                                                                                  
        if(0 == hash_table_dist.at<float>(id_1, id_2) || 0 == hash_table_dist.at<float>(id_2, id_1))       
        {                                                                                                  
            hash_table_dist.at<float>(id_1, id_2) = min_dist;   hash_table_dist.at<float>(id_2, id_1) =    
min_dist;                                                                                                  
        }                                                                                                  
        li_id[idx1_closest] = id_last++;                                                                   
        li_id.erase(li_id.begin() + idx2_closest);                                                         
    }                                                                                                      
    return is_something_merged;                                                                            
}                                                                                                          

		
		
		
Mat compute_histogram_4_emd(const Mat& hist, bool is_hsv, int n_sp)   
{
	cout_indented(n_sp, "compute_histogram_4_emd");                                                       
	vector<Vec3f> sigv;       
	float ssum = 0;  
	if(is_hsv)
	{
		int n_bin_h = hist.size[0], n_bin_s = hist.size[1], n_bin_v = hist.size[2];// : hist.size[2];      
		for(int h = 0; h < n_bin_h; h++)                                                                   
        {                                                                                                  
            for(int s = 0; s < n_bin_s; s++)                                                               
            {                                                                                              
                float sum_val = 0;                                                                         
				for(int v = 0; v < n_bin_v; v++)                                                           
                {                                                                                          
                    float bin_val = hist.at<float>(h, s, v);                                               
                    sum_val += bin_val;                                                                    
                }                                                                                          
                if(0 != sum_val) sigv.push_back(cv::Vec3f(sum_val, (float)h, (float)s));                   
                ssum += sum_val;                                                                           
            }                                                                                              
        }                                                                                                  
    }                                                                                                      
    else    //  hls                                                                                        
    {                                                                                                      
		int n_bin_h = hist.size[0], n_bin_l = hist.size[1], n_bin_s = hist.size[2];// : hist.size[2];      
        for(int h = 0; h < n_bin_h; h++)                                                                   
        {                                                                                                  
            for(int s = 0; s < n_bin_s; s++)                                                               
            {                                                                                              
                float sum_lig = 0;                                                                         
                for(int l = 0; l < n_bin_l; l++)                                                           
                {                                                                                          
                    float bin_val = hist.at<float>(h, l, s);                                               
                    sum_lig += bin_val;                                                                    
                }                                                                                          
                if(0 != sum_lig) sigv.push_back(cv::Vec3f(sum_lig, (float)h, (float)s));                   
                ssum += sum_lig;                                                                           
            }                                                                                              
        }                                                                                                  
    }                                                                                                      
    cout_indented(n_sp + 1, "ssum : " + to_string(ssum));                                                  
    cout_indented(n_sp + 1, "sigv.size() : " + to_string(sigv.size()));                                    
    return cv::Mat(sigv).clone().reshape(1);                                                               
}                                                                                                          

Mat compute_edge_bilateral(const Mat& im_gray, int diameter, double sigma_color, double sigma_space, double          th_low, double th_high)
{
    Mat im_blur, im_255_edge;
    bilateralFilter(im_gray, im_blur, diameter /*9*/, sigma_color/*75*/, sigma_space/*75*/);
    Canny(im_blur, im_255_edge, th_low, th_high);
    return im_255_edge;
}

Mat compute_edge_gaussian(const Mat& im_gray, const Size& smooth_sz, double th_low, double th_high)
{
    Mat im_blur, im_255_edge;
    //medianBlur(im_gray, im_blur, smooth_size/*7*/);
    GaussianBlur(im_gray, im_blur, smooth_sz, 0, 0);
    Canny(im_blur, im_255_edge, th_low, th_high);
    return im_255_edge;
}

Mat compute_edge_median(const Mat& im_gray, int smooth_size, double th_low, double th_high)
{
    Mat im_blur, im_255_edge;
    medianBlur(im_gray, im_blur, smooth_size/*7*/);
    Canny(im_blur, im_255_edge, th_low, th_high);
    return im_255_edge;
}




Mat exponential_map_direct(const Mat &v, const double &delta_t, int n_sp)
{
    cout_indented(n_sp, "exponential_map_direct START");   
    if(!(6 == v.rows && 1 == v.cols)) throw std::length_error("Cannot compute direct exponential map from a " + std::to_string(v.rows) + " by " + std::to_string(v.cols) + ". Should be 6 by 1.");
    double theta, si, co, sinc, mcosc, msinc;
    Mat rd, u, dt(3, 1, CV_64F), v_dt = v * delta_t;
    v_dt(Rect(0, 3, 1, 3)).copyTo(u);
    Rodrigues(u, rd);
    theta = norm(u, NORM_L2);    
    si = sin(theta);
    co = cos(theta);
    sinc = sinc_wo_visp(si, theta);
    mcosc = mcosc_wo_visp(co, theta);
    msinc = msinc_wo_visp(si, theta);
    double  u_0 =       u.at<double>(0),    u_1 =       u.at<double>(1),    u_2 =       u.at<double>(2), 
            v_dt_0 =    v_dt.at<double>(0), v_dt_1 =    v_dt.at<double>(1), v_dt_2 =    v_dt.at<double>(2);
    dt.at<double>(0) =  v_dt_0 * (sinc + u_0 * u_0 * msinc) +
                        v_dt_1 * (u_0 * u_1 * msinc - u_2 * mcosc) + 
                        v_dt_2 * (u_0 * u_2 * msinc + u_1 * mcosc);
    dt.at<double>(1) =  v_dt_0 * (u_0 * u_1 * msinc + u_2 * mcosc) + 
                        v_dt_1 * (sinc + u_1 * u_1 * msinc) +
                        v_dt_2 * (u_1 * u_2 * msinc - u_0 * mcosc);

    dt.at<double>(2) =  v_dt_0 * (u_0 * u_2 * msinc - u_1 * mcosc) +
                        v_dt_1 * (u_1 * u_2 * msinc + u_0 * mcosc) +
                        v_dt_2 * (sinc + u_2 * u_2 * msinc);
    Mat Delta = combine_rotation_translation_into_homogeneous_matrix(rd, dt);
    cout_indented(n_sp, "exponential_map_direct END");   
    return Delta;
}








// 	#define WDIBIXEL uint8_t
//	Mat im_bgr = imread("im_bgr.bmp");
//	Mat im_bgr_rotated = Mat::zeros(Size(im_bgr.cols * 2, im_bgr.rows * 3), im_bgr.type()); 
//	WDIBPIXEL *pDstBase = im_bgr_rotated.data, *pSrcBase = im_bgr.data;
//	int n_channel = im_bgr.channels(), 
//		srcW = im_bgr.cols, srcH = im_bgr.rows, srcDelta = im_bgr.step;
//		dstW = im_bgr_rotated.cols, dstH = im_bgr_rotated.rows, dstDelta = im_bgr_rotated.step;
//	float fSrcCX = 0.5 * srcW, fSrcCY = 0.4 * srcH, 
//		fDstCX = 0.6 * dstW, fDstCY = 0.2 * dstH, fAngle = deg2rad(45), fScale = 1.0;
//	if (1 == n_channel && IsExp2(srcW) && IsExp2(srcH)) RotateWrapFillFastSrcSizeExp2(
//		pDstBase, dstW, dstH, dstDelta, pSrcBase, srcW, srcH, srcDelta, n_channel, 
//		fDstCX, fDstCY, fSrcCX, fSrcCY, fAngle, fScale, true, 0);
//	=> RotateWrapFillFastSrcSizeExp2 

static
void RotateWrapFillFastSrcSizeExp2(
    WDIBPIXEL *pDstBase, int dstW, int dstH, int dstDelta,
    WDIBPIXEL *pSrcBase, int srcW, int srcH, int srcDelta,
    int n_channel,
    float fDstCX, float fDstCY,
    float fSrcCX, float fSrcCY,
    float fAngle, float fScale, 
    bool is_mosaicking, int n_sp)
{
    cout_indented(n_sp, "RotateWrapFillFastSrcSizeExp2");
    if (dstW <= 0) { return; }
    if (dstH <= 0) { return; }
    srcDelta /= sizeof(WDIBPIXEL);
    dstDelta /= sizeof(WDIBPIXEL);
    //cout_indented(n_sp + 1, "srcDelta_ori : " + to_string(srcDelta_ori));
    cout_indented(n_sp + 1, "srcDelta : " + to_string(srcDelta));
    cout_indented(n_sp + 1, "dstDelta : " + to_string(dstDelta));   
    float duCol = (float)sin(-fAngle) * (1.0f / fScale);
    float dvCol = (float)cos(-fAngle) * (1.0f / fScale);
    float duRow = dvCol;
    float dvRow = -duCol;
    float startingu = fSrcCX - (fDstCX * dvCol + fDstCY * duCol);
    float startingv = fSrcCY - (fDstCX * dvRow + fDstCY * duRow);
    float rowu = startingu;
    float rowv = startingv;
    for(int y = 0; y < dstH; y++)
    {
        float u = rowu;
        float v = rowv;
        WDIBPIXEL *pDst = pDstBase + (dstDelta * y);
        for(int x = 0; x < dstW ; x++)
        {
            #if DEBUG_DRAW
            if ((int(u) == int(fSrcCX)) && (int(v) == int(fSrcCY)))
            {
                *pDst++ = DEBUG_MARK_COLOR;
                u += duRow;
                v += dvRow;
                continue;
            }
            #endif
            int sx = (int)u * n_channel;
            int sy = (int)v;
            // Negative u/v adjustement
            if(is_mosaicking)
            {
                if (u < 0) {
                    for(int iC = 0; iC < n_channel; iC++) sx--; 
                }
                if (v < 0) { sy--; }
                sx &= (srcDelta - n_channel);
                sy &= (srcH - 1);
            }
            else
            {
                if(!(0 <= u && u < srcW && 0 <= v && v < srcH)) 
                {
                    for(int iC = 0; iC < n_channel; iC++) pDst++;
                    u += duRow;
                    v += dvRow;
                    continue;
                }                
            }
            WDIBPIXEL *pSrc = pSrcBase + sx + (sy * srcDelta);
            for(int iC = 0; iC < n_channel; iC++) *pDst++ = *pSrc++;
            u += duRow;
            v += dvRow;
        }
        rowu += duCol;
        rowv += dvCol;
    }
}


// 	#define WDIBPIXEL uint8_t
//	Mat im_bgr = imread("im_bgr.bmp");
//	Mat im_bgr_rotated = Mat::zeros(Size(im_bgr.cols * 2, im_bgr.rows * 3), im_bgr.type()); 
//	WDIBPIXEL *pDstBase = im_bgr_rotated.data, *pSrcBase = im_bgr.data;
//	int n_channel = im_bgr.channels(), 
//		srcW = im_bgr.cols, srcH = im_bgr.rows, srcDelta = im_bgr.step;
//		dstW = im_bgr_rotated.cols, dstH = im_bgr_rotated.rows, dstDelta = im_bgr_rotated.step;
//	float fSrcCX = 0.5 * srcW, fSrcCY = 0.4 * srcH, 
//		fDstCX = 0.6 * dstW, fDstCY = 0.2 * dstH, fAngle = deg2rad(45), fScale = 1.0;
//	RotateWrapFill(
//		pDstBase, dstW, dstH, dstDelta, pSrcBase, srcW, srcH, srcDelta, n_channel, 
//		fDstCX, fDstCY, fSrcCX, fSrcCY, fAngle, fScale, true, 0);
//	=> RotateWrapFill 

void RotateWrapFill(
    WDIBPIXEL *pDstBase, int dstW, int dstH, int dstDelta,
    WDIBPIXEL *pSrcBase, int srcW, int srcH, int srcDelta,
    int n_channel,
    float fDstCX, float fDstCY,
    float fSrcCX, float fSrcCY, 
    float fAngle, float fScale, 
    bool is_mosaicking, int n_sp)
{
    cout_indented(n_sp, "RotateWrapFill");    
    if (1 == n_channel && IsExp2(srcW) && IsExp2(srcH))
    {
        cout_indented(n_sp + 1, "scrW : " + to_string(srcW));
        RotateWrapFillFastSrcSizeExp2
        (
            pDstBase, dstW,dstH,dstDelta,
            pSrcBase,srcW, srcH, srcDelta,
            n_channel,
            fDstCX, fDstCY,
            fSrcCX, fSrcCY,
            fAngle, fScale,
            is_mosaicking, n_sp + 1
        );
        return;
    }    
    cout_indented(n_sp + 1, "srcDelta : " + to_string(srcDelta));
    cout_indented(n_sp + 1, "dstDelta : " + to_string(dstDelta));   //exit(0);
    if (dstW <= 0) { return; }
    if (dstH <= 0) { return; }
    //cout_indented(n_sp, "srcDelta : " + to_string(srcDelta));   
    srcDelta /= sizeof(WDIBPIXEL);
    dstDelta /= sizeof(WDIBPIXEL);
    float duCol = (float)sin(-fAngle) * (1.0f / fScale);
    float dvCol = (float)cos(-fAngle) * (1.0f / fScale);
    float duRow = dvCol;
    float dvRow = -duCol;
    float startingu = fSrcCX - (fDstCX * dvCol + fDstCY * duCol);
    float startingv = fSrcCY - (fDstCX * dvRow + fDstCY * duRow);
    float rowu = startingu;
    float rowv = startingv;   
    //cout_indented(n_sp + 1, "(fSrcCX, fSrcCY) : (" + to_string(fSrcCX) + ", " + to_string(fSrcCY) + ")");
    for(int y = 0; y < dstH; y++)
    {
        //cout_indented(n_sp + 1, "y : " + to_string(y));
        float u = rowu;
        float v = rowv;
        //cout_indented(n_sp + 1, "(u, v) : (" + to_string(u));
        WDIBPIXEL *pDst = pDstBase + (dstDelta * y);
        for(int x = 0; x < dstW ; x++)
        {
            //cout_indented(n_sp + 2, "x : " + to_string(x));
            #if DEBUG_DRAW
            if ((int(u) == int(fSrcCX)) && (int(v) == int(fSrcCY)))
            {
                *pDst++ = DEBUG_MARK_COLOR;
                u += duRow;
                v += dvRow;
                continue;
            }
            #endif
            int sx = (int)u * n_channel;
            int sy = (int)v;
            //cout_indented(n_sp + 2, "(sx, sy) b4 : (" + to_string(sx) + ", " + to_string(sy) + ") / (" + to_string(srcW) + ", " + to_string(srcH) + ")");   exit(0);
            // Negative u/v adjustement
            // We need some additional proccessing for negative u and v values
            // value in range (-0.99..;0) should be mapped to last source pixel, not zero
            // Because zero source pixel already drawn at [0;0.99..)
            // (else we will observe double line of same colored pixels in when u/v flips from + to -)
            // Example: without shift u = -0.25 becimes sx=0, we need sx=-1, since we already had sx=0 at u=+0.25
            if(is_mosaicking)
            {
                if (u < 0)
                {
                // Negative u/v adjustement
                    for(int iC = 0; iC < n_channel; iC++) sx--;
                    sx = -sx % srcDelta; sx = srcDelta - sx;
                }
                sx %= srcDelta;
                if (v < 0)
                {
                    // Negative u/v adjustement
                    sy--;
                    sy = -sy % srcH; sy = srcH - sy; 
                }
                sy %= srcH;
            }
            else
            {
                if(!(0 <= u && u < srcW && 0 <= v && v < srcH)) 
                {
                    for(int iC = 0; iC < n_channel; iC++) pDst++;
                    u += duRow;
                    v += dvRow;
                    continue;
                }
            }
            //cout_indented(n_sp + 2, "(sx, sy) after : (" + to_string(sx) + ", " + to_string(sy) + ") / (" + to_string(srcW) + ", " + to_string(srcH) + ")");   exit(0);
            WDIBPIXEL *pSrc = pSrcBase + sx + (sy * srcDelta);
            for(int iC = 0; iC < n_channel; iC++)            
                *pDst++ = *pSrc++;
                //*pDst++ = *pSrc;
            u += duRow;
            v += dvRow;
        }
        rowu += duCol;
        rowv += dvCol;
    }
}


bool is_this_simple_float( float val )
{
    float times100_f = val * 100;
    int times100_i = int( times100_f );
    return 0 == float( times100_i ) - times100_f;
}



double compute_area_of_contour(const vector<Point>& li_pt, int n_sp)     
{
	cout_indented(n_sp, "compute_area_of_contour");                                                     
	return contourArea(li_pt);           
}

Point2f compute_center_of_contour(const vector<Point>& li_pt, int n_sp)   
{                                                                                                        
	 cout_indented(n_sp, "compute_center_of_countour"); 
	 const Point *pts = (const Point *) Mat(li_pt).data;
	 int n_pt = Mat(li_pt).rows;      
	 Rect bbox = boundingRect(li_pt);      
	 Mat im_blob = Mat::zeros(bbox.y + bbox.height + 2, bbox.x + bbox.width + 2, CV_8UC1);   
	 fillPoly(im_blob, &pts, &n_pt, 1, Scalar(255));       
	 Moments mom = moments(im_blob, true);  
	 return Point2f(mom.m10 / mom.m00, mom.m01 / mom.m00);
}	


float compute_remainder( float numerator, float denominator )
{
    float scale = 100000.0;
    return float( int( numerator * scale ) % int( denominator * scale ) ) / scale;
}



std::pair<cv::Mat, cv::Mat> split_homogeneous_transform_matrix_into_rotation_and_translation(const Mat& mat_homo)
{
	if(!(mat_homo.rows >= 3 && mat_homo.cols >= 3 && mat_homo.cols == mat_homo.rows))
	{
		std::cout << "The given matrix is NOT homogeneous transformation matrix." << std::endl; exit(0);
	}
	int dim_rot = mat_homo.rows - 1;
	cv::Mat mat_rot = mat_homo(cv::Rect(0, 0, dim_rot, dim_rot)).clone();
	cv::Mat vec_tra = mat_homo(cv::Rect(dim_rot, 0, 1, dim_rot)).clone();
	return std::pair<cv::Mat, cv::Mat>(mat_rot, vec_tra);
}


bool is_this_contour_circle_or_ellipse(RotatedRect& box, const vector<Point>& li_pt, const Size& sz, float th_dist_center, float th_dist_boundary, const Point2f *p_center, float area, int n_sp)
{
    cout_indented(n_sp, "is_this_contour_circle_or_ellipse"); //exit(0);
        Point2f p_cen = NULL == p_center ? compute_center_of_contour(li_pt, n_sp + 1) : *p_center;
            //RotatedRect box = fitEllipseDirect(li_pt);
                box = fitEllipseDirect(li_pt);
                    float dist = dist_two_points(p_cen, box.center);
                        float d_norm = dist / sqrt(box.size.width * box.size.width + box.size.height * box.size.height); 
                            cout_indented(n_sp + 1, "dist : " + to_string(dist) + ", d_norm : " + to_string(d_norm) + ", th_dist_center : " + to_string(th_dist_center));  //exit(0);
                                if(d_norm > th_dist_center) return false;
                                    Mat im_white(sz, CV_8UC1, Scalar(255)), im_black = Mat::zeros(sz, CV_8UC1), im_dist;
                                        
                                            vector<vector<Point> > li_li_pt = {li_pt}; 
                                                drawContours(im_black, li_li_pt, 0, Scalar(255), 1, 8); 
                                                    ellipse(im_white, box, Scalar(0), 1, 8);
                                                        //imwrite("im_white.bmp", im_white);  exit(0); 
                                                            distanceTransform(im_white, im_dist, DIST_L2, DIST_MASK_5);
                                                                print_mat_type(im_dist, n_sp + 1);
                                                                    print_matrix_min_max(im_dist, false, n_sp + 1);
                                                                        double minVal, maxVal, d_max_norm; Point minLoc, maxLoc;
                                                                            minMaxLoc(im_dist, &minVal, &maxVal, &minLoc, &maxLoc, im_black);
                                                                                cout_indented(n_sp + 1, "minVal : " + to_string(minVal) + ", maxVal : " + to_string(maxVal));   //exit(0);
                                                                                    float areea = area > 0 ? area : compute_area_of_contour(li_pt, n_sp + 1);
                                                                                        d_max_norm = maxVal / sqrt(areea);
                                                                                            cout_indented(n_sp + 1, "d_max_norm : " + to_string(d_max_norm) + " / " + to_string(th_dist_boundary));  //exit(0);
                                                                                                cout_indented(n_sp + 1, "box.size.width : " + to_string(box.size.width) + ", box.size.height : " + to_string(box.size.height));  //exit(0);
                                                                                                    float r_box_size = MAX(box.size.width, box.size.height) / MIN(box.size.width, box.size.height); 
                                                                                                        cout_indented(n_sp + 1, "r_box_size : " + to_string(r_box_size));  //exit(0);
                                                                                                            return d_max_norm < th_dist_boundary;
                                                                                                            }





//	Mat im_bgr = imread("im_bgr.bmp", CV_LOAD_IMAGE_COLOR);
//  Mat im_hls = cvtColor(im_bgr, im_hls, COLOR_BGR2HLS);
//	Mat hist_hls = get_histogram(im_hks

float compute_entropy(const Mat& hist_ori, int n_sp)               
{
    cout_indented(n_sp, "compute_entropy START");       
    //hist /= frame.total();                 
    Mat hist_norm, logP;    
    normalize(hist_ori, hist_norm, 1, 0, NORM_L1);   
    hist_norm += 1e-4; //prevent 0        
    cv::log(hist_norm, logP);         
    float entropy = -1 * sum(hist_norm.mul(logP)).val[0];    
    cout_indented(n_sp, "compute_entropy END");         
    return entropy;   
}                                  


//	vector<Point> li_pt(4);
//	li_pt[0] = Point(0, 0);	li_pt[1] = Point(100, 0);	li_pt[2] = Point(100, 100);	li_pt[3] = Point(0, 1000);
//	cout << contour_2_shape_name(li_pt, Mat(), -100) << endl;
//	=> square	

//#define TH_RATIO_RADIUS_DIF     0.12
#define TH_RATIO_RADIUS_CIRCLE	1.1
#define RATIO_RADIUS_PENTA      1.0 / cos(36.0 / 180.0 * CV_PI) 
#define MIN_RATIO_RADIUS_PENTA  RATIO_RADIUS_PENTA * 1.0 
#define MAX_RATIO_RADIUS_PENTA  RATIO_RADIUS_PENTA * 1.15
#define SQUARENESS_MIN          0.95
#define SQUARENESS_MAX          1.10
#define DIAMONDNESS_MIN		0.95	
#define DIAMONDNESS_MAX		1.05	
#define RECTNESS_MIN            0.95
#define RECTNESS_MAX            1.1
//#define ELLIPSENESS_MIN         0.95
//#define ELLIPSENESS_MAX         1.16
#define TH_RATIO_ISOSCLES_TRIANGLE 1.1
#define TH_RATIO_EQUILATERAL_TRIANGLE 1.1

tuple<string, Point2f, float> contour_2_shape(const vector<Point>& li_pt, const Size& sz, const Mat *im_mask, float th_d_center_ellipse, float th_d_boundary_ellipse, int n_sp)
{
    cout_indented(n_sp, "contour_2_shape_name");
    tuple<string, Point2f, float> tuple_shape_center_radius("some", Point2f(-1, -1), -1); 
    //string shape_name = "some";
	
	float area;
	Point2f p_center;  
    if(im_mask)
	{
		Moments mom = moments(*im_mask, true);
		p_center.x = mom.m10 / mom.m00;	p_center.y = mom.m01 / mom.m00;		
      	area = countNonZero(*im_mask);
	}
	else
	{
		p_center = compute_center_of_contour(li_pt, n_sp + 1);
		area = contourArea(li_pt);
	}
    
	float epsilon = arcLength(li_pt, true) * 0.02;
    vector<Point> li_pt_approx;
    approxPolyDP(li_pt, li_pt_approx, epsilon, true);
    int iP, n_pt = li_pt.size(), n_pt_approx = li_pt_approx.size();
    vector<float> li_d_center_boundary(n_pt);
    float rad_max = -1, rad_min = 100000000000000;
    for(iP = 0; iP < n_pt; iP++)
    {
        float dist = dist_two_points(p_center, li_pt[iP]);
        li_d_center_boundary[iP] = dist;
        if(dist > rad_max) rad_max = dist;
        if(dist < rad_min) rad_min = dist;
    }
    cout_indented(n_sp + 1, "n_pt_approx : " + to_string(n_pt_approx) + "\trad_max : " + to_string(rad_max) + "\trad_min : " + to_string(rad_min));
    float //rad_dif = rad_max - rad_min, 
        area_penta_rad_min = 5 * cos(deg2rad(54)) * rad_min * rad_min,
        area_penta_rad_max = 5 / tan(deg2rad(54)) * rad_max * rad_max;                                                      
    float //ratio_rad_dif = rad_dif / rad_max, 
        ratio_rad = rad_max / rad_min, 
        area_penta_max = MAX(area_penta_rad_min, area_penta_rad_max),
        area_penta_min = MIN(area_penta_rad_min, area_penta_rad_max), 
        squareness = area / (4.0 * rad_min * rad_min),
        rectness = area / (4.0 * rad_min * sqrt(rad_max * rad_max - rad_min * rad_min)),
        equilateral_triangleness = (area * sqrt(3)) / ((rad_max + rad_min) * (rad_max + rad_min)), 
        //ellipseness = area / (rad_max * rad_min * CV_PI),
        diamondness = (area * sqrt(rad_max * rad_max - rad_min * rad_min)) / (2.0 * rad_max * rad_max * rad_min);
    //cout_indented(n_sp + 1, "ratio_rad_dif : " + to_string(ratio_rad_dif) + " / " + to_string(TH_RATIO_RADIUS_DIF));
    cout_indented(n_sp + 1, "min penta : " + to_string(MIN_RATIO_RADIUS_PENTA) + " / ratio_rad : " + to_string(ratio_rad) + " / max penta : " + to_string(MAX_RATIO_RADIUS_PENTA));
    //cout_indented(n_sp + 1, "min : " + to_string(ELLIPSENESS_MIN) + " / ellipseness : " + to_string(ellipseness) + " / max : " + to_string(ELLIPSENESS_MAX));
    cout_indented(n_sp + 1, "min : " + to_string(SQUARENESS_MIN) + " / squareness : " + to_string(squareness) + " / max : " + to_string(SQUARENESS_MAX));
    cout_indented(n_sp + 1, "min : " + to_string(RECTNESS_MIN) + " / rectness : " + to_string(rectness) + " / max : " + to_string(RECTNESS_MAX));
    if(3 == n_pt_approx)
    {
        float d01 = norm(li_pt_approx[0] - li_pt_approx[1]), d12 = norm(li_pt_approx[1] - li_pt_approx[2]),
            d20 = norm(li_pt_approx[2] - li_pt_approx[0]);
        float d_max = MAX(d01, MAX(d12, d20)), d_min = MIN(d01, MIN(d12, d20));
        float ratio_max_min = d_max / d_min;
        cout_indented(n_sp + 1, "ratio_max_min : " + to_string(ratio_max_min) + " / " + to_string(TH_RATIO_EQUILATERAL_TRIANGLE));
        if(ratio_max_min < TH_RATIO_EQUILATERAL_TRIANGLE)
        {
            //shape_name = "triangle_equilateral";
            std::get<0>(tuple_shape_center_radius) = "triangle_equilateral";
            std::get<1>(tuple_shape_center_radius) = p_center;
            std::get<2>(tuple_shape_center_radius) = d_max;
        }
        else
        {
            float r_01_12 = MAX(d01, d12) / MIN(d01, d12), r_12_20 = MAX(d12, d20) / MIN(d12, d20), r_20_01 = MAX(d20, d01) / MIN(d20, d01);
            cout_indented(n_sp + 1, "r_01_12 : " + to_string(r_01_12) + ", r_12_20 : " + to_string(r_12_20) + ", r_20_01 : " + to_string(r_20_01) + " / " + to_string(TH_RATIO_EQUILATERAL_TRIANGLE));
            if(r_01_12 < TH_RATIO_ISOSCLES_TRIANGLE || r_12_20 < TH_RATIO_ISOSCLES_TRIANGLE || r_20_01 < TH_RATIO_ISOSCLES_TRIANGLE)
            {
                //shape_name = "triangle_isosceles";
                std::get<0>(tuple_shape_center_radius) = "triangle_isosceles";
                std::get<1>(tuple_shape_center_radius) = p_center;
                std::get<2>(tuple_shape_center_radius) = d_max;
            }
        }
    }
    else if(4 == n_pt_approx)
    {
        if(SQUARENESS_MIN < squareness && squareness < SQUARENESS_MAX)  
        {
            //shape_name = "square";
            std::get<0>(tuple_shape_center_radius) = "square";
            std::get<1>(tuple_shape_center_radius) = p_center;
            std::get<2>(tuple_shape_center_radius) = rad_max;
        }
        else if(RECTNESS_MIN < rectness && rectness < RECTNESS_MAX)
        {
            //shape_name = "rectangle";
            std::get<0>(tuple_shape_center_radius) = "rectangle";
            std::get<1>(tuple_shape_center_radius) = p_center;
            std::get<2>(tuple_shape_center_radius) = rad_max;
        }
        else if(DIAMONDNESS_MIN < diamondness && diamondness < DIAMONDNESS_MAX)
        //else if(0.95 < diamondness && diamondness < 1.05)
        {
            //shape_name = "diamond";
            std::get<0>(tuple_shape_center_radius) = "diamond";
            std::get<1>(tuple_shape_center_radius) = p_center;
            std::get<2>(tuple_shape_center_radius) = rad_max;
        }
    }
    else if(5 == n_pt_approx)
    {
        if(MIN_RATIO_RADIUS_PENTA < ratio_rad && ratio_rad < MAX_RATIO_RADIUS_PENTA)
        {
            //shape_name = "pentagon";
            std::get<0>(tuple_shape_center_radius) = "pentagon";
            std::get<1>(tuple_shape_center_radius) = p_center;
            std::get<2>(tuple_shape_center_radius) = rad_max;
        }
    }
    else// if(n_pt_approx > 7)
    {
        RotatedRect rbox;
        //if(ratio_rad_dif < TH_RATIO_RADIUS_DIF)
        if(ratio_rad < TH_RATIO_RADIUS_CIRCLE)
        {
            //shape_name = "circle";
            std::get<0>(tuple_shape_center_radius) = "circle";
            std::get<1>(tuple_shape_center_radius) = p_center;
            std::get<2>(tuple_shape_center_radius) = rad_max;
        }
        //else if(ELLIPSENESS_MIN < ellipseness && ellipseness < ELLIPSENESS_MAX)
        else if(is_this_contour_circle_or_ellipse(rbox, li_pt, sz, th_d_center_ellipse, th_d_boundary_ellipse, &p_center, area, n_sp + 1))
        {

            float r_box_size = MAX(rbox.size.width, rbox.size.height) / MIN(rbox.size.width, rbox.size.height);
            {
                //shape_name = "circle";
                std::get<0>(tuple_shape_center_radius) = r_box_size < TH_RATIO_RADIUS_CIRCLE ? "circle" : "ellipse";
                std::get<1>(tuple_shape_center_radius) = p_center;
                std::get<2>(tuple_shape_center_radius) = rad_max;
            }
        }
    }
    //cout_indented(n_sp + 1, shape_name);
    return tuple_shape_center_radius;
}



Mat mean_rotation_matrix_moakher(const std::vector<Mat> &vec_R)
{
    int n_rot = vec_R.size();
    Mat meanR = Mat::zeros(3, 3, CV_64F);
    for(size_t i = 0; i < vec_R.size(); i++) meanR += vec_R[i];
    meanR /= static_cast<double>(n_rot);
    // Euclidean mean of the rotation matrix following Moakher's method (SIAM 2002)
    //vpMatrix M, U, V;   vpColVector sv;
    //meanR.pseudoInverse(M, sv, 1e-6, U, V);
    Mat M, U, V, sv, kerA;
    pseudo_inverse(meanR, M, sv, 1e-6, U, V, kerA);
    //double det = sv[0]*sv[1]*sv[2];
    double det = sv.at<double>(0) * sv.at<double>(1) * sv.at<double>(2);
    if(det > 0) {
        meanR = U * V.t();
    }
    else {
        //vpMatrix D(3, 3);   D = 0.0;    D[0][0] = D[1][1] = 1.0; D[2][2] = -1;
        Mat D = Mat::eye(3, 3, CV_64F); D.at<double>(2, 2) = -1;
        meanR = U * D * V.t();
    }
    //R = meanR;
    //return R;
    return meanR;
}


Mat mean_traslation_vector(const std::vector<Mat> li_tra)
{
    int iT, n_tra = li_tra.size();
    Mat meanT = li_tra[0].clone();
    for(iT = 1; iT < n_tra; iT++)
    {
        meanT += li_tra[iT];
    }
    meanT /= n_tra;
    return meanT;
}



Mat merge_mask(const vector<Mat>& li_mask, vector<int> li_idx, int n_sp)
{
    cout_indented(n_sp, "merge_mask");
    Mat im_mask;
    int iM, n_mask = li_idx.size();
    for(iM = 0; iM < n_mask; iM++)
    {
        int idx = li_idx[iM];
        if(0 == iM) im_mask = li_mask[idx];
        else bitwise_or(im_mask, li_mask[idx], im_mask); 
        //cout_indented(n_sp + 1, "idx : " + to_string(idx));
        //cout_indented(n_sp + 2, "countNonZero(li_mask[idx]) : " + to_string(countNonZero(li_mask[idx])));
        //cout_indented(n_sp + 2, "countNonZero(im_mask) : " + to_string(countNonZero(im_mask)));
    }
    return im_mask;
}





Mat get_hsv_histogram(const Mat& im_hsv, const Mat& im_mask, int n_sp)
{
    cout_indented(n_sp, "get_hsv_histogram");
    Mat hist_hsv;
    int hbins = 50, sbins = 32, vbins = 10, channels[] = {0,  1, 2};
    int histSize[] = {hbins, sbins, vbins}; 
    float hranges[] = { 0, 180 }, sranges[] = { 0, 255 }, vranges[] = {0, 255};
    const float* ranges[] = { hranges, sranges, vranges}; 
    //cout_indented(n_sp + 1, "countNonZero(im_mask) : " + to_string(countNonZero(im_mask)));
    calcHist(&im_hsv, 1, channels, im_mask, hist_hsv, 3, histSize, ranges, true, false);
    //cout_indented(n_sp + 1, "b4 countNonZero(hist_hsv) : " + to_string(countNonZero(hist_hsv)));
    normalize(hist_hsv, hist_hsv, 1, 0, cv::NORM_L1);
    //cout_indented(n_sp + 1, "after countNonZero(hist_hsv) : " + to_string(countNonZero(hist_hsv)));
    return hist_hsv;
}

Mat get_hls_histogram(const Mat& im_hls, const Mat& im_mask, int n_sp)
{
    cout_indented(n_sp, "get_hls_histogram");
    Mat hist_hls;
    int hbins = 50, lbins = 10, sbins = 32, channels[] = {0, 1, 2};
    int histSize[] = {hbins, lbins, sbins}; 
    float hranges[] = { 0, 180 }, sranges[] = { 0, 255 }, lranges[] = {0, 255};
    const float* ranges[] = { hranges, lranges, sranges}; 
    //cout_indented(n_sp + 1, "countNonZero(im_mask) : " + to_string(countNonZero(im_mask)));
    calcHist(&im_hls, 1, channels, im_mask, hist_hls, 3, histSize, ranges, true, false);
    //cout_indented(n_sp + 1, "b4 countNonZero(hist_hls) : " + to_string(countNonZero(hist_hls)));
    normalize(hist_hls, hist_hls, 1, 0, cv::NORM_L1);
    //cout_indented(n_sp + 1, "after countNonZero(hist_hls) : " + to_string(countNonZero(hist_hls)));
    return hist_hls;
}

Mat get_histogram(const Mat& im_hsv_or_hls, const Mat& im_mask, bool is_hsv, int n_sp)
{
    return is_hsv ? get_hsv_histogram(im_hsv_or_hls, im_mask, n_sp) : get_hls_histogram(im_hsv_or_hls, im_mask, n_sp);
}


//	Mat mat = Mat::zeros(100, 10, CV_8UC3);
//	cout << mat_type_2_str(mat.type(), -100) << endl;
//	=> 8UC3	

string mat_type_2_str(int type, int n_sp) 
{
	cout_indented(n_sp, "mat_type_2_str");
  	string r;
  	uchar depth = type & CV_MAT_DEPTH_MASK;
  	uchar chans = 1 + (type >> CV_CN_SHIFT);
  	switch ( depth ) {
    	case CV_8U:  r = "8U"; break;
    	case CV_8S:  r = "8S"; break;
    	case CV_16U: r = "16U"; break;
    	case CV_16S: r = "16S"; break;
    	case CV_32S: r = "32S"; break;
    	case CV_32F: r = "32F"; break;
    	case CV_64F: r = "64F"; break;
    	default:     r = "User"; break;
  	}
  	r += "C";
  	r += (chans + '0');
  	return r;
}



//	Mat im_bgr = imread("im_bgr.bmp" CV_LOAD_IMAGE_COLOR);
//	Mat mat_norm = mat_norm_channel_wise(im_bgr, NORM_L2);

template<typename T> 
Mat mat_norm_channel_wise(const Mat& mat, int norm_type)
{
    Mat mat_norm(mat.size(), CV_64FC1);
	int n_c = mat.channels();	
    if(2 == n_c)
    {
        for(int iR = 0; iR < mat.rows; iR++)
        {
            for(int iC = 0; iC < mat.cols; iC++)
            {
                mat_norm.at<double>(iR, iC) = norm(mat.at<Vec<T, 2> >(iR, iC), norm_type);
            }
        }
    } 
    else if(3 == n_c)
    {
        for(int iR = 0; iR < mat.rows; iR++)
        {
            for(int iC = 0; iC < mat.cols; iC++)
            {
                mat_norm.at<double>(iR, iC) = norm(mat.at<Vec<T, 3> >(iR, iC), norm_type);
            }
        }
    } 
    else if(4 == n_c)
    {
        for(int iR = 0; iR < mat.rows; iR++)
        {
            for(int iC = 0; iC < mat.cols; iC++)
            {
                mat_norm.at<double>(iR, iC) = norm(mat.at<Vec<T, 4> >(iR, iC), norm_type);
            }
        }
    }  
    else if(5 == n_c)
    {
        for(int iR = 0; iR < mat.rows; iR++)
        {
            for(int iC = 0; iC < mat.cols; iC++)
            {
                mat_norm.at<double>(iR, iC) = norm(mat.at<Vec<T, 5> >(iR, iC), norm_type);
            }
        }
    }  
    else if(6 == n_c)
    {
        for(int iR = 0; iR < mat.rows; iR++)
        {
            for(int iC = 0; iC < mat.cols; iC++)
            {
                mat_norm.at<double>(iR, iC) = norm(mat.at<Vec<T, 6> >(iR, iC), norm_type);
            }
        }
    }   
    else if(7 == n_c)
    {
        for(int iR = 0; iR < mat.rows; iR++)
        {
            for(int iC = 0; iC < mat.cols; iC++)
            {
                mat_norm.at<double>(iR, iC) = norm(mat.at<Vec<T, 7> >(iR, iC), norm_type);
            }
        }
    }  
    else if(8 == n_c)
    {
        for(int iR = 0; iR < mat.rows; iR++)
        {
            for(int iC = 0; iC < mat.cols; iC++)
            {
                mat_norm.at<double>(iR, iC) = norm(mat.at<Vec<T, 8> >(iR, iC), norm_type);
            }
        }
    }      
    else if(9 == n_c)
    {
        for(int iR = 0; iR < mat.rows; iR++)
        {
            for(int iC = 0; iC < mat.cols; iC++)
            {
                mat_norm.at<double>(iR, iC) = norm(mat.at<Vec<T, 9> >(iR, iC), norm_type);
            }
        }
    }
    return mat_norm;    
}


//	Point2f p_center(10, 20);
//	float c = cos(deg2rad(60)), s = sin(deg2rad(60));
//	float rot_mat[] = {	c,  -s, -p_center.x * c + p_center.y * s + p_center.x, 
//        			s,  c,  -p_center.x * s - p_center.y * c + p_center.y,
//			        0,  0,  1
//	};
//	Mat mat_rot = init_mat<float>(3, 3, rot_mat, 0);
//	Mat mat_norm = get_row_or_column_or_channel_wise_norm(mat_rot, "row", NORM_L2, 0);

Mat get_row_or_column_or_channel_wise_norm(const Mat& mat, const string& str, int norm_type, int n_sp)
{
    cout_indented(n_sp, "get_row_or_column_or_channel_wise_norm START");
    Mat mat_norm;//(mat.rows, 1, CV_64FC1);
    if("row" == str)
    {
        mat_norm.create(mat.rows, 1, CV_64FC1);
        for(int iR = 0; iR < mat.rows; iR++) mat_norm.at<double>(iR) = norm(mat.row(iR), norm_type); 
    }
    else if("column" == str)
    {
        mat_norm.create(1, mat.cols, CV_64FC1);
        for(int iC = 0; iC < mat.cols; iC++) mat_norm.at<double>(iC) = norm(mat.col(iC), norm_type); 
    }
    else if("channel" == str)
    {
        int n_c = mat.channels();
        //typedef Vec<float, n_c> veec;
        if(CV_8U == mat.depth() || CV_16U == mat.depth()) mat_norm = mat.clone();
        else if(1 == n_c) mat_norm = cv::abs(mat);
        else
        {
            //mat_norm.create(mat.size(), CV_64FC1);
            if(CV_8S == mat.depth()) mat_norm = mat_norm_channel_wise<schar>(mat, norm_type); 
            else if(CV_16S == mat.depth()) mat_norm = mat_norm_channel_wise<short>(mat, norm_type); 
            else if(CV_32S == mat.depth()) mat_norm = mat_norm_channel_wise<int>(mat, norm_type); 
            else if(CV_32F == mat.depth()) mat_norm = mat_norm_channel_wise<float>(mat, norm_type); 
            else if(CV_64F == mat.depth()) mat_norm = mat_norm_channel_wise<double>(mat, norm_type); 
        }
    }
    cout_indented(n_sp, "get_row_or_column_or_channel_wise_norm END");
    return mat_norm;
}



//	Point2f p_center(10, 20);
//	float c = cos(deg2rad(60)), s = sin(deg2rad(60));
//	float rot_mat[] = {	c,  -s, -p_center.x * c + p_center.y * s + p_center.x, 
//        			s,  c,  -p_center.x * s - p_center.y * c + p_center.y,
//			        0,  0,  1
//	};
//	Mat mat_rot = init_mat_with_array_of_values<float>(3, 3, rot_mat, 0);

template <typename T> 
Mat init_mat_with_array_of_values(int n_r, int n_c, T li_val[], int n_sp)
{
    cout_indented(n_sp, "init_mat START");
    Mat_<T> mat(n_r, n_c, li_val);
#if 0 
	int iR, iE, iC, n_elem = n_r * n_c;
    Mat_<T> mat(n_r, n_c);
    for(iR = 0, iE = 0; iR < n_r; iR++)
    {
        for(iC = 0; iC < n_c; iC++, iE++)
        {
            mat(iR, iC) = li_val[iE];
        }      
    }
#endif	// 0	
    cout_indented(n_sp, "init_mat END");
    return mat;
}



void cout_mat_indented(const Mat& mat, const string& str_mat_name, int n_sp)
{
    cout_indented(n_sp, "cout_mat_indented START");
    if(1 == mat.channels()) cout_mat_2d_indented(mat, str_mat_name, n_sp + 1);
    else cout_mat_3d_indented(mat, str_mat_name, n_sp + 1);
    cout_indented(n_sp, "cout_mat_indented END");
}

void cout_mat_2d_indented(const Mat& mat, const string& str_mat_name, int n_sp)
{
    if(str_mat_name.empty()) n_sp--;
    else cout_indented(n_sp, str_mat_name + " =");
    cout_indented(n_sp, "[");
    for(int iR = 0; iR < mat.rows; iR++)
    {
        stringstream ss;    ss << mat.row(iR);
        cout_indented(n_sp + 1, ss.str());
    }
    cout_indented(n_sp, "]");
    return;
}

void cout_mat_3d_indented(const Mat& mat, const string& str_mat_name, int n_sp)
{
    if(str_mat_name.empty()) n_sp--;
    else cout_indented(n_sp, str_mat_name + " =");
    int iC, n_ch = mat.channels();
    vector<Mat> li_mat(n_ch);
    split(mat, li_mat);
    cout_indented(n_sp, "[");
    for(int iC = 0; iC < n_ch; iC++)
    {
        cout_mat_3d_indented(li_mat[iC], "", n_sp + 1);
    }
    cout_indented(n_sp, "]");
    return;
}


//	Mat mat = Mat::zeros(100, 10, CV_8UC3);
//	print_mat_type(mat, 0);
//	=> mat type : 8UC3	

void cout_mat_type_indented(const Mat& mat, int n_sp)
{
	cout_indented(n_sp, "cout_mat_type_indented START");
	cout_indented(n_sp + 1, "mat type : " + mat_type_2_str(mat.type(), n_sp + 1)); 		
	cout_indented(n_sp, "cout_mat_type_indented END");
}

//	Mat mat = Mat::zeros(100, 10, CV_8UC1);
//	mat.at<uchar>(10, 20) = 150;
//	print_matrix_min_max(mat, true, 0);
//	=> min : 0 at (0, 0),	max : 150 at (20, 10)
//	print_matrix_min_max(mat, false, 0);
//	=> min : 0,	max : 150

void print_matrix_min_max(const Mat& mat, bool with_loc, int n_sp)
{
	cout_indented(n_sp, "print_matrix_min_max");
	double minVal, maxVal;
	stringstream ss;
	if(with_loc) 
	{
		Point minLoc, maxLoc;
		minMaxLoc(mat, &minVal, &maxVal, &minLoc, &maxLoc);
		ss << "min : " << minVal << "at (" << minLoc.x << ", " << minLoc.y << "),\tmax : " << maxVal << "at (" << maxLoc.x << ", " << maxLoc.y << ")";
	}
	else
	{
		minMaxLoc(mat, &minVal, &maxVal);
		ss << "min : " << minVal << ",\tmax : " << maxVal;
	}
	cout_indented(n_sp + 1, ss.str());					
}

//	Point2f p0(10, 20), p1(20, 20), p2(20, 10);
//	Point2f d_01 = p0 - p1, d_21 = p2 - p1;
//	float deg_01 = rad2deg(atan2(d_01.y, d_01.x)), deg_21 = rad2deg(atan2(d_21.y, d_21.x));
//	float x_01 = -compute_offset_for_puttext(deg_01, 180, 0, MAX_OFFSET_X, 0), 
//		y_01 = compute_offset_for_puttext(deg_01, 90, -90, MAX_OFFSET_Y, 0),
//		x_21 = -compute_offset_for_puttext(deg_21, 180, 0, MAX_OFFSET_X, 0), 
//		y_21 = compute_offset_for_puttext(deg_21, 90, -90, MAX_OFFSET_Y, 0);
//	p0.x += x_01;	p0.y += y_01;	p2.x += x_21;	p2.y += y_21;
float compute_offset_for_puttext(float deg, float max_deg, float min_deg, float max_offset, float min_offset)
{
     float dif_deg = fabs(min_deg - max_deg), scale_output = 0.5 * (max_offset - min_offset);
     float scale_input = 180.0 / dif_deg;
     float deg_modified = scale_input * (deg - max_deg);
     float rad_modified = deg_modified * CV_PI / 180.0 ;
     return scale_output * (1.0 + cos(rad_modified)) + min_offset;
}


float dist_two_points(const Point2f& p1, const Point2f& p2)
{
	return cv::norm(p1 - p2);
}

//------------ draw (circular) arc around 'p_center' and from 'p_1' to 'p_2' --------------
float draw_arc(Mat& im_bgr, const Point2f& p_center, const Point2f& p_1, const Point2f& p_2, const Scalar& kolor)
{
    float rad1 = norm(p_center - p_1), rad2 = norm(p_center - p_2);
    float radius = 0.5 * (rad1 + rad2);
    float x_dif_1 = p_1.x - p_center.x, y_dif_1 = p_1.y - p_center.y, x_dif_2 = p_2.x - p_center.x, y_dif_2 = p_2.y - p_center.y;
    float ang_rad_start, ang_rad_end, ang_rad_1 = atan2(y_dif_1, x_dif_1), ang_rad_2 = atan2(y_dif_2, x_dif_2);
    if(ang_rad_1 < ang_rad_2)
    {
        ang_rad_start = ang_rad_1;  ang_rad_end = ang_rad_2;
    }
    else
    {
        ang_rad_end = ang_rad_1;  ang_rad_start = ang_rad_2;
    }     
    ang_rad_end = unwrap(ang_rad_start, ang_rad_end);
    float ang_rad = ang_rad_end - ang_rad_start;
    float ang_deg = rad2deg(ang_rad);  
    ellipse(im_bgr, p_center, Size(radius, radius), 0, rad2deg(ang_rad_start), rad2deg(ang_rad_end), kolor); 
    circle(im_bgr, p_1, 1, CV_RGB(255, 0, 0), 2);   circle(im_bgr, p_2, 1, CV_RGB(0, 255, 0), 2); 
    //namedWindow("arc", WINDOW_NORMAL);  imshow("arc", im_bgr);  waitKey(1);  //exit(0); 
    return ang_deg;  
}

//------------ rotate 1st point around 2nd point by 3rd radian --------------
//	Point2f p_rotated, p1, p2, deg;
//	p1.x = 100;	p1.y = 100;	p2.x = 200;	p2.y = 100;	deg = 90;
//	p_rotated = rotate_1st_around_2nd_by_3rd_radian(p1, p2, deg2rad(deg));
//	cout << p1 << " -> " << deg << " deg -> " << p_rotated << endl;
//	=> [100, 100] -> 90 deg -> [200, 0]
//	p1.x = 100;	p1.y = 100;	p2.x = 200;	p2.y = 100;	deg = 180;
//	p_rotated = rotate_1st_around_2nd_by_3rd_radian(p1, p2, deg2rad(deg));
//	cout << p1 << " -> " << deg << " deg -> " << p_rotated << endl;
//	=> [100, 100] -> 180 deg -> [300, 100] 
#include <complex>
Point2f rotate_1st_around_2nd_by_3rd_radian(const Point2f& p1, const Point2f& p2, float rad)
{
    complex<float> P_rotated, P(p1.x, p1.y), Q(p2.x, p2.y);
    P_rotated = (P - Q) * polar(float(1), rad) + Q;
    return Point2f(P_rotated.real(), P_rotated.imag());
}



//------------ draw pencils of lines radiating from 'p_rot_center' and passing thru 'p_one_of_pencil'. -------------- 
//------------ The lines form a rotation symmetry of angle 'deg'. --------------
//	Mat im_bgr;
//	Point p_rot_center(100, 100), p_one_of_pencil(100, 200);
//	float deg = 72;
//	draw_rotation_pencil(im_bgr, p_rot_center, p_one_of_pencil, deg)
//	=> 5 lines radiating from (100, 100) and 77 deg rotated from each other are added to 'im_bgr'. 
void draw_rotation_pencil(Mat& im_bgr, const Point& p_rot_center, const Point2f& p_one_of_pencil, float deg,
    const Scalar& color_start, const Scalar& color_others)
{
    int iR, n_rot = cvRound(360.0 / deg);
    for(iR = 0; iR < n_rot; iR++)
    {
        Point2f p_rotated;
        if(iR)
        {
            float rad = deg2rad(deg * float(iR));
            p_rotated = rotate_1st_around_2nd_by_3rd_radian(p_one_of_pencil, p_rot_center, rad);
        }
        else
        {
            p_rotated = p_one_of_pencil;
        }
       
        Point2f p_boundary = get_boundary_point_of_1st_radiated_from_2nd(p_rotated, p_rot_center, im_bgr.cols, im_bgr.rows);
        line(im_bgr, p_rot_center, p_boundary, iR ? color_others : color_start, 1); 
    }
    return;
}


//------------ draw key point match --------------
void draw_match(const Mat& im_gray, const vector<KeyPoint>& li_kp, const vector<DMatch>& li_match)
{
    Mat im_bgr_match;
    int n_match = li_match.size(), n_kp = li_kp.size(), iP, iM;
    for(iP = 0; iP < n_kp; iP++)
    {
        vector<DMatch> li_match_each;
        for(iM = 0; iM < n_match; iM++)
        {
            int idx = li_match[iM].queryIdx;
            if(iP == idx) li_match_each.push_back(li_match[iM]);
        }
        int n_match_each = li_match_each.size();
        if(n_match_each)
        {
            drawMatches(im_gray, li_kp, im_gray, li_kp, li_match_each, im_bgr_match);
            //namedWindow(to_string(iP), WINDOW_NORMAL); imshow(to_string(iP), im_bgr_match);   waitKey(1);
        }     
    }
    return;
}    

//------------ detect key points from gray image --------------
//	using namespace cv;
//	Mat im_gray = imread("img.bmp", CV_LOAD_IMAGE_GRAYSCALE);
//	Ptr<FeatureDetector> detector = ORB::create()
//	vector<KeyPoint> li_kp = detect_keypoint(im_gray, detector);
//	for(int iK = 0; iK < li_kp.size(); iK++) cout << li_kp[iK].pt << ", "; cout << endl;
//	=> [x1, y1], [x2, y2], ....... , [xn, yn]
vector<KeyPoint> detect_keypoint(const Mat& im_gray, const Ptr<FeatureDetector>& detector)
{
    vector<KeyPoint> li_kp;
    detector->detect(im_gray, li_kp);
    return li_kp;
}


//------------ compute feature descriptor the list of given key points --------------
//	using namespace cv;
//	Mat im_gray = imread("img.bmp", CV_LOAD_IMAGE_GRAYSCALE);
//	Ptr<FeatureDetector> detector = ORB::create();
//	vector<KeyPoint> li_kp = detect_keypoint(im_gray, detector);
//	Ptr<DescriptorExtractor> desc = ORB::create();
//	Mat mat_feature = compute_descriptor(im_gray, li_kp, desc);
//	cout << "li_kp.size() : " << li_kp.size << endl; 
//	=> 80
//	cout << "mat_feature.size() : " << mat_feature.size() << endl; 
//	=> [80, 128]
Mat compute_descriptor(const Mat& im_gray, vector<KeyPoint>& li_kp, const Ptr<DescriptorExtractor>& desc)
{
    Mat mat_desc;
    desc->compute(im_gray, li_kp, mat_desc);
    return mat_desc; 
}




//------------ find match between the intra members of the key point list.  Of course, the match to the self is not allowed.
vector<DMatch> match_intra(const Mat& desc, const vector<KeyPoint>& li_kp, const Ptr<DescriptorMatcher>& matcher, 
    int n_naver, unsigned int kMaxMatchingSize, float th_dist_match, float th_dist_pxl) 
{
    vector<DMatch> li_match;  
    vector< vector<DMatch> > vmatches;
    matcher->knnMatch(desc, desc, vmatches, n_naver);
    for (int i = 0; i < static_cast<int>(vmatches.size()); ++i) 
    {
        int iM, n_match = vmatches[i].size(); 
        for(iM = 0; iM < n_match; iM++)
        {
            int idx1 = vmatches[i][iM].trainIdx, idx2 = vmatches[i][iM].queryIdx;
            if(idx1 <= idx2) continue;
            float dist = cv::norm(li_kp[idx1].pt - li_kp[idx2].pt);
            if(dist < th_dist_pxl) continue;
            li_match.push_back(vmatches[i][iM]);
        }     
    }
    std::sort(li_match.begin(), li_match.end());
    while (th_dist_match < li_match.back().distance) {
        li_match.pop_back();
    }
    while (li_match.size() > kMaxMatchingSize) {
        li_match.pop_back();
    }
    return li_match;
}




//------------ find the position where a line radiatated from 2nd point and passing thru 1st point intersect the image boundary -------------- 
//	Point2f p_boundary, p1, p2;
//	int width = 600, height = 400;
//	p1.x = 150;	p1.y = 100;	p2.x = 300;	p2.y = 200;
//	p_boundary = get_boundary_point_of_1st_radiated_from_2nd(p1, p2, width, height);
//	cout << p_boundary << endl;
//	=> [0, 0]
//	p1.x = 400;	p1.y = 300;	p2.x = 100;	p2.y = 100;
//	p_boundary = get_boundary_point_of_1st_radiated_from_2nd(p1, p2, width, height);
//	cout << p_boundary << endl;
//	=> [550, 400]
Point2f get_boundary_point_of_1st_radiated_from_2nd(const Point2f& p1, const Point2f& p2, int width, int height)
{
    Point2f p_boundary(-1, -1);
    float dx = p1.x - p2.x, dy = p1.y - p2.y;
    if(0 == dx && 0 == dy) return p_boundary;
    float dx_boundary = dx > 0 ? float(width) - p2.x : (0 > dx ? -p2.x : 0.0),
        dy_boundary = dy > 0 ? float(height) - p2.y : (0 > dy ? -p2.y : 0.0);
    cout << "dx : " << dx << ", dy : " << dy << endl;  // exit(0);
    cout << "dx_boundary : " << dx_boundary << ", dy_boundary : " << dy_boundary << endl;   //exit(0);
    if(0 == dx)
    {
        p_boundary.x = p2.x;    p_boundary.y = dy > 0 ? float(height) : 0.0;
    }
    else if(0 == dy)
    {
        p_boundary.y = p2.y;    p_boundary.x = dx > 0 ? float(width) : 0.0;
    }
    else
    {
        float ratio_x = dx_boundary / dx, ratio_y = dy_boundary / dy;
        if(ratio_x > ratio_y)
        {
            p_boundary.x = ratio_y * dx + p2.x; p_boundary.y = dy > 0 ? height : 0;
        }
        else
        {
            p_boundary.y = ratio_x * dy + p2.y; p_boundary.x = dx > 0 ? width : 0;
        }
    }
    return p_boundary;
}


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


// Checks if a matrix is a valid rotation matrix.
bool is_rotation_matrix(const cv::Mat &R)
{
    cv::Mat Rt;
    cv::transpose(R, Rt);
    cv::Mat shouldBeIdentity = Rt * R;
    cv::Mat I = Mat::eye(3, 3, shouldBeIdentity.type());    
    return  cv::norm(I, shouldBeIdentity) < 1e-6;    
}



//------------ Rotatate an image by a given degrees either with resizing or not	--------------  
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
	//Mat im_bin0255_circle = Mat::zeros(im_bin0255_inside_circle.size(), im_bin0255_inside_circle.type());
	Mat im_bin0255_circle = zeros_like(im_bin0255_inside_circle);
	float radius = MIN(im_bin0255_inside_circle.rows * 0.5 - 2, im_bin0255_inside_circle.cols * 0.5 - 2);
	circle(im_bin0255_circle, p_center, radius, Scalar(255, 255, 255), -1);
	Mat im_bin0255_inside_circle_wo_circle;
	im_bin0255_inside_circle.copyTo(im_bin0255_inside_circle_wo_circle, im_bin0255_circle);
	//show_image("im_bin0255_inside_circle", im_bin0255_inside_circle);
	//show_image("im_bin0255_inside_circle_wo_circle", im_bin0255_inside_circle_wo_circle);
	//waitKey();  //exit(0);
	return im_bin0255_inside_circle_wo_circle;
}




//#include <numeric>
template <typename T, typename Compare>
std::vector<std::size_t> sort_permutation(
    const std::vector<T>& vec,
    Compare compare)
{
    std::vector<std::size_t> p(vec.size());
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(),
        [&](std::size_t i, std::size_t j){ return compare(vec[i], vec[j]); });
    return p;
}


template <typename T>
void apply_permutation_in_place(
    std::vector<T>& vec,
    const std::vector<std::size_t>& p)
{
    std::vector<bool> done(vec.size());
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        if (done[i])
        {
            continue;
        }
        done[i] = true;
        std::size_t prev_j = i;
        std::size_t j = p[i];
        while (i != j)
        {
            std::swap(vec[prev_j], vec[j]);
            done[j] = true;
            prev_j = j;
            j = p[j];
        }
    }
}


//-----------------------------------------------------------------------------------------------------  
//	vector<int> li_int({4, 1, 3, 2});
//	vector<string> li_string({"aa", "bb", "cc", "dd"});
//	sort_two_seqs_as_first_seq_sorted(li_int, li_string, true);
//	=> li_int : 1, 2, 3, 4 and li_string : "bb", "dd", "cc", "aa" 
//	sort_two_seqs_as_first_seq_sorted(li_int, li_string, false);
//	=> li_int : 4, 3, 2, 1 and li_string : "aa", "cc", "dd", "bb"  
template<typename T>	
void sort_two_seqs_as_first_seq_sorted(vector<int>& li_int, vector<T>& li_string, bool is_descending)
{
	//auto p = sort_permutation(li_int, [](int const& a, int const& b) {return is_descending ? a < b : a > b;});
	auto p = sort_permutation(li_int, [&is_descending](int const& a, int const& b) {return is_descending ? a < b : a > b;});
	//auto p = sort_permutation(li_int, [](int const& a, int const& b) {return a < b;});
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
	

void compute_pseudo_inverse(const Mat &a, const Mat &sv, const Mat &v, unsigned int nrows, unsigned int ncols, unsigned int nrows_orig, unsigned int ncols_orig, double svThreshold, Mat &Ap, unsigned int &rank)
{
    Mat a1 = Mat::zeros(ncols, nrows, a.type());
    // compute the highest singular value and the rank of h
    double maxsv = 0;
    for (unsigned int i = 0; i < ncols; i++) {
        double sv_abs = fabs(sv.at<double>(i));
        if(sv_abs > maxsv) maxsv = sv_abs;
    }
    rank = 0;
    for (unsigned int i = 0; i < ncols; i++) {
        if(fabs(sv.at<double>(i)) > maxsv * svThreshold) rank++;
        for(unsigned int j = 0; j < nrows; j++) {
            for (unsigned int k = 0; k < ncols; k++) {
                if(fabs(sv.at<double>(k)) > maxsv * svThreshold) {
                    a1.at<double>(i, j) += v.at<double>(i, k) * a.at<double>(j, k) / sv.at<double>(k);
                }
            }
        }
    }
    Ap = nrows_orig >= ncols_orig ? a1 : a1.t();
    return;
}

void compute_pseudo_inverse(const Mat &U, const Mat &sv, const Mat &V, unsigned int nrows_orig, unsigned int ncols_orig, double svThreshold, Mat &Ap, unsigned int &rank, Mat &imA, Mat &imAt, Mat &kerAt)
{
    Ap = Mat::zeros(ncols_orig, nrows_orig, CV_64F);
    // compute the highest singular value and the rank of h
    double maxsv = sv.at<double>(0);
    rank = 0;
    for(unsigned int i = 0; i < ncols_orig; i++) {
        if(fabs(sv.at<double>(i)) > maxsv * svThreshold) {
            rank++;
        }
        for(unsigned int j = 0; j < nrows_orig; j++) {
            for(unsigned int k = 0; k < ncols_orig; k++) {
                double sv_k = sv.at<double>(k);
                if(fabs(sv_k) > maxsv * svThreshold) {
                    Ap.at<double>(i, j) += V.at<double>(i, k) * U.at<double>(j, k) / sv_k;
                }
            }
        }
    }
    // Compute im(A) and im(At)
    U(Rect(0, 0, rank, nrows_orig)).copyTo(imA);  
    V(Rect(0, 0, rank, ncols_orig)).copyTo(imAt);  
    if(rank != ncols_orig) {
        kerAt = Mat::zeros(ncols_orig - rank, ncols_orig, CV_64F);
        for (unsigned int j = 0, k = 0; j < ncols_orig; j++) {
            if(fabs(sv.at<double>(j)) <= maxsv * svThreshold) {
                double sos = sum_of_squared(V.col(j)); 
                if(sos > std::numeric_limits<double>::epsilon())
                {
                    for(unsigned int i = 0; i < V.rows; i++) {
                        kerAt.at<double>(k, i) = V.at<double>(i, j);
                    }
                    k++;
                }
            }
        }
    }     
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
							      int hori_minus_vert_plus, int neg_left_or_top_0_center_pos_right_or_bottom,
							      float factor_margin, const Scalar& color_margin,
							      bool save_as_video, const string& dir_save)
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
			//im_cur = concatenate_images(im_cur, imread(fn, cv_read_flag), hori_minus_vert_plus);
			im_cur = concatenate_images(im_cur, imread(fn, cv_read_flag), hori_minus_vert_plus, neg_left_or_top_0_center_pos_right_or_bottom, 
						    factor_margin, color_margin)	

		}
         	if(save_as_video) vw = write_one_frame_to_video(vw, im_cur, 0 == iF, path_vid, 30, 1000);
		else save_one_image_under_directory(im_cur, dir_save, "comparision_");
		iF++;
	}
	if(save_as_video) { cout << "concatenated video has just saved at : " << path_vid << endl;  vw.release(); }
}



void concatenate_images_from_seqeunces_into_video_or_sequence(vector< vector<string> >& li_li_path, 
							      int hori_minus_vert_plus, int neg_left_or_top_0_center_pos_right_or_bottom,
							      float factor_margin, const Scalar& color_margin, 
                                  int neg_vid_0_seq_pos_gif, const string& dir_save)
{
	vector<vector<int> > li_li_id = get_list_of_list_of_ids_as_number(li_li_path);
	for(int iS = 0; iS < li_li_id.size(); iS++) sort_two_seqs_as_first_seq_sorted(li_li_id[iS], li_li_path[iS], true);
	bool is_gray = are_all_seqs_gray(li_li_path);
	int /*w_concat, h_concat,*/ iF = 0, n_seq = li_li_path.size(), n_frm = -1, cv_read_flag = is_gray ? CV_LOAD_IMAGE_GRAYSCALE : CV_LOAD_IMAGE_COLOR;
	if (n_seq > 0) n_frm = li_li_path[0].size();
    vector<int> li_idx(n_seq, -1);
	VideoWriter vw;
	string path_vid_or_gif; //= python_join_equivalent(dir_save, "output.avi");
    //GifWriter writer = {};
    if(0 > neg_vid_0_seq_pos_gif)
    {
        //path_vid_or_gif = python_join_equivalent(dir_save, "output.mp4");
        path_vid_or_gif = python_join_equivalent(dir_save, "output.avi");
    }
    else if(0 < neg_vid_0_seq_pos_gif)
    {
        //path_vid_or_gif = python_join_equivalent(dir_save, "output.gif");
        path_vid_or_gif = python_join_equivalent(dir_save, "output.webp");
    }

	//mkdir_if_not_exist(dir_save.c_str());
    mkdirs(dir_save.c_str());
    while(get_next_index(li_idx, li_li_id))
	{
        cout << "iF : " << iF << " / " << n_frm << endl;
        int idx = li_idx[0];
		string fn = li_li_path[0][idx];
		Mat im_cur = imread(fn, cv_read_flag);
		for(int iS = 1; iS < n_seq; iS++)
		{
			idx = li_idx[iS];
			fn = li_li_path[iS][idx];
			//im_cur = concatenate_images(im_cur, imread(fn, cv_read_flag), hori_minus_vert_plus);
			im_cur = concatenate_images(im_cur, imread(fn, cv_read_flag), hori_minus_vert_plus, neg_left_or_top_0_center_pos_right_or_bottom, 
						    factor_margin, color_margin);	

		}
        if(0 > neg_vid_0_seq_pos_gif) vw = write_one_frame_to_video(vw, im_cur, 0 == iF, path_vid_or_gif, 30, 1000);
	else if(0 <= neg_vid_0_seq_pos_gif) 
        {
            //string fn_concat = "concat_" + get_exact_file_name_from_path(fn) + ".bmp"; 
            string fn_concat = "concat_" + get_exact_file_name_from_path(fn) + ".png"; 
            save_one_image_under_directory(im_cur, dir_save, fn_concat);
        }     

	iF++;
    }
    if(0 > neg_vid_0_seq_pos_gif) 
    { 
        cout << "concatenated video has just saved at : " << path_vid_or_gif << endl;  
        vw.release();
        string str_ffmpeg = "ffmpeg -y -i " + path_vid_or_gif + " " + python_join_equivalent(dir_save, "output.mp4");
        cout << "str_ffmpeg : " << str_ffmpeg << endl;    //exit(0);
        std::system(str_ffmpeg.c_str());  
 
    }
    else if(0 < neg_vid_0_seq_pos_gif)
    {
#if 0    
        string str_imagemagick = "convert -delay 20 -loop 0 -monitor " + python_join_equivalent(dir_save, "concat_*") + " " + path_vid_or_gif;
        cout << "str_imagemagick : " << str_imagemagick << endl;    //exit(0);
        std::system(str_imagemagick.c_str());  
        cout << "concatenated animated-gif has just saved at : " << path_vid_or_gif << endl;    //exit(0);  
        string str_optimize_10 = "convert " + path_vid_or_gif + " -fuzz 10% -layers Optimize " + path_vid_or_gif;
        cout << "str_optimize_10 : " << str_optimize_10 << endl;    //exit(0);
        std::system(str_optimize_10.c_str());  
#else   //0
        string str_webp = "img2webp -v -mixed -d 40 " + python_join_equivalent(dir_save, "concat_*.png") + " -o " + path_vid_or_gif;
        cout << "str_webp : " << str_webp << endl;    //exit(0);
        std::system(str_webp.c_str());    //exit(0); 
#endif  //0
        //GifEnd( &writer );
    }
    else
    {
        cout << "concatenated image sequence has just saved under : " << dir_save << endl;
    }
    return;
}














unsigned int pseudo_inverse(const Mat& A, Mat &Ap, Mat &sv, double svThreshold, Mat &imA, Mat &imAt, Mat &kerA) 
{
    unsigned int rank, nrows = A.rows, ncols = A.cols;
    Mat A_dummy, U, V, sv_;
    if(nrows < ncols) {
        A_dummy = Mat::zeros(ncols, ncols, A.type());  sv = Mat::zeros(nrows, 1, A.type());
    } 
    else {
        A_dummy = Mat::zeros(nrows, ncols, A.type());  sv = Mat::zeros(ncols, 1, A.type());
    }
    A.copyTo(A_dummy(Rect(0, 0, ncols, nrows)));
    svd_opencv(A_dummy, U, sv_, V);
    //compute_pseudo_inverse(U, sv_, V, nrows, ncols, svThreshold, Ap, rank, imA, imAt, kerA);
    compute_pseudo_inverse(U, sv_, V, nrows, ncols, svThreshold, Ap, rank, imA, imAt, kerA);
    // Remove singular values equal to to that correspond to the lines of 0
    // introduced when m < n
    sv_(Rect(0, 0, 1, sv.rows)).copyTo(sv);
    return rank;
}


unsigned int pseudo_inverse(const Mat& A, Mat &Ap, double svThreshold)
{
    unsigned int rank, nrows, ncols, nrows_orig = A.rows, ncols_orig = A.cols;
    Ap = Mat(ncols_orig, nrows_orig, A.type());
    if (nrows_orig >= ncols_orig) {
        nrows = nrows_orig;
        ncols = ncols_orig;
    } 
    else {
        nrows = ncols_orig;
        ncols = nrows_orig;
    }
    Mat U, sv, V, A_dummy = nrows_orig >= ncols_orig ? A.clone() : A.t();
    svd_opencv(A_dummy, U, sv, V);
    compute_pseudo_inverse(U, sv, V, nrows, ncols, nrows_orig, ncols_orig, svThreshold, Ap, rank);
    return rank;
}

//-----------------------------------------------------------------------------------------------------  
//	Mat im = imread("aaa.bmp");
//	save_one_image_under_directory(im, "/home/folder", "bbb.bmp");
//	=> An image is saved at /home/folder/bbb.bmp".

void save_one_image_under_directory(const Mat& im, const string& dir_save, const string& fn_img)
{
	//mkdir_if_not_exist(dir_save.c_str());
	mkdirs(dir_save.c_str());
	string path_res = python_join_equivalent(dir_save, fn_img);
 	imwrite(path_res, im);
}

//-----------------------------------------------------------------------------------------------------  
//	VideoWriter vw = init_video_writer("/home/folder/aaa.avi", 30, Size(640, 480));

VideoWriter init_video_writer(const string& fn_path, double fps, const Size& saiz)
{
	VideoWriter writer;
    cout << "fps : " << fps << endl;
    cout << "saiz : " << saiz << endl;
    writer.open(fn_path, VideoWriter::fourcc('H', '2', '6', '4'), fps, saiz, true);
    if (!writer.isOpened())
    {
        writer.open(fn_path, VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, saiz, true);
        if (!writer.isOpened())
        {
            writer.open(fn_path, VideoWriter::fourcc('M', 'P', '4', 'V'), fps, saiz, true);
            if (!writer.isOpened())
            {
                writer.open(fn_path, VideoWriter::fourcc('X', '2', '6', '4'), fps, saiz, true);
                if (!writer.isOpened())
                {
                    writer.open(fn_path, VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, saiz, true);
                    if (!writer.isOpened())
                    {
                        cout << "동영상을 저장하기 위한 초기화 작업 중 에러 발생" << endl;	exit(0);
                    }    
                    else
                    {
                        cout << "Codec : MJPG OK" << endl;
                    }
                }
                else
                {
                    cout << "Codec : X264 OK" << endl;
                }
            }
            else
            {
                cout << "Codec : MP4V OK" << endl;
            }
        }
        else
        {
            cout << "Codec : XVID OK" << endl;
        }
    }
    else
    {
        cout << "Codec : H264 OK" << endl;
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
                //if(is_first_a_factor_of_second(iS, size_src.width) && is_first_a_factor_of_second(iS, size_src.height))
                //{
                    int wid = size_src.width / iS, hei = size_src.height / iS;
                    if(wid <= size_tgt.width || hei <= size_tgt.height)
                    {
                        size_smaller_than.width = wid;  size_smaller_than.height = hei;
                        break;
                    }
                //}       
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

Mat resize_image(const Mat& im_ori, int w_new, int h_new, float fx, float fy, int max_side, bool make_width_multiple_of_2 = false)
{
	Mat im_resized;
	int max_wh = MAX(im_ori.cols, im_ori.rows);
	if(w_new > 0 && h_new > 0) resize(im_ori, im_resized, Size(w_new, h_new), 0, 0);
	else if(fx > 0 && fy > 0) resize(im_ori, im_resized, Size(0, 0), fx, fy);
	else if(max_side < max_wh)
	{
		float ratio = float(max_side) / float(max_wh);
		if (make_width_multiple_of_2)
		{
			w_new = 2 * int(float(im_ori.cols) * ratio / 2.0);
			ratio = float(w_new) / float(im_ori.cols);
		}			
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


//-----------------------------------------------------------------------------------------------------  
// Non maxima suppreson on 2D mat. 
// The local maxima values of the returned matrix is '255' and else is '0'.   
//	Mat mat_hist = (Mat_<float>(3, 4) << 1, 1, 2, 1, 2, 3, 0, 4, 2, 0, 1, 3);
//	cout << mat_hist << endl;
//	=> 	[1, 1, 2, 1;
//		 2, 3, 0, 4;
//		 2, 0, 1, 3]
//	Mat mat_peak_255 = non_maxima_suppression_on_mat(mat_hist, true);
//	cout << mat_peak_255 << endl;
//	=>	[0, 0, 0, 0;
//		 0, 255, 0, 255;
//		 0, 0, 0, 0]

Mat non_maxima_suppression_on_mat(const cv::Mat& src, const bool remove_plateaus = true)
{
	Mat mask;
	// find pixels that are equal to the local neighborhood not maximum (including 'plateaus')
    	cv::dilate(src, mask, cv::Mat());    
    	cv::compare(src, mask, mask, cv::CMP_GE);
    	// optionally filter out pixels that are equal to the local minimum ('plateaus')
    	if (remove_plateaus) 
    	{    
        	cv::Mat non_plateau_mask;        
        	cv::erode(src, non_plateau_mask, cv::Mat());        
        	cv::compare(src, non_plateau_mask, non_plateau_mask, cv::CMP_GT);        
        	cv::bitwise_and(mask, non_plateau_mask, mask);
    	}
	return mask;	
}


//-----------------------------------------------------------------------------------------------------  
// function that finds the peaks of a given 2D hist image
// The list of local maxima points which satisfy the threshold conditions are returned.
//	Mat mat_hist = (Mat_<float>(3, 4) << 1, 1, 2, 1, 2, 3, 0, 4, 2, 0, 1, 3);
//	cout << mat_hist << endl;
//	=> 	[1, 1, 2, 1;
//		 2, 3, 0, 4;
//		 2, 0, 1, 3]
//	vector<Point> li_peak_th_2 = find_peaks_on_mat(mat_hist, 2, -1, Size(1, 1), true);
//	cout << li_peak_th_2 << endl;
//	=>	[1, 1;
//		 3, 1]
//	vector<Point> li_peak_th_3 = find_peaks_on_mat(mat_hist, 3, -1, Size(1, 1), true);
//	cout << li_peak_th_3 << endl;
//	=>	[3, 1]

//void findHistPeaks(InputArray _src, OutputArray _idx, const float scale = 0.2, const Size& ksize = Size(9, 9), const bool remove_plateus = true)
vector<Point> find_peaks_on_mat(InputArray _src, const float thres, const float scale, const Size& ksize, const bool remove_plateus = true)
{
    Mat hist = _src.getMat();
    // die if histogram image is not the correct type
    CV_Assert(hist.type() == CV_32F);
    
    // find the min and max values of the hist image
    double min_val, max_val; Point min_loc, max_loc;
    minMaxLoc(hist, &min_val, &max_val, &min_loc, &max_loc);
	
    //Mat mask; 
    if(ksize.width * ksize.height > 1) GaussianBlur(hist, hist, ksize, 0); // smooth a bit in order to obtain better result  
    //non_maxima_suppression_on_mat(hist, mask, remove_plateus); // extract local maxima    
    Mat mask = non_maxima_suppression_on_mat(hist, remove_plateus); // extract local maxima    
    vector<Point> maxima;   // output, locations of non-zero pixels    
    cv::findNonZero(mask, maxima);    
    for(vector<Point>::iterator it = maxima.begin(); it != maxima.end();)
    {
        Point pnt = *it;
        float val = hist.at<float>(pnt.y, pnt.x);
        bool is_satisfying_threshold = (thres < 0) || (thres >= 0 && val > thres);
        bool is_satisfying_scale = (scale <= 0) || (scale > 0 && val > max_val * scale); 
        if(is_satisfying_threshold && is_satisfying_scale) ++it;
	else it = maxima.erase(it);
    }                                                                                      
    return maxima;
}

//------------ Find peaks on a 2D mat. -------------- 
vector<Point> find_peaks_2D(const vector<Point2f>& li_center, const Size& sz_im, float th_hist)
{
    Mat im_hist = Mat::zeros(sz_im, CV_32FC1);   
    int iC, n_center = li_center.size();
    for(iC = 0; iC < n_center; iC++)
    {
        int x0 = li_center[iC].x, y0 = li_center[iC].y;
        int x1 = x0 + 1, y1 = y0 + 1;
        float w_x0_y0, w_x1_y0, w_x0_y1, w_x1_y1;
        compute_bilnear_weight(w_x0_y0, w_x1_y0, w_x0_y1, w_x1_y1, li_center[iC].x, li_center[iC].y);
        im_hist.at<float>(y0, x0) += w_x0_y0;   im_hist.at<float>(y0, x1) += w_x1_y0;
        im_hist.at<float>(y1, x0) += w_x0_y1;   im_hist.at<float>(y1, x1) += w_x1_y1;
    }
    vector<Point> li_center_max = find_peaks_on_mat(im_hist, th_hist, -1, Size(15, 15), true);
    return li_center_max;        
}


Mat rot_mat_2_quaternion(const Mat& m33) {

    double qx, qy, qz, qw,  
        m00 = m33.at<double>(0, 0), m01 = m33.at<double>(0, 1), m02 = m33.at<double>(0, 2),
        m10 = m33.at<double>(1, 0), m11 = m33.at<double>(1, 1), m12 = m33.at<double>(1, 2),
        m20 = m33.at<double>(2, 0), m21 = m33.at<double>(2, 1), m22 = m33.at<double>(2, 2);

    float tr = m00 + m11 + m22;

    if (tr > 0) { 
        float S = sqrt(tr+1.0) * 2; // S=4*qw 
    qw = 0.25 * S;
      qx = (m21 - m12) / S;
        qy = (m02 - m20) / S; 
          qz = (m10 - m01) / S; 
          } else if ((m00 > m11)&(m00 > m22)) { 
            float S = sqrt(1.0 + m00 - m11 - m22) * 2; // S=4*qx 
              qw = (m21 - m12) / S;
                qx = 0.25 * S;
                  qy = (m01 + m10) / S; 
                    qz = (m02 + m20) / S; 
                    } else if (m11 > m22) { 
                      float S = sqrt(1.0 + m11 - m00 - m22) * 2; // S=4*qy
                        qw = (m02 - m20) / S;
                          qx = (m01 + m10) / S; 
                            qy = 0.25 * S;
                              qz = (m12 + m21) / S; 
                              } else { 
                                float S = sqrt(1.0 + m22 - m00 - m11) * 2; // S=4*qz
                                  qw = (m10 - m01) / S;
                                    qx = (m02 + m20) / S;
                                      qy = (m12 + m21) / S;
                                        qz = 0.25 * S;
                                        }
    
    Mat Q = (Mat_<double>(4, 1) << qx, qy, qz, qw);
    //Mat Q = (Mat_<double>(4, 1) << qw, qx, qy, qz);
    return Q;
}    



template<typename T>
Mat skewMat( const Mat_<T> &x )
{
  Mat_<T> skew(3,3);
    skew <<   0 , -x(2),  x(1),
              x(2),    0 , -x(0),
                       -x(1),  x(0),    0;

                         return std::move(skew);
                         }


 Mat skew_symmetric( InputArray _x )
 {
   const Mat x = _x.getMat();
     const int depth = x.depth();
       CV_Assert( x.size() == Size(3,1) || x.size() == Size(1,3) );
	 CV_Assert( depth == CV_32F || depth == CV_64F );

	   Mat skewMatrix;
	     if( depth == CV_32F )
	       {
		   skewMatrix = skewMat<float>(x);
		     }
		       else if( depth == CV_64F )
			 {
			     skewMatrix = skewMat<double>(x);
			       }
				 else
				   {
				       //CV_Error(CV_StsBadArg, "The DataType must be CV_32F or CV_64F");
					 }

					   return skewMatrix;
					   }





double sqrt_of_mean_square(const cv::Mat& m)
{
	double sos = sum_of_squared(m);
	double ms = sos / m.total();
	return sqrt(ms);		
}

double sum_of_squared(const cv::Mat& m)
{
	double sqrt_sos = cv::norm(m, cv::NORM_L2);
	return sqrt_sos * sqrt_sos;
}
	
void svd_opencv(const Mat& A, Mat& U, Mat &w, Mat &V)
{
    std::cout << "VISP_HAVE_OPENCV_VERSION : " << VISP_HAVE_OPENCV_VERSION << std::endl;
    cv::Mat m;
    A.convertTo(m, CV_64F);
    //int rows = U.rows, cols = U.cols;
    //cv::Mat m(rows, cols, CV_64F, this->data);
    cv::SVD opencvSVD(m);
    V = opencvSVD.vt.t();
    w = opencvSVD.w;
    U = opencvSVD.u;
    return;
}


//	ref. : https://stackoverflow.com/questions/10167534/how-to-find-out-what-type-of-a-mat-object-is-with-mattype-in-opencv
void writeMat2File(cv::Mat& m, const string& filename, bool channelwise)
{
	if (m.dims >= 4)
	{
		cout << "Matrix dimension is " << m.dims << "File writing for matrix of more than 3 dimension is not implemented yet." << endl;
		return;
	}

	ofstream fout(filename);

	if (!fout)
	{
		cout << "File Not Opened" << endl;  return;
	}

	int taip = m.type() % 8;
	int n_c = m.channels();
	if (channelwise)
	{
		if (0 == taip)	//	unsinged char
		{
			for (int iC = 0; iC < n_c; iC++)
			{
				for (int i = 0; i < m.rows; i++)
				{
					unsigned char *ptr_row = m.ptr<unsigned char>(i);
					for (int j = 0; j < m.cols; j++) fout << ptr_row[n_c * j + iC] << "\t";
					fout << endl;
				}
			}
		}

		else if (1 == taip)	//	nsinged char
		{
			for (int iC = 0; iC < n_c; iC++)
			{
				for (int i = 0; i < m.rows; i++)
				{
					signed char *ptr_row = m.ptr<signed char>(i);
					for (int j = 0; j < m.cols; j++) fout << ptr_row[n_c * j + iC] << "\t";
					fout << endl;
				}
			}
		}

		else if (2 == taip)	//	nsinged char
		{
			for (int iC = 0; iC < n_c; iC++)
			{
				for (int i = 0; i < m.rows; i++)
				{
					unsigned short *ptr_row = m.ptr<unsigned short>(i);
					for (int j = 0; j < m.cols; j++) fout << ptr_row[n_c * j + iC] << "\t";
					fout << endl;
				}
			}
		}

		else if (3 == taip)	//	nsinged char
		{
			for (int iC = 0; iC < n_c; iC++)
			{
				for (int i = 0; i < m.rows; i++)
				{
					signed short *ptr_row = m.ptr<signed short>(i);
					for (int j = 0; j < m.cols; j++) fout << ptr_row[n_c * j + iC] << "\t";
					fout << endl;
				}
			}
		}

		else if (4 == taip)	//	nsinged char
		{
			for (int iC = 0; iC < n_c; iC++)
			{
				for (int i = 0; i < m.rows; i++)
				{
					int *ptr_row = m.ptr<int>(i);
					for (int j = 0; j < m.cols; j++) fout << ptr_row[n_c * j + iC] << "\t";
					fout << endl;
				}
			}
		}

		else if (5 == taip)	//	nsinged char
		{
			for (int iC = 0; iC < n_c; iC++)
			{
				for (int i = 0; i < m.rows; i++)
				{
					float *ptr_row = m.ptr<float>(i);
					for (int j = 0; j < m.cols; j++) fout << ptr_row[n_c * j + iC] << "\t";
					fout << endl;
				}
			}
		}

		else if (6 == taip)	//	nsinged char
		{
			for (int iC = 0; iC < n_c; iC++)
			{
				for (int i = 0; i < m.rows; i++)
				{
					double *ptr_row = m.ptr<double>(i);
					for (int j = 0; j < m.cols; j++) fout << ptr_row[n_c * j + iC] << "\t";
					fout << endl;
				}
			}
		}
	}

	else
	{
		if (0 == taip)	//	unsinged char
		{
			for (int i = 0; i < m.rows; i++)
			{
				unsigned char *ptr_row = m.ptr<unsigned char>(i);
				for (int j = 0; j < m.cols; j++)
				{
					for (int iC = 0; iC < n_c; iC++) fout << ptr_row[n_c * j + iC] << "\t";
				}
				fout << endl;
			}
		}
		else if (1 == taip)	//	singed char
		{
			for (int i = 0; i < m.rows; i++)
			{
				signed char *ptr_row = m.ptr<signed char>(i);
				for (int j = 0; j < m.cols; j++)
				{
					for (int iC = 0; iC < n_c; iC++) fout << ptr_row[n_c * j + iC] << "\t";
				}
				fout << endl;
			}
		}

		else if (2 == taip)	//	unsinged short
		{
			for (int i = 0; i < m.rows; i++)
			{
				unsigned short *ptr_row = m.ptr<unsigned short>(i);
				for (int j = 0; j < m.cols; j++) 
				{
					for (int iC = 0; iC < n_c; iC++) fout << ptr_row[n_c * j + iC] << "\t";
				}
				fout << endl;
			}
		}

		else if (3 == taip)	//	singed short
		{
			for (int i = 0; i < m.rows; i++)
			{
				signed short *ptr_row = m.ptr<signed short>(i);
				for (int j = 0; j < m.cols; j++)
				{
					for (int iC = 0; iC < n_c; iC++) fout << ptr_row[n_c * j + iC] << "\t";
				}
				fout << endl;
			}
		}

		else if (4 == taip)	//	int
		{
			for (int i = 0; i < m.rows; i++)
			{
				int *ptr_row = m.ptr<int>(i);
				for (int j = 0; j < m.cols; j++)
				{
					for (int iC = 0; iC < n_c; iC++) fout << ptr_row[n_c * j + iC] << "\t";
				}
				fout << endl;
			}
		}

		else if (5 == taip)	//	float
		{
			for (int i = 0; i < m.rows; i++)
			{
				float *ptr_row = m.ptr<float>(i);
				for (int j = 0; j < m.cols; j++) 
				{
					for (int iC = 0; iC < n_c; iC++) fout << ptr_row[n_c * j + iC] << "\t";
				}
				fout << endl;
			}
		}

		else if (6 == taip)	//	double
		{
			for (int i = 0; i < m.rows; i++)
			{
				double *ptr_row = m.ptr<double>(i);
				for (int j = 0; j < m.cols; j++) 
				{
					for (int iC = 0; iC < n_c; iC++) fout << ptr_row[n_c * j + iC] << "\t";
				}
				fout << endl;
			}
		}
	}
	fout.close();
}

Mat zeros_like(const Mat& mat_ori)
{
	return Mat::zeros(mat_ori.size(), mat_ori.type());
}

Mat ones_like( const Mat& mat_ori, float skaler )
{
    return Mat::ones( mat_ori.size(), mat_ori.type() ) * skaler;
}



cv::Point2f find_blackhole_by_correlation( const Mat& im_gray, const Rect& roi, const Mat& im_gray_black_circle )
{
    Mat im_result;
    matchTemplate( im_gray( roi ), im_gray_black_circle, im_result, cv::TM_CCOEFF_NORMED );
    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc( im_result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    cv::Point p_tl( roi.x + maxLoc.x, roi.y + maxLoc.y );
    cv::Point p_br( p_tl.x + im_gray_black_circle.cols, p_tl.y + im_gray_black_circle.rows );
    return cv::Point2f( 0.5 * float( p_tl.x + p_br.x ), 0.5 * ( p_tl.y + p_br.y ) );
}

std::vector<cv::Point2f> binary_mat_2_point_list( cv::Mat& binaryImage, cv::Mat* im_mask = NULL )
{
    std::vector<cv::Point2f> pointPositions;
    uchar *p_data_y = NULL, *p_data = NULL, *p_mask_y = NULL, *p_mask = NULL;
    for ( int y = binaryImage.rows - 1; y >= 0; --y )
    {
        p_data_y = binaryImage.ptr<uchar>( y );

        if ( im_mask )
        {
            p_mask_y = im_mask->ptr<uchar>( y );
        }
        for ( int x = binaryImage.cols - 1; x >= 0; --x )
        {
            p_data = p_data_y + x;

            if ( im_mask )
            {
                p_mask = p_mask_y + x;
            }
            if ( *( p_data ) > 0 && ( im_mask ? * ( p_mask ) > 0 : true ) )
            {
                pointPositions.push_back( cv::Point2f( x, y ) );
            }
        }
    }
    return pointPositions;
}





	
		

