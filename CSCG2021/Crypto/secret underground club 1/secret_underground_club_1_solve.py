from Crypto.PublicKey import RSA

def main():
    #Note that 10001 in hex is 65537 in decimal
    e = int("10001", 16)
    #Input given random n variable
    n = int("cf835cd70abcc72105bb5a24d6ea6bd56bbcd765d7ebbf1c85aa7b358f7edf1a2e80745854121fc7c245df05bd5d5241b680523a45753580b7aaa2a41f42b3938473536c143f05cf9f346f37f1ef78cbe0ce4ba564660567b76d4965aec35d5cb8298b2c1678acfc1d43326e6b3daf4cc21205bbc31685fdf688abe8fb92ca61", 16)

    #Input message for which the signature will be generated
    message_raw = "AAAA"
    message = int(message_raw, 16)
    valid = pow(message, e, n)
    print(f"Message={valid:x}\n")
    print("Signature=" + message_raw)

if __name__ == '__main__':
    main()
