#include <iostream>
#include "zmake.hh"

int main(int argc, char* argv[]){
   if (argc < 2){
      ZMake::log ("Usage: zmake <commands> [options]");
      return 1;
   }

   std::string command{argv[1]};
   switch(ZMake::getCommand(command)){
      case ZMake::Commands::BUILD: ZMake::build(); break;
      case ZMake::Commands::CLEAN: ZMake::clean(); break;
      case ZMake::Commands::NEW: ZMake::newProject(argv[2]); break;
      case ZMake::Commands::RUN: ZMake::run(); break;
      case ZMake::Commands::INVALID: ZMake::log("What? Type a real command, moron."); break;
   }
   //
   return 0;
}
