import socket

filename = "data.txt"

# Set the server address and port
hostname=socket.gethostname()
IPAddr=socket.gethostbyname(hostname)
print(IPAddr)
server_address = ('', 3000)

# Create a socket object
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the server address and port
server_socket.bind(server_address)
while (True):
# Listen for incoming connections
    server_socket.listen(1)
    print('Server listening on port 3000...')

# Accept a client connection
    client_socket, client_address = server_socket.accept()
    print('Client connected:', client_address)
    client_socket.sendall("front".encode())

    data = client_socket.recv(1024)
# Receive and print data from the client
    if len(data.decode().split(",")) > 3:
        
        with open(filename, 'a') as file:
            file.write(data.decode())
        responsedata = data.decode().split(',')
        left = responsedata[0]
        right = responsedata[-1]
        front = responsedata[int(len(responsedata)/2)]
        if int(left) > 90:
            response = "left"
            client_socket.sendall(response.encode())
        elif int(front) > 90:
            response = "left"
            client_socket.sendall(response.encode())
        elif int(right) > 90:
            response = "left"
            client_socket.sendall(response.encode())
    else:
        response = "end"
        client_socket.sendall(response.encode())
        print("send front")
    
    print('Received data:', data.decode())

# Send a response to the client
response = 'Hello from the server!'
client_socket.sendall(response.encode())

# Close the client socket and server socket
client_socket.close()
server_socket.close()
