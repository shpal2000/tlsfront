incdirs = include_directories(['../tlspack_socket/', '../'])

executable('tlsfront_tcp.exe'
            , sources : [ 'tlsfront_tcp.cpp', 'app.cpp']
            , dependencies: [openssl, nlohmann_json_dep]
            , include_directories : [incdirs]
            , link_with : [ev_socklib]
            , build_rpath : '/rundir/lib'
            , install_rpath : '/rundir/lib'
            , install_dir : '/srcdir/imgdir/'
            , install : true)