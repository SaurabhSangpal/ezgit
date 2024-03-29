cmake_minimum_required(VERSION 3.18)

project(ezgit)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets CONFIG REQUIRED)

set(SRC src/ui/MainWindow.ui
	src/ui/RepoViewerWidget.ui
	src/ui/AllCommits.ui
	src/ui/CloneDialog.ui
	src/main.cc
	src/git_wrapper/Repository.cc
	src/git_wrapper/Remote.cc
	src/git_wrapper/Commit.cc
	src/git_wrapper/File.cc
	src/ui/MainWindow.cc
	src/ui/RepoViewerWidget.cc
	src/ui/AllCommits.cc
	src/ui/CloneDialog.cc
	src/ui/Commit.cc
	src/config/Config.cc
	src/ui/YourChanges.cc
	src/ui/ChangedFile.cc)

add_executable(ezgit WIN32 ${SRC})
target_include_directories(ezgit PRIVATE ${PROJECT_SOURCE_DIR}/vendor/libgit2/include)
target_link_libraries(ezgit PRIVATE ${PROJECT_SOURCE_DIR}/vendor/libgit2/bin/git2.lib
									Qt5::Widgets)

add_custom_command(TARGET ezgit POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
					${PROJECT_SOURCE_DIR}/vendor/libgit2/bin/git2.dll
					${CMAKE_CURRENT_BINARY_DIR}/git2.dll)