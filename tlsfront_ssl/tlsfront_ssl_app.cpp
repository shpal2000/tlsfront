#include "tlsfront_ssl_app.hpp"
#include "tlsfront_ssl_socket.hpp"
#include "tlsfront_ssl_session.hpp"


tlsfront_ssl_app::tlsfront_ssl_app(tlsfront_ssl_cfg* cfg, tlsfront_ssl_stats* gstats)
{
    ev_socket::set_sockaddr (&m_front_addr
                            , cfg->front_ip.c_str()
                            , htons(cfg->front_port));

    ev_socket::set_sockaddr (&m_back_addr
                            , cfg->back_ip.c_str()
                            , htons(cfg->back_port));

    ev_socket::set_sockaddr (&m_local_addr
                            , cfg->front_ip.c_str()
                            , 0);

    m_sock_opt.rcv_buff_len = 0;
    m_sock_opt.snd_buff_len = 0;

    m_stats_arr.push_back(&m_stats);
    m_stats_arr.push_back(gstats);

    m_init_ok = false;
    m_front_lsocket = nullptr;
    m_ssl_ctx = SSL_CTX_new(TLS_server_method());
    if (m_ssl_ctx) 
    {
        SSL_CTX_set_min_proto_version (m_ssl_ctx, SSL3_VERSION);
        SSL_CTX_set_max_proto_version (m_ssl_ctx, TLS1_3_VERSION);
        SSL_CTX_set_mode(m_ssl_ctx, SSL_MODE_ENABLE_PARTIAL_WRITE);
        SSL_CTX_set_session_cache_mode(m_ssl_ctx, SSL_SESS_CACHE_CLIENT);
        SSL_CTX_set_session_id_context(m_ssl_ctx
                                            , (unsigned char*)this
                                            , sizeof(void*)); 
        SSL_CTX_set1_groups_list(m_ssl_ctx, "P-521:P-384:P-256");
        SSL_CTX_set_dh_auto(m_ssl_ctx, 1);

        const char* server_cert = "/workspaces/tlsfront/tlsfront_ssl/cert.pem";
        const char* server_key = "/workspaces/tlsfront/tlsfront_ssl/key.pem";

        std::ifstream f(server_cert);
        std::ostringstream ss;
        std::string str;
        ss << f.rdbuf();
        str = ss.str();

        BIO *bio = NULL;
        BIO *kbio = NULL;
        X509 *cert = NULL;
        bio = BIO_new_mem_buf((char *)str.c_str(), -1);
        cert = PEM_read_bio_X509(bio, NULL, 0, NULL);
        SSL_CTX_use_certificate (m_ssl_ctx, cert);

        std::ifstream f2(server_key);
        std::ostringstream ss2;
        std::string str2;
        ss2 << f2.rdbuf();
        str2 = ss2.str();
        kbio = BIO_new_mem_buf(str2.c_str(), -1);
        EVP_PKEY *key = NULL;
        key = PEM_read_bio_PrivateKey(kbio, NULL, 0, NULL);
        SSL_CTX_use_PrivateKey(m_ssl_ctx, key);

        BIO_free(bio);
        BIO_free(kbio);
        EVP_PKEY_free(key);
        X509_free(cert);

        m_front_lsocket
            = (tlsfront_ssl_socket*) new_tcp_listen (&m_front_addr
                                                    , 1000
                                                    , &m_stats_arr
                                                    , &m_sock_opt);

    }

    if (m_ssl_ctx && m_front_lsocket)
    {
        m_init_ok = true;
    }
}


tlsfront_ssl_app::~tlsfront_ssl_app()
{

}


void tlsfront_ssl_app::run_iter(bool tick_sec)
{
    tlspack_app::run_iter (tick_sec);

    if (tick_sec)
    {
        m_stats.tick_sec();
    }
}

ev_socket* tlsfront_ssl_app::alloc_socket()
{
    return new tlsfront_ssl_socket(m_ssl_ctx);
}

void tlsfront_ssl_app::free_socket(ev_socket* ev_sock)
{
    delete ev_sock;
}
