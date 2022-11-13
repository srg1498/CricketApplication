--------------------------------------- HOW TO RUN APPLICATION FOR DIFFERENT TESTCASES -------------------------------------------------------


# - There are two testcases files which are present at this path - "./testcases/
  - testcase1.txt - It will give result as tie, which will then also result in super over.
  - testcase2.txt - It is a random input which can give any result (NOTE:- If scores are equal, then only super over will happen).

# - There is one folder "./gamedata/input/gameinput/" which contains the main input file.
  - Application basically refers this file for execution of the game.
  - If this file is empty, application will generate input for the game.
  - For running testcases which are there in "./testcases/" folder, please copy the testcase data and paste it into main input file.
  - Right now input file is having testcase1 data which will result in super over.
  - Save the main input file if you do any changes in this file

# - Execute run.exe file for running this application




--------------------------------------------------   PROJECT BUILD INFO  ------------------------------------------------------------------------


# PROBLEM STATEMENT - We need to create one cricket application which will predict outcome based on the bowlcard, shot and timing
                      input. Also we have to add commentary in this application and if match is tied, then super over should happen.


# Design and Implementation Details:-
  
  - I firstly created one Game class which will handle all the functionalities like loading media files, loading input data,
    create teams, etc.
  
  - I created Player and Team Models.

  - I used singleton pattern for creating Game object because during whole process only one game object is sufficient.

  - Apart from this, for loading the media files, I created one base class MediaFolderLoader and then created three derived
    classes (each for different media folder).

  - I also add two separate class for handling file operations. These were FileReader and FileWriter classes.
    I created these classes so that RAII concept can be achieved. Constructor takes care of file opening and destructor takes care
    of file closing.

  - In utilityModules, I basically defined common functions which are used many times like toLowerCase(), splitString(), etc. 

  - In configurations, I kept all global path variables, cricket variables, etc.


  
  For compiling the project, I used the following command:-

  g++ -o run ./src/app.cpp ./src/Game/Game.cpp ./src/Team/Team.cpp ./src/Player/Player.cpp ./src/MediaFolderLoader/MediaFolderLoader.cpp ./src/ShotOutcomesMediaFolderLoader/ShotOutcomesMediaFolderLoader.cpp ./src/TeamsMediaFolderLoader/TeamsMediaFolderLoader.cpp ./src/CommentaryMediaFolderLoader/CommentaryMediaFolderLoader.cpp ./src/FileReader/FileReader.cpp ./src/FileWriter/FileWriter.cpp ./src/UtilityModules/utilityModules.cpp ./src/GameInputLineStructure/GameInputLineStructure.cpp




-------------------------------------------- OTHER FILES INFO USED IN THIS PROJECT ----------------------------------------------------


# MediaFiles info:-
  1) ./gamedata/mediafiles/Teams - This folder contains teams data like players info.
  2) ./gamedata/mediafiles/ShotOutcomes - This folder has outcome chart (timing vs shot) of each of the bowlCard in separate file.
  3) ./gamedata/mediafiles/Commentary - This folder has commentary details.



# Game Input:-
  1) ./gamedata/input/gameinput/GameInput.txt - This file has input of both the innings. Each line tells about what kind of bowl 
                                                bowler has bowled, which shot batter has played and with what timing.
                                                Each line is in below mentioned format
                                                <bowlCard> <shot> <timing>/
                                              - If file is initially empty, then code application will generate input for the game.

  2) ./gamedata/input/gamesuperoverinput/GameSuperOverInput.txt - This file is initially empty. It contains input for the super over. 
                                                                  If match is tied, then input for the super over will be generated 
                                                                  and saved in this file.
  

# Game Output:-
  1) ./gamedata/output/MatchSummary.txt - This file contains match summary.

  2) ./gamedata/output/GameCommentary.txt - This file contains commentary of the match.




# Code Files Info:-
  1) configurations.h  - This file contains game configurations info like cricket variables, path variables
  2) include - This folder contains all the interfaces(classes) of the application. 
  3) src - This folder contains all the implementations of the interfaces used in the application.





-------------------------------------- CODE COMPILATION AND OTHER INFO REGARDING COMPILER ------------------------------------------


# Compiler info used for compiling this code:-
  -> Using built-in specs.
  -> COLLECT_GCC=g++
  -> COLLECT_LTO_WRAPPER=c:/mingw/bin/../libexec/gcc/x86_64-w64-mingw32/11.2.0/lto-wrapper.exe
  -> Target: x86_64-w64-mingw32
  -> Configured with: ../src/configure --enable-languages=c,c++ --build=x86_64-w64-mingw32 --host=x86_64-w64-mingw32 --target=x86_64-w64-mingw32 --disable-multilib --prefix=/c/temp/gcc/dest --with-sysroot=/c/temp/gcc/dest --disable-libstdcxx-pch --disable-libstdcxx-verbose --disable-nls --disable-shared --disable-win32-registry --enable-threads=posix --enable-libgomp --with-zstd=/c/mingw --disable-bootstrap
  -> Thread model: posix
  -> Supported LTO compression algorithms: zlib zstd
  -> gcc version 11.2.0 (GCC)
  
# - If some changes are done in any of the code files, then use the below command for compiling the code:-
    g++ -o run ./src/app.cpp ./src/Game/Game.cpp ./src/Team/Team.cpp ./src/Player/Player.cpp ./src/MediaFolderLoader/MediaFolderLoader.cpp ./src/ShotOutcomesMediaFolderLoader/ShotOutcomesMediaFolderLoader.cpp ./src/TeamsMediaFolderLoader/TeamsMediaFolderLoader.cpp ./src/CommentaryMediaFolderLoader/CommentaryMediaFolderLoader.cpp ./src/FileReader/FileReader.cpp ./src/FileWriter/FileWriter.cpp ./src/UtilityModules/utilityModules.cpp ./src/GameInputLineStructure/GameInputLineStructure.cpp
  
  - After compilation only, execute run.exe if you do any changes in the code.







  