#pragma once
#include <string>

namespace ZMake {
   // helpers
   bool isZmake();
   std::string getCurrentDir();
   void log(std::string const& input);
   
   // commands
   void build();
   void clean();
   void newProject(std::string const& input);
   void run();
}
