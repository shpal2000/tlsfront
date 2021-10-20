mkdir subprojects
cd subprojects
git clone https://github.com/nlohmann/json.git


meson build
ninja -C build


{
    "proxy_list" : [
        {
            "front_ip" : "12.12.50.1",
            "front_port" : 443,

            "cs_groups" : [
                {
                    "client_ip" : "127.0.0.1"
                    "server_ip" : "127.0.0.20",
                    "server_port" : 80
                }
            ]
        }
    ]
}