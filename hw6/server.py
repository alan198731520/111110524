import socket
import threading

clients = []

def handle_client(client_socket):
    while True:
        try:
            # 接收來自 client 的指令
            request = client_socket.recv(1024).decode('utf-8')
            if not request:
                break

            print(f"Received: {request}")

            # 執行指令並取得結果
            result = execute_command(request)
            
            # 將結果廣播給所有 client
            broadcast(result, client_socket)
        except ConnectionResetError:
            break

    client_socket.close()
    clients.remove(client_socket)

def broadcast(message, source_socket):
    for client in clients:
        if client != source_socket:
            try:
                client.send(message.encode('utf-8'))
            except:
                client.close()
                clients.remove(client)

def execute_command(command):
    try:
        # 模擬執行指令
        result = f"Executed: {command}"
        return result
    except Exception as e:
        return str(e)

def server_program():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('0.0.0.0', 9999))
    server.listen(5)
    print("Server started on port 9999")

    while True:
        client_socket, addr = server.accept()
        print(f"Accepted connection from {addr}")
        clients.append(client_socket)
        client_handler = threading.Thread(target=handle_client, args=(client_socket,))
        client_handler.start()

if __name__ == "__main__":
    server_program()
