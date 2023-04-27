from socket import socket
from telnetlib import Telnet

#I'm going to sleep. Count me some sheep: 4919
#Nice, now reset it. Bet you can't: 1/4919
#Okay, what's the magic word?
#Nope

xor = "anextremelycomplicatedkeythatisdefinitelyuselessss"
enc = "2& =$!-( <*+*( ?!&$$6,. )' $19 , #9=!1 <*=6 <6;66#"
dec = ""
for a,b in zip(xor, enc):
    dec += chr(ord(a) ^ ord(b))

print("The Flag is: " + dec)
#The Flag is: SHEEPSHEEPSHEEPSHEEPSHEEPSHEEPSHEEPSHEEPSHEEPSHEEP

sock = socket()
sock.connect(("challs.actf.co", 32760))
print(sock.recv(1024))
sock.send(b"4919\n")
print(sock.recv(1024))
sock.send(b"443\n")
print(sock.recv(1024))
sock.send(bytes(dec, "ascii"))
print(sock.recv(1024))