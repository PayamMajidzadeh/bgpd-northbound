FROM ubuntu

# ENV http_proxy "http://proxy1.altranit.corp.altran.com:8080"
# ENV https_proxy "https://proxy1.altranit.corp.altran.com:8080"

ENV TZ=Europe/Rome

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && apt-get upgrade -y
RUN apt-get install telnet git autoconf automake libtool make gawk libreadline-dev texinfo dejagnu pkg-config libpam0g-dev libjson-c-dev bison flex python-pytest python3-dev libncap-dev libyang-dev libgrpc-dev libgrpc++-dev libyangrpc-dev protobuf-compiler-grpc libcap-dev  python3-pip clang-format vim nano yang-tools -y
RUN pip3 install pytest
RUN pip3 install pyang

# RUN git config --global http.proxy http://proxy1.altranit.corp.altran.com:8080
# RUN git config --global https.proxy https://proxy1.altranit.corp.altran.com:8080

RUN git clone https://github.com/FRRouting/frr.git

WORKDIR /frr

RUN git switch stable/7.4

RUN ./bootstrap.sh
RUN ./configure    --prefix=/usr    --localstatedir=/var/run/frr    --sysconfdir=/etc/frr    --enable-exampledir=/usr/share/doc/frr    --enable-watchfrr    --enable-multipath=64    --enable-vtysh    --enable-shell-access    --disable-doc      --disable-ldpd    --disable-nhrpd       --disable-babeld        --disable-pimd    --disable-pbrd    --disable-fabricd    --disable-irdp    --disable-rusage    --disable-backtrace    --disable-time-check   --disable-bfdd    --disable-largefile    --enable-user=root    --enable-group=root --enable-shell-access --enable-grpc  --disable-rr-semantics \
  --with-yangmodelsdir=/yangmodels/
# For some reason, we can not load our cutom bgp YANG model if we desable other routing protocols
# TODO: find out why do we need them
#   --disable-ripd    --disable-ripngd    --disable-isisd     --disable-eigrpd 
RUN make -j 32 
RUN make install
# Copy frr-bgpd YANG model
COPY frr-queue/custom-yang/yang /yangmodels
COPY frr-queue/custom-yang/yang /frr/yang
COPY frr-queue/custom-yang/bgpd /frr/bgpd

# Make frr based on new changes
RUN make -j 32 -B
RUN make install

# Necessary folder and empty configuration files
RUN mkdir -p /etc/frr/conf/
RUN touch /etc/frr/vtysh.conf /etc/frr/frr.conf.sav /etc/frr/conf/zebra.conf /etc/frr/conf/bgpd.conf /etc/frr/conf/ospfd.conf /etc/frr/conf/ripd.conf /etc/frr/conf/eigrpd.conf
RUN install -m 775 -o root -g root -d /var/log/frr
RUN install -m 640 -o root -g root /frr/tools/etc/frr/daemons.conf /etc/frr/daemons.conf

# Copy the source
COPY frr-queue/eolo_tests /root/eolo_tests

# Our own config file
RUN cp /root/eolo_tests/daemons /root/daemons
RUN install -m 640 -o root -g root /root/daemons /etc/frr/daemons
# Allow forwarding
RUN echo "net.ipv4.ip_forward=1" >> /etc/sysctl.conf
RUN echo "net.ipv6.conf.all.forwarding=1" >> /etc/sysctl.conf

# Healthcheck script
RUN cp /root/eolo_tests/healthcheck.sh /usr/local/bin/healthcheck.sh
RUN chmod +x /usr/local/bin/healthcheck.sh
HEALTHCHECK CMD /usr/local/bin/healthcheck.sh || exit 1

# Start-up script
RUN cp /root/eolo_tests/docker-start /usr/sbin/docker-start
RUN chmod +x /usr/sbin/docker-start
ENTRYPOINT ["/usr/sbin/docker-start"]

# # Clean-up the repository
# RUN rm -rf /frr
# RUN apt clean

# Path for library
RUN echo "/usr/local/lib" >> /etc/ld.so.conf && ldconfig

WORKDIR "/root"
