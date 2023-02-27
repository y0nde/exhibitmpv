project('mpvapp', 'cpp')

#incdir = include_directories('/opt/homebrew/include')

mpv_header = include_directories('/opt/homebrew/include')

cc = meson.get_compiler('cpp')
mpv_dep = cc.find_library(
    'mpv',
    has_headers: ['mpv/client.h'],
    dirs: ['/opt/homebrew/lib'],
    header_include_directories: mpv_header,
  )
#mpv_dep = = declare_dependency(
  #link_args : ['-L/opt/homebrew/lib', '-lmpv'],
  #include_directories : ['/opt/homebrew/include']
  #)
executable('mpvapp', 'main.cpp',
  dependencies : [mpv_dep],
  include_directories: mpv_header)
