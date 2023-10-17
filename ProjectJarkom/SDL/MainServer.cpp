#include <SDL.h>
#include <SDL_net.h>
#include <iostream>

const int PORT = 12345;

int main(int argc, char* argv[]) {
    if (SDL_Init(0) == -1 || SDLNet_Init() == -1) {
        std::cerr << "SDL or SDL_net initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    IPaddress ip;
    TCPsocket serverSocket, clientSocket;
    const char* host = "127.0.0.1"; // Server's IP address

    if (SDLNet_ResolveHost(&ip, host, PORT) == -1) {
        std::cerr << "SDLNet_ResolveHost failed: " << SDLNet_GetError() << std::endl;
        return 1;
    }

    serverSocket = SDLNet_TCP_Open(&ip);
    if (!serverSocket) {
        std::cerr << "SDLNet_TCP_Open failed: " << SDLNet_GetError() << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    while (1) {
        clientSocket = SDLNet_TCP_Accept(serverSocket);
        if (clientSocket) {
            const char* message = "Hello, client!"; // Message to send to the client
            SDLNet_TCP_Send(clientSocket, message, strlen(message) + 1);
            SDLNet_TCP_Close(clientSocket);
        }
    }

    SDLNet_TCP_Close(serverSocket);
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
