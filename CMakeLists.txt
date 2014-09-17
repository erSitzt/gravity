cmake_minimum_required(VERSION 2.8)

project(gravity)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)


INCLUDE_DIRECTORIES(
/usr/local/include
/usr/local/include/bullet
/usr/local/include/entityx
/home/ersitzt/libraries/SFML-2.1/include
/home/ersitzt/libraries/cereal/include
/home/ersitzt/lf/include
/home/ersitzt/lf/ext/freetype2/include
/home/ersitzt/lf/ext
/home/ersitzt/lf/ext/freetype2/include/freetype
/home/ersitzt/lf/ext/jpeglib
/home/ersitzt/lf/ext/libpng
/home/ersitzt/lf/ext/zlib
/home/ersitzt/lf/ext/ngplant
/home/ersitzt/ClionProjects/gravity
)

LINK_DIRECTORIES(
/usr/local/lib
/home/ersitzt/libraries/SFML-2.1/lib
)


LINK_LIBRARIES(
Lightfeather BulletDynamics BulletCollision LinearMath entityx sfml-audio sfml-system
)

FILE(GLOB MyCSources *.cpp)

ADD_EXECUTABLE(gravity ${MyCSources})




install(TARGETS gravity DESTINATION bin)