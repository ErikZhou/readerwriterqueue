cmake_minimum_required(VERSION 3.9)
project(ReaderWriterQueue VERSION 1.0.0)
set (APP_NAME "${PROJECT_NAME}")

include(FetchContent)

FetchContent_Declare(
  readerwriterqueue
  GIT_REPOSITORY    https://github.com/cameron314/readerwriterqueue
  GIT_TAG           master
)

FetchContent_MakeAvailable(readerwriterqueue)

add_executable (${APP_NAME} main.cpp)
#add_library(my_target main.cpp)
#target_link_libraries(my_target PUBLIC readerwriterqueue)
target_link_libraries(${APP_NAME} PUBLIC readerwriterqueue)
