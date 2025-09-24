#include "zmake.hh"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <filesystem>
// for latest cmake version
#include <cpr/cpr.h>
#include <regex>

// ------------------ vars ------------------- //

std::string tempMain[8]{
   "#include <iostream>\n",
   "\n",
   "int main(){\n",
   R"(    std::cout << "Hey, neighbor!\n";)",
   "\n",
   "    //\n",
   "    return 0;\n",
   "}",
};

// ----------------- helpers ----------------- //

ZMake::Commands ZMake::getCommand(const std::string &input){
   // hide ugly if statements in a helper
   if(input == "build"){
      return Commands::BUILD;
   } else if(input == "clean"){
      return Commands::CLEAN;
   } else if(input == "new"){
      return Commands::NEW;
   } else if (input == "run"){
      return Commands::RUN;
   }
   return Commands::INVALID;
}

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
      log(" > ERROR! Not currently in a ZMake project. Did you run 'zmake new'?");
      return false;
   }
   std::string project;
   _id_z >> project;
   if (project == ""){
      log(" > ERROR! Project token empty. Did you run 'zmake new'?");
      return false;
   }
   return true;
}

std::string ZMake::getLatestCmake(){
   // I don't love this solution, but it helps keep the project as cross-platform as possible.
   // Subject to change.
   auto r{cpr::Get(cpr::Url{"https://cmake.org/download/"})};
   std::regex rgx("\\((\\d+\\.\\d+\\.\\d+)\\)");
   std::smatch match;
   if(std::regex_search(r.text, match, rgx)){
      return match[1];
   }
   return "";
}

// ----------------- commands ------------------ //

void ZMake::build() {
   if(isZmake()){
      std::filesystem::path project{getCurrentDir()};
      std::filesystem::path build{ project / "build"};
      log(" > Building...");

      if(!std::filesystem::create_directory(build)){
         log(" > Build folder already exists... rebuilding");
      } 

      std::string cmdBuild{"cmake -S " + getCurrentDir() + " -B " + getCurrentDir() + "/build && cd build && make"};
      system(cmdBuild.c_str());
      return;
   }
}

void ZMake::clean() {
   if(isZmake()){
      log(" > Cleaning...");
      std::filesystem::path build{getCurrentDir() + "/build"};
      if(!std::filesystem::remove_all(build)){
         log(" > Nothing to clean!");
      }
      log(" > All clean!");
   }
}

void ZMake::newProject(const char* input) {
   if(input == 0){
      log("Please type a project name!");
      return;
   }

   std::string inputStr{input};
   std::filesystem::path dir{input};
   if(std::filesystem::create_directory(dir)){
      // Probably written nooblishly. Sorry.
      log(" > Created project folder...");
      log(" > Initializing...");

      // ZMake token
      std::ofstream _id_z( dir / ".id.z");
      _id_z << input;

      // build directory tree
      std::filesystem::path src{"src"};
      std::filesystem::path build{"build"};
      std::filesystem::create_directory(dir / src);
      std::filesystem::create_directory(dir / build);
      std::ofstream scriptTemplate{dir / src/ "main.cc"};

      // see std::string tempMain
      for (std::string l : tempMain){
         scriptTemplate << l;
      }
      
      // CMakeLists.txt template
      std::ofstream CMakeListTemplate{dir / "CMakeLists.txt"};
      CMakeListTemplate << "cmake_minimum_required(VERSION " + getLatestCmake() + ")\n";
      CMakeListTemplate << "project(" + inputStr + " VERSION 0.0.1)\n";
      CMakeListTemplate << "add_executable(" + inputStr + " src/main.cc)\n";

      // Initialize git & gitignore
      std::string gitCmd{"cd " + inputStr + " && git init"};
      std::ofstream gitIgnore{dir / ".gitignore"};
      gitIgnore << "/build/";
      system(gitCmd.c_str());

   } else {
      // exit if dir already exists
      log (" > ERROR! Failed to create project directory... Does it already exist?");
      return;
   }
}

void ZMake::run() {
   if(isZmake()){
      log(" > Running...");
      // get project name
      std::ifstream _id_z{".id.z"};
      std::string project;
      _id_z >> project;

      build();
      std::string runCmd{"cd build && ./" + project};
      system(runCmd.c_str());
   }
}
