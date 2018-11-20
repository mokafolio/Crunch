tests = executable('CrunchTests', 'CrunchTests.cpp', 
    dependencies: crunchDeps, 
    include_directories : incDirs,
    cpp_args : '-fsanitize=address',
    link_args : '-fsanitize=address')
test('Crunch Tests', tests, workdir: meson.current_build_dir())