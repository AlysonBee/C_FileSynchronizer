


import socket


def init_api():

    sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sockfd.connect(('127.0.0.1', 4212))

    if sockfd:
        sockfd.send('USER:APPLICATION_NAME=Hello_World_API'.encode('utf-8'))
    return sockfd


def SendResponse(user_key: str, sockfd: int, payload: str):
    """Used to send a response to the requesting user.

    :param: user_key: The key that designates the requesting user's
        location.
    :param: sockfd: The socket number to send the response to.
    :param: payload: The information to send.
    """
    to_send = user_key + payload
    socket.send(payload)

if __name__ == '__main__':
    sockfd = init_api()

    while True:
        print('Waiting for a hello...')
        request = sockfd.recv(4096)
        print('Message received is ', request.decode('utf-8'))
        print('response received, calling you back')
        sockfd.send('Hello World Dude\n'.encode('utf-8'))
