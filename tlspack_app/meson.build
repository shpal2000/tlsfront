openssl = dependency('openssl')
nlohmann_json_proj = subproject('json')
nlohmann_json_dep = nlohmann_json_proj.get_variable('nlohmann_json_dep')

incdirs = include_directories(['../tlspack_socket/', '../subprojects/'])

tlspack_applib = shared_library('tlspack_app'
                            , sources : ['tlspack_app.cpp']
                            , dependencies: [openssl, nlohmann_json_dep]
                            , link_with : [ev_socklib]
                            , include_directories : [incdirs]
                            , install_rpath : '/tlsfront/lib'
                            , install_dir : '/workspaces/tlsfront/deploy'
                            , install : true)
