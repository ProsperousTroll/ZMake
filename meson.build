project(
  'zmake',
  'cpp',
  default_options: ['default_library=static'],
)

inc = include_directories('include')
cpr_dep = dependency('cpr')

executable(
  'zmake',
  ['src/main.cc', 'src/zmake.cc'],
  include_directories: inc,
  dependencies: [cpr_dep]
)
