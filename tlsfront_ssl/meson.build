incdirs = include_directories(['../tlspack_socket/', '../'])

executable('tlsfront_ssl.exe'
            , sources : [ 'tlsfront_ssl.cpp', 'app.cpp']
            , dependencies: [openssl, nlohmann_json_dep]
            , include_directories : [incdirs]
            , link_with : [ev_socklib]
            , build_rpath : '/rundir/lib'
            , install_rpath : '/rundir/lib'
            , install_dir : '/srcdir/imgdir/'
            , install : true)