incdirs = include_directories(['../tlspack_socket/'
                                , '../tlspack_app/'
                                , '../subprojects/'])

executable('tlsserver.exe'
            , sources : [ 'tlsserver_socket.cpp'
                            , 'tlsserver_app.cpp'
                            , 'tlsserver_main.cpp']
            , dependencies: [openssl, nlohmann_json_dep]
            , include_directories : [incdirs]
            , link_with : [ev_socklib, tlspack_applib]
            , build_rpath : '/tlsfront/bin'
            , install_rpath : '/tlsfront/bin'
            , install_dir : '/workspaces/tlsfront/deploy'
            , install : true)