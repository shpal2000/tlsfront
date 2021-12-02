FROM ubuntu:focal
ENV DEBIAN_FRONTEND=noninteractive
ARG USERNAME=tlsfront
ARG USER_UID=1000
ARG USER_GID=$USER_UID
RUN apt-get update \
    && apt-get -yq install apt-utils \
    && apt-get -yq install mongodb \
    #
    # Verify git, process tools, lsb-release (common in install instructions for CLIs) installed
    && apt-get -yq install git iproute2 procps lsb-release \
    # Install C++ tools
    && apt-get -yq install build-essential cmake cppcheck valgrind \
    #
    && apt-get -yq install iputils-ping netcat tcpdump \
    && mv /usr/sbin/tcpdump /usr/bin/tcpdump \
    #
    && apt-get -yq install pkg-config \
    && apt-get -yq install python3-pip meson curl \
    && apt-get -yq install vim \
    && apt-get -yq install libssl-dev \
    && apt-get -yq install openssh-client sshpass net-tools \
    && apt-get -yq install iptables \
    #
    && cd / \
    && curl https://www.openssl.org/source/openssl-1.1.1d.tar.gz -o ./openssl-1.1.1d.tar.gz \
    && tar -xzvf ./openssl-1.1.1d.tar.gz \
    && cd openssl-1.1.1d \
    && ./config --prefix=/usr/local/ssl --openssldir=/usr/local/ssl shared zlib enable-ssl3 enable-ssl3-method \
    && make \
    && make install_sw \
    && echo "/usr/local/ssl/lib" > /etc/ld.so.conf.d/openssl-1.1.1d.conf \
    && mv /usr/bin/c_rehash /usr/bin/c_rehash.BEKUP \
    && mv /usr/bin/openssl /usr/bin/openssl.BEKUP \
    && cp /usr/local/ssl/bin/c_rehash /usr/bin/c_rehash \ 
    && cp /usr/local/ssl/bin/openssl /usr/bin/openssl \
    #
    && groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get install -yq sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME\
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && sudo ldconfig -v \
    #
    && pip3 install requests pytest aiohttp pymongo \
    # Clean up
    && apt-get autoremove -yq \
    && apt-get clean -yq \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /usr/local/tlsfront/lib
COPY ./*.so /usr/local/tlsfront/lib/
RUN echo "/usr/local/tlsfront/lib" > /etc/ld.so.conf.d/tlsfront.conf
RUN ldconfig -v
COPY ./*.exe /usr/local/bin/
RUN mkdir -p /tlsfront_web/
COPY web/ /tlsfront_web/

ENV DEBIAN_FRONTEND=