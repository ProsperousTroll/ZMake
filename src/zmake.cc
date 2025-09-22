#include "zmake.hh"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <filesystem>

// ----------------- helpers ----------------- //

std::string ZMake::getCurrentDir(){
   return std::filesystem::current_path().string();
}

void ZMake::log(std::string const& input){
   std::string out{R"(echo -e "\e[3;92m )" + input + R"(")"};
   system(out.c_str());
}

bool ZMake::isZmake() {
   std::ifstream _id_z(".id.z");
   if(!_id_z){
      ZMake::log(" > ERROR! Not currently in a ZMake project. Did you run 'zmake new'?");
      return false;
   }
   return true;
}

// ----------------- commands ------------------ //

void ZMake::build() {
   if(ZMake::isZmake()){
      ZMake::log(" > Building...");
      return;
   }
}

void ZMake::clean() {
   ZMake::log(" > Cleaning...");
}

void ZMake::newProject(std::string const& input) {

   std::filesystem::path dir{input};
   if(std::filesystem::create_directory(dir)){
      ZMake::log(" > Created project folder...");
      ZMake::log(" > Initializing...");

      std::ofstream _id_z( dir / ".id.z");
      _id_z << input;

      std::filesystem::path src{"src"};
      std::filesystem::create_directory(dir / src);
      std::ofstream scriptTemplate{dir / src/ "main.cc"};

      // Template for starter main file. formatted weird so the output looks normal.
      scriptTemplate << R"(
#include <iostream>

int main(){
   std::cout << "Hello, World!\n";
   //
   return 0;
}
      )";

      std::ofstream CMakeListTemplate{dir / "CMakeLists.txt"};
      CMakeListTemplate << "uhhhhhhhhhhhh uh oh hahah";

   } else {
      // exit if dir already exists
      ZMake::log (" > ERROR! Failed to create project directory... Does it already exist?");
      return;
   }

}

void ZMake::run() {
   ZMake::log(" > Running...");
}
