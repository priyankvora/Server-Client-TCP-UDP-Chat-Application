import socket

s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

data = "Hello server, this is my ip and port no : "

addr = ("localhost",20000)

s.sendto(data,addr)


