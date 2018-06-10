FROM library/debian:jessie
MAINTAINER "nick@forward-loop.com"
RUN \
       apt-get update && \
       apt-get upgrade -y && \
       apt-get install -y \
        build-essential \
        curl \
        wget \
        git \
        python \
        python-pip \
        picocom \
        gcc-avr \
        avr-libc \
        avrdude \
        arduino-core
RUN \
        pip install ino

WORKDIR /floop
