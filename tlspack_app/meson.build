openssl = dependency('openssl')
nlohmann_json_proj = subproject('json')
nlohmann_json_dep = nlohmann_json_proj.get_variable('nlohmann_json_dep')

tlspack_applib = shared_library('tlspack_app'
                            , sources : ['tlspack_app.cpp']
                            , dependencies: [openssl, nlohmann_json_dep]
                            , include_directories : []
                            , install_rpath : '/rundir/lib'
                            , install_dir : '/srcdir/imgdir/'
                            , install : true)

