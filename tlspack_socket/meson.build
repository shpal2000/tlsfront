openssl = dependency('openssl')
ev_socklib = shared_library('ev_sock'
                            , sources : [ 'ev_socket.cpp', 'ev_app.cpp']
                            , dependencies: [openssl]
                            , include_directories : []
                            , install_rpath : '/usr/lib'
                            , install_dir : '/workspaces/tlsfront/deploy'
                            , install : true)

