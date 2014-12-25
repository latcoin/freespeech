#
# Dockerfile for building Freespeech peer-to-peer micro-blogging
#
FROM ubuntu:14.04

# Install freespeech-core
RUN apt-get update
RUN apt-get install -y git autoconf libtool build-essential libboost-all-dev libssl-dev libdb++-dev libminiupnpc-dev && apt-get clean
#RUN git clone https://github.com/miguelfreitas/freespeech-core.git
ADD . /freespeech-core
RUN cd freespeech-core && \
    ./bootstrap.sh && \
    make

# Install freespeech-html
RUN git clone https://github.com/miguelfreitas/freespeech-html.git /freespeech-html

# Configure HOME directory
# and persist freespeech data directory as a volume
ENV HOME /root
VOLUME /root/.freespeech

# Run freespeechd by default
ENTRYPOINT ["/freespeech-core/freespeechd", "-rpcuser=user", "-rpcpassword=pwd", "-rpcallowip=172.17.42.1", "-htmldir=/freespeech-html", "-printtoconsole"]
EXPOSE 28332
