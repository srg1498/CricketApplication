# Execute run.exe file for running this application


# Compiler info used for compiling this code:-
  -> Using built-in specs.
  -> COLLECT_GCC=g++
  -> COLLECT_LTO_WRAPPER=c:/mingw/bin/../libexec/gcc/x86_64-w64-mingw32/11.2.0/lto-wrapper.exe
  -> Target: x86_64-w64-mingw32
  -> Configured with: ../src/configure --enable-languages=c,c++ --build=x86_64-w64-mingw32 --host=x86_64-w64-mingw32 --target=x86_64-w64-mingw32 --disable-multilib --prefix=/c/temp/gcc/dest --with-sysroot=/c/temp/gcc/dest --disable-libstdcxx-pch --disable-libstdcxx-verbose --disable-nls --disable-shared --disable-win32-registry --enable-threads=posix --enable-libgomp --with-zstd=/c/mingw --disable-bootstrap
  -> Thread model: posix
  -> Supported LTO compression algorithms: zlib zstd
  -> gcc version 11.2.0 (GCC)
  
  -> If some changes are done in any of the code files, then use the below command for compiling the code:-
     g++ -o run app.cpp ./Implementations/Game.cpp ./Implementations/Team.cpp ./Implementations/Player.cpp ./Implementations/MediaFolderLoader.cpp ./Implementations/ShotOutcomesMediaFolderLoader.cpp ./Implementations/TeamsMediaFolderLoader.cpp ./Implementations/CommentaryMediaFolderLoader.cpp ./Implementations/FileReader.cpp ./Implementations/FileWriter.cpp ./Implementations/utilityModules.cpp



# MediaFiles info:-
  1) ./MediaFiles/Teams - This folder contains teams data like players info.
  2) ./MediaFiles/ShotOutcomes - This folder has outcome chart (timing vs shot) of each of the bowlCard in separate file.
  3) ./MediaFiles/Commentary - This folder has commentary details.



# Game Input:-
  1) ./InputsAndOutputs/Inputs/GameInput.txt - This file has input of both the innings. Each line tells about what kind of bowl 
                                               bowler has bowled, which shot batter has played and with what timing.
                                               Each line is in below mentioned format
                                               <bowlCard> <shot> <timing>/
                                             - If file is initially empty, then code application will generate input for the game.

  2) ./InputsAndOutputs/Inputs/GameSuperOverInput.txt - This file is initially empty. It contains input for the super over. 
                                                        If match is tied, then input for the super over will be generated 
                                                        and saved in this file.
  

# Game Output:-
  1) ./InputsAndOutputs/Outputs/MatchSummary.txt - This file contains match summary.

  2) ./InputsAndOutputs/Inputs/GameCommentary.txt - This file contains commentary of the match.




# Code Files Info:-
  1) configurations.h  - This file contains game configurations info like cricket variables, path variables
  2) Interfaces - This folder contains all the interfaces(classes) of the application. 
  3) Implementations - This folder contains all the implementations of the interfaces used in the application.




  