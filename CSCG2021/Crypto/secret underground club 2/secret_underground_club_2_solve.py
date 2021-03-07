from Crypto.PublicKey import RSA
import math

def main():
    #https://crypto.stackexchange.com/questions/18631/chosen-plaintext-attack-on-textbook-rsa-decryption
    #https://youtu.be/ZjYzrn8M3w4
    #https://asecuritysite.com/encryption/c_c
    
    #Most likely this is a chosen chipertext attack against plain RSA,
    #as no hash is used

    #Note that 10001 in hex is 65537 in decimal
    e = int("10001", 16)
    #Input given random n variable
    n = int(input("n="), 16)

    #Input message for which the signature will be generated
    #Convert message to hex

    message = int(input("Input challenge="), 16)

    #Blinding value "r" to that it won't be detected by the oracle
    #It needs to be gcd(r,n) = 1
    r = int("2", 16)
    if math.gcd(r,n) != 1:
        return(1)
    c2 = message * (pow(r, e, n))

    print(f"Blinded message={c2:x}\n")

    #m1 is the answer obtained by the oracle.
    #In this case the signature for the blinded message
    m1 = input("Answer by oracle=")

    #Now compute m = m1*r^(-1) where m is the message
    #This step will de-blind the messeage, thus giving us the signature for the message
    m = int(m1,16)*(pow(r,-1, n))

    print(f"Signature for:{message:x}\n")
    print(hex(int(m)))

if __name__ == '__main__':
    main()
