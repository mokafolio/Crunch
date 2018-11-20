project('Crunch', 'cpp', default_options : ['cpp_std=c++14'])

# disable this bogus warning (should be deprecated in newer clang versions)
add_global_arguments('-Wno-missing-braces', '-fno-exceptions', language: 'cpp')

crunchInc = [
    'Crunch/Bezier.hpp',
    'Crunch/Circle.hpp',
    'Crunch/Color1.hpp',
    'Crunch/Color3.hpp',
    'Crunch/Color4.hpp',
    'Crunch/Colors.hpp',
    'Crunch/CommonFunc.hpp',
    'Crunch/Constants.hpp',
    'Crunch/ExponentialFunc.hpp',
    'Crunch/GeometricFunc.hpp',
    'Crunch/IntersectionResult.hpp',
    'Crunch/Line.hpp',
    'Crunch/LineSegment.hpp',
    'Crunch/Matrix2.hpp',
    'Crunch/Matrix3.hpp',
    'Crunch/Matrix32.hpp',
    'Crunch/Matrix4.hpp',
    'Crunch/MatrixFunc.hpp',
    'Crunch/NumericalFunc.hpp',
    'Crunch/PerlinNoise.hpp',
    'Crunch/Quaternion.hpp',
    'Crunch/QuaternionFunc.hpp',
    'Crunch/Randomizer.hpp',
    'Crunch/Rectangle.hpp',
    'Crunch/RectanglePacker.hpp',
    'Crunch/StringConversion.hpp',
    'Crunch/TiledFrustum.hpp',
    'Crunch/TrigonometryFunc.hpp',
    'Crunch/Tween.hpp',
    'Crunch/UtilityFunc.hpp',
    'Crunch/Vector2.hpp',
    'Crunch/Vector3.hpp',
    'Crunch/Vector4.hpp'
]

incDirs = include_directories('.')

install_headers(crunchInc, subdir: 'Crunch')

if get_option('buildSubmodules') == false
    stickDep = meson.get_compiler('cpp').find_library('Stick')
    crunchDeps = [stickDep, dependency('threads')]
else
    stickProj = subproject('Stick')
    crunchDeps = stickProj.get_variable('stickDep')
endif

subdir('Tests')
