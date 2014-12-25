# Ubuntu / Debian building instructions

Tested on a pristine:
 - Ubuntu 13.10 amd64

## Install

1. sudo apt-get update
1. sudo apt-get install git autoconf libtool build-essential libboost-all-dev libssl-dev libdb++-dev libminiupnpc-dev automake
1. git clone https://github.com/miguelfreitas/freespeech-core.git
1. cd freespeech-core
1. ./autotool.sh
1. ./configure
1. make

## Configuration & web gui

1. mkdir ~/.freespeech
1. echo -e "rpcuser=user\nrpcpassword=pwd" > ~/.freespeech/freespeech.conf
1. chmod 600 ~/.freespeech/freespeech.conf
1. git clone https://github.com/miguelfreitas/freespeech-html.git ~/.freespeech/html

## Start

1. cd freespeech-core
1. ./freespeechd -rpcuser=user -rpcpassword=pwd -rpcallowip=127.0.0.1
1. Open http://127.0.0.1:58432/index.html and use the user/pwd credentials
1. Create your account !
