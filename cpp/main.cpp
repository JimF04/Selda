#include <iostream>
#include <string>
#include <winsock2.h>
#include <json/json.h> // Librería jsoncpp

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[1024];

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error al inicializar Winsock." << std::endl;
        return 1;
    }

    // Crear el socket del servidor
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket del servidor: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Configurar la dirección del servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080); // Puerto 8080

    // Vincular el socket a la dirección y el puerto
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error al vincular el socket del servidor: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Escuchar las conexiones entrantes
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error al escuchar las conexiones entrantes: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Servidor esperando conexiones en el puerto 8080..." << std::endl;

    // Aceptar la conexión entrante
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error al aceptar la conexión entrante: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Cliente conectado desde " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;

    // Leer los datos enviados por el cliente
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == SOCKET_ERROR) {
        std::cerr << "Error al leer los datos del cliente: " << WSAGetLastError() << std::endl;
    } else {
        buffer[bytesRead] = '\0'; // Agregar el carácter nulo al final de la cadena recibida
        std::cout << "Mensaje recibido del cliente: " << buffer << std::endl;

        // Procesar el mensaje JSON
        Json::CharReaderBuilder builder;
        Json::CharReader *reader = builder.newCharReader();
        Json::Value root;
        std::string errors;
        bool parsingSuccessful = reader->parse(buffer, buffer + bytesRead, &root, &errors);
        delete reader;

        if (!parsingSuccessful) {
            std::cerr << "Error al analizar el JSON: " << errors << std::endl;
        } else {
            if (root.isMember("wall_tracing")) {
                std::cout << "Realizando wall tracing..." << std::endl;

                // Implementa aquí la lógica de wall tracing
                // Por ejemplo, podrías calcular la trayectoria y enviar los resultados al cliente

                // Aquí se muestra un ejemplo de envío de datos de vuelta al cliente
                Json::Value response;
                response["result"] = "tracing_completed";
                Json::StreamWriterBuilder writerBuilder;
                std::ostringstream os;
                std::unique_ptr<Json::StreamWriter> writer(writerBuilder.newStreamWriter());
                writer->write(response, &os);
                std::string responseString = os.str();

                // Enviar la respuesta al cliente
                int bytesSent = send(clientSocket, responseString.c_str(), responseString.length(), 0);
                if (bytesSent == SOCKET_ERROR) {
                    std::cerr << "Error al enviar la respuesta al cliente: " << WSAGetLastError() << std::endl;
                }
            } else {
                std::cerr << "El JSON no contiene información para wall tracing." << std::endl;
            }

        }
    }

    // Cerrar los sockets
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
