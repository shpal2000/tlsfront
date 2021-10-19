project('tlsfront', 'c', 'cpp',
  version : '1.0',
  default_options : ['warning_level=3'
                      , 'cpp_std=c++17'])

openssl = dependency('openssl')
incdirs = include_directories(['./tlspack-socket/'])

subdir ('tlspack-socket')

executable('tlsfront.exe'
            , sources : [ 'main.cpp']
            , dependencies: [openssl]
            , include_directories : [incdirs]
            , link_with : [ev_socklib]
            , build_rpath : '/rundir/lib'
            , install_rpath : '/rundir/lib'
            , install_dir : '/srcdir/imgdir/'
            , install : true)