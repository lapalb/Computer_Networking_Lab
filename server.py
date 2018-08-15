import socket
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
addr='127.0.0.1'
port=5000

s.bind((addr,port))
s.listen(1)
while True:
    c,addr=s.accept()
    print("Got connection from", addr)
    c.send('Hi from server'.encode("Ascii"))
    c.send('Bye from server'.encode("Ascii"))
    c.close()
