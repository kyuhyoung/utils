//------------ c++ counterpart of python function "join" --------------  
#include <experimental/filesystem>
string python_join_equivalent(const string& dir_to_file, const string& filename)
{
  std::experimental::filesystem::path dir(dir_to_file);
  std::experimental::filesystem::path fn(filename);    
  std::experimental::filesystem::path full_path = dir / fn;
  return full_path.u8string();                                                                               
}
