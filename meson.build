project('src', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

ell_api_dependency = declare_dependency(
    include_directories : include_directories(['includes/']),
)

executable('ell',
           'src/main.cpp',
           'src/injector.cpp',
           dependencies: [ell_api_dependency],
           include_directories: include_directories(['src/include']),
           install : true)