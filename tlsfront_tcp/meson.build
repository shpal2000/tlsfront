incdirs = include_directories(['../tlspack_socket/'
                                , '../tlspack_app/'
                                , '../subprojects/'])

executable('tlsfront_tcp.exe'
            , sources : [ 'tlsfront_tcp_socket.cpp'
                            , 'tlsfront_tcp_session.cpp'
                            , 'tlsfront_tcp_app.cpp'
                            , 'main.cpp']
            , dependencies: [openssl, nlohmann_json_dep]
            , include_directories : [incdirs]
            , link_with : [ev_socklib, tlspack_applib]
            , build_rpath : '/rundir/lib'
            , install_rpath : '/rundir/lib'
            , install_dir : '/srcdir/imgdir/'
            , install : true)