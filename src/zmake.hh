#pragma once
#include <string>

namespace ZMake {
   enum class Commands {
      BUILD,
      CLEAN,
      INVALID,
      NEW,
      RUN,
   };

   // helpers
   Commands getCommand(std::string const& input);
   bool isZmake();
   std::string getCurrentDir();
   void log(std::string const& input);
   std::string getLatestCmake();
   
   // commands
   void build();
   void clean();
   void newProject(const char* input);
   void run();
}
