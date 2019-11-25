


import socket
import sys
import time

# req/app_name/socket_number/request_body

def pack_request(message: str):
    request = 'req:Hello_World_API:' + message
    return request


def SendRequest(sockfd):

    value = pack_request('Hello API')
#    sockfd.send('USER'.encode('utf-8'))
    time.sleep(1)
    sockfd.send(value.encode('utf-8'))
    response = sockfd.recv(4096)
    print('Response is : ', response.decode('utf-8'))

def init_socket(server: str, port: int) -> None:

    sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    sockfd.connect((server, port))

    SendRequest(sockfd)


if __name__ == '__main__':


    init_socket('127.0.0.1', 4212)

    
