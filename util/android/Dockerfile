FROM debian:jessie
MAINTAINER Emanuele Fornara "efornara@users.sourceforge.net"
RUN apt-get update
RUN apt-get install -y nano nvi make zip
ADD scripts /opt
RUN chmod 755 /opt/get_droid
RUN /opt/get_droid
RUN apt-get install -y gcc linuxdoc-tools
ENV CC65ANDROID_WORKDIR /opt
