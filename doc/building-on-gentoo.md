# Gentoo building instructions

## Install

1. sudo layman -o https://raw.github.com/ddorian1/gentoo-freespeech-overlay/master/gentoo-freespeech-overlay.xml -a freespeech
1. sudo emerge -av freespeech

## Configuration & web gui

1. mkdir ~/.freespeech
1. echo -e "rpcuser=user\nrpcpassword=pwd" > ~/.freespeech/freespeech.conf
1. chmod 600 ~/.freespeech/freespeech.conf
1. git clone https://github.com/miguelfreitas/freespeech-html.git ~/.freespeech/html

## Start

1. freespeechd -rpcuser=user -rpcpassword=pwd
1. Open http://127.0.0.1:58432/index.html and use the user/pwd credentials
1. Create your account !
