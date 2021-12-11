project('tlsfront', 'c', 'cpp',
  version : '1.0',
  default_options : ['warning_level=3'
                      , 'cpp_std=c++17'])

openssl = dependency('openssl')
nlohmann_json_proj = subproject('json')
nlohmann_json_dep = nlohmann_json_proj.get_variable('nlohmann_json_dep')

subdir ('tlspack_socket')
subdir ('tlspack_app')
subdir ('tlsfront')
subdir ('tlsclient')
subdir ('tlsserver')