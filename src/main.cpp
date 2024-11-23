#include <filesystem>
#include <fstream>
#include <iostream>

std::string project_name = "project";
//std::string project_version = "0.1.0";
std::string cpp_standard = "17";

void project_config(int argc,char** argv){
  if(argc>=2){
    project_name = std::string(argv[1]);
  }

  std::cout<<"program is generate C++ project \n"<<std::endl;

  std::cout<<"Project name (defaults to "<<project_name<<") :";

  std::string cin_project_name;
  std::getline(std::cin, cin_project_name);
  if(!cin_project_name.empty())
    project_name = cin_project_name;
  
  // std::cout<<"Project version (defaults to "<<project_version<<") :";
  // std::string cin_project_version;
  // std::getline(std::cin, cin_project_version);
  // if(!cin_project_version.empty())
  //   project_version = cin_project_version;

  std::cout<<"C++ standand (defaults to "<<cpp_standard<<") :";
  std::string cin_cpp_standard;
  std::getline(std::cin, cin_cpp_standard);
  if(!cin_cpp_standard.empty())
    cpp_standard = cin_cpp_standard;
}


int main(int argc,char** argv){
  project_config(argc,argv);

  std::filesystem::path current_dir = std::filesystem::current_path();
  std::string project_path = current_dir.string()+"/"+project_name;
  if(std::filesystem::exists(project_path) && std::filesystem::is_directory(project_path)){
    std::cerr<<project_path<<" is exists \n cloudn't create peojcet"<<std::endl;
    return -1;
  }else{
    std::filesystem::create_directories(project_path+"/include");
    std::filesystem::create_directories(project_path+"/src");

    std::fstream main_cpp(project_path+"/src/main.cpp",std::ios::out);
    if(!main_cpp.is_open()){
      std::cerr<<"open file error"<<std::endl;
      std::filesystem::remove_all(project_path);
      return -1;
    }
    main_cpp<<"#include <iostream>\n\nint main(){\n\tstd::cout<<\"hello "+project_name+"!\"<<std::endl;\n\n\treturn 0;\n}";
    main_cpp.close();

    std::fstream cmake(project_path+"/CMakeLists.txt",std::ios::out);
    if(!cmake.is_open()){
      std::cerr<<"open file error"<<std::endl;
      std::filesystem::remove_all(project_path);
      return -1;
    }
    cmake<<"cmake_minimum_required(VERSION 3.20)\nproject("+project_name+")\n\nset(CMAKE_CXX_STANDARD "+cpp_standard+")\nset(CMAKE_CXX_STANDARD_REQUIRED ON)\n\ninclude_directories(${SOURCE_DIR}/include)\n\nfile(GLOB PROJECT_SOURCES src/*.cpp)\n\n# if you need\n# find_package()\n\nadd_executable(${PROJECT_NAME} ${PROJECT_SOURCES})\n\n# if you need\n# target_link_libraries(${PROJECT_NAME} ...)";
    cmake.close();
  }
  std::cout<<"generate "+ project_name+" finish"<<std::endl;
}
