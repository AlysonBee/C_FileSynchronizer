


import socket


def api_listener():

    sockfd = socket.socket(socket.AF_NET, socket.SOCK_STREAM)

    sockfd.connect(('127.0.0.1', 4242))

    while True:

        buff = sockfd.recv(4096)

