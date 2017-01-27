cmake_minimum_required (VERSION 2.8.11)
project (Crunch)
set(CMAKE_CXX_FLAGS "-std=c++11 -fno-exceptions")

option(BuildSubmodules "BuildSubmodules" OFF)
option(AddTests "AddTests" ON)

if(BuildSubmodules)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Submodules/Stick)
else()
    include_directories (${CMAKE_CURRENT_SOURCE_DIR} /usr/local/include ${CMAKE_INSTALL_PREFIX}/include)
endif()

link_directories(/usr/local/lib)

set (CRUNCHDEPS Stick pthread)

set (CRUNCHINC 
Crunch/Bezier.hpp
Crunch/Circle.hpp
Crunch/Color1.hpp
Crunch/Color3.hpp
Crunch/Color4.hpp
Crunch/Colors.hpp
Crunch/CommonFunc.hpp
Crunch/Constants.hpp
Crunch/ExponentialFunc.hpp
Crunch/GeometricFunc.hpp
Crunch/IntersectionResult.hpp
Crunch/Line.hpp
Crunch/LineSegment.hpp
Crunch/Matrix2.hpp
Crunch/Matrix3.hpp
Crunch/Matrix4.hpp
Crunch/MatrixFunc.hpp
Crunch/NumericalFunc.hpp
Crunch/PerlinNoise.hpp
Crunch/Quaternion.hpp
Crunch/QuaternionFunc.hpp
Crunch/Randomizer.hpp
Crunch/Rectangle.hpp
Crunch/RectanglePacker.hpp
Crunch/StringConversion.hpp
Crunch/TiledFrustum.hpp
Crunch/TrigonometryFunc.hpp
Crunch/Tween.hpp
Crunch/UtilityFunc.hpp
Crunch/Vector2.hpp
Crunch/Vector3.hpp
Crunch/Vector4.hpp
)

if(BuildSubmodules)
    set(PrevAddTests ${AddTests})
    set(AddTests OFF)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Submodules/Stick)
    set(AddTests ${PrevAddTests})
endif()

install (FILES ${CRUNCHINC} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/Crunch)

if(AddTests)
    add_subdirectory(Tests)
endif()
