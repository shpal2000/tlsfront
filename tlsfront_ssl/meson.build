incdirs = include_directories(['../tlspack_socket/'
                                , '../tlspack_app/'
                                , '../subprojects/'])

executable('tlsfront_ssl.exe'
            , sources : [ 'tlsfront_ssl_socket.cpp'
                            , 'tlsfront_ssl_session.cpp'
                            , 'tlsfront_ssl_app.cpp'
                            , 'tlsfront_ssl_main.cpp']
            , dependencies: [openssl, nlohmann_json_dep]
            , include_directories : [incdirs]
            , link_with : [ev_socklib, tlspack_applib]
            , build_rpath : '/rundir/lib'
            , install_rpath : '/rundir/lib'
            , install_dir : '/srcdir/imgdir/'
            , install : true)