#include <iostream>
#include "zmake.hh"

int main(int argc, char* argv[]){
   if (argc < 2){
      std::cout << "Usage: zmake <command> [options]\n";
      return 1;
   }

   std::string command{argv[1]};

   if(command == "run"){

      ZMake::run();

   } else if (command == "new"){

      // failsafe, exit 
      std::string input{argv[2]};
      if(input == ""){
         ZMake::log(" > Please enter a project name...");
         return 1;
      }

      ZMake::newProject(input);

   } else if (command == "build"){

      ZMake::build();

   } else if (command == "clean"){

      ZMake::clean();

   } 

   else {
      std::cout << "What? Type a real command moron.\n";
   }

   //
   return 0;
}
