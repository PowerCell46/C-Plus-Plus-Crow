cmake_minimum_required(VERSION 3.29)
project(C__ProjectCLion)

set(CMAKE_CXX_STANDARD 26)

add_executable(C__ProjectCLion main.cpp
        crow_all.h
        src/QuestionRelated/QuestionController.h
        src/QuestionRelated/QuestionController.cpp
        src/SubmissionRelated/SubmissionController.cpp
        src/SubmissionRelated/SubmissionController.h
        src/Common/Constants.cpp
        src/Common/Constants.h
        src/UsersRelated/UserController.cpp
        src/UsersRelated/UserController.h
)

find_package(asio CONFIG REQUIRED)
target_link_libraries(C__ProjectCLion PRIVATE asio::asio ws2_32 mswsock)

## Define SQLAPI++ paths
#set(SQLAPI_INCLUDE_DIR "C:\\Users\\HP ZBook 17 G5\\Downloads\\SQLAPI\\include")  # Path to SQLAPI headers
#set(SQLAPI_LIB_DIR "C:\\Users\\HP ZBook 17 G5\\Downloads\\SQLAPI\\lib")          # Path to SQLAPI library
#
## Add the include directory for SQLAPI
#target_include_directories(C__ProjectCLion PRIVATE "${SQLAPI_INCLUDE_DIR}")
#
## Link the SQLAPI++ library
#target_link_libraries(C__ProjectCLion
#        "C:\\Users\\HP ZBook 17 G5\\Downloads\\SQLAPI\\mingw-w64-x86_64-4.8.5-posix-seh-rt_v4-rev0\\lib\\libsqlapiddll.a"
#)
