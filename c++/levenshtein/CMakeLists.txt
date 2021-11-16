cmake_minimum_required(VERSION 3.11)

project( Levenshtein )

add_executable(${PROJECT_NAME} main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(OpenMP)
find_package(Threads)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
