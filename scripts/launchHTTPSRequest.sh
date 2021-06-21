#!/bin/bash
display_usage()
{
    echo "Usage: ./launchHTTPSRequest <type> <port> <pathtocertificate>"
    echo "  <type>: Type of client to use:"
    echo "      \"curl\": Curl client with one time request (but many SSL info)"
    echo "      \"openssl\": OpenSSL client with possibility to send several request to server"
    echo "  <port>: The port of the server"
    echo "  <pathtocertificate>: The path to the key and certificate file"
    exit
}

# $1 -> port and $2 -> pathtocertificate
launchCurl() {
    echo "1 = $1 / 2 = $2"
    curl -v -k https://127.0.0.1:$1 -cacert $2
}

# $1 -> port and $2 -> pathtocertificate
launchOpenSSL() {
    openssl s_client -connect 127.0.0.1:$1 -cert $2 -key $2 -state -debug
}


if [ "$1" == "-h" ] || [ "$1" == "--help" ]
then
    display_usage
fi

if [ "$#" -ne 3 ]
then
    display_usage
else
    if [ "$1" == "curl" ]
    then
        launchCurl $2 $3
    elif [ "$1" == "openssl" ]
    then
        launchOpenSSL $2 $3
    else
        echo "Unknown client type" && exit
    fi
fi
