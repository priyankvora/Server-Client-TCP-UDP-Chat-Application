import socket

s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

host = '127.0.0.1'
port = 20000

s.bind((host,port))

while True:
	data,addr = s.recvfrom(1024)
	print data.strip(),addr
