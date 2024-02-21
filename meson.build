project(
    'ell',
    'cpp',
    version : '0.1',
    default_options : ['warning_level=3', 'cpp_std=c++14'],
)

cc = meson.get_compiler('cpp')

ell_api_dependency = declare_dependency(
    include_directories : include_directories(['includes/']),
)

executable(
    'ell',
    'src/main.cpp',
    'src/injector.cpp',
    dependencies: [
    ell_api_dependency,
    cc.find_library('dl'),
    cc.find_library('stdc++fs'),

    ],
    include_directories: include_directories(['src/include']),
    install : true
)