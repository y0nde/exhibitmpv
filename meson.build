project('mpvapp', 'cpp', default_options : ['cpp_std=c++20'])

incdir = include_directories('/Users/yonde/Packages/boost/include')

#mpv_header = include_directories('/opt/homebrew/include')

cc = meson.get_compiler('cpp')
#mpv_dep = cc.find_library(
#    'mpv',
#    has_headers: ['mpv/client.h'],
#    dirs: ['/opt/homebrew/lib'],
#    header_include_directories: mpv_header,
#  )
#mpv_dep = = declare_dependency(
  #link_args : ['-L/opt/homebrew/lib', '-lmpv'],
  #include_directories : ['/opt/homebrew/include']
  #)

#executable('mpvapp', 'main.cpp',
  #dependencies : [],
  #include_directories: [])

executable('mpvapp', 
  'main.cpp',
  'command.cpp',
  'commandsender.cpp',
  'scheduler.cpp',
  'schedulereader.cpp',
  'timer.cpp',
  dependencies : [],
  include_directories: [incdir])
