project('tlspack-socket', 'c', 'cpp',
  version : '1.0',
  default_options : ['warning_level=3'
                      , 'cpp_std=c++17'])

openssl = dependency('openssl')
ev_socklib = shared_library('ev_sock'
                            , sources : [ 'ev_socket.cpp', 'ev_app.cpp']
                            , dependencies: [openssl]
                            , include_directories : []
                            , install_rpath : '/rundir/lib'
                            , install_dir : '/srcdir/imgdir/'
                            , install : true)

