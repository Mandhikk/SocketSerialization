#include <SDL.h>
#include <SDL_net.h>
#include <iostream>

const int PORT = 12345;
const char* SERVER_IP = "127.0.0.1"; // Replace with the server's IP address

int main(int argc, char* argv[]) {
    if (SDL_Init(0) == -1 || SDLNet_Init() == -1) {
        std::cerr << "SDL or SDL_net initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    IPaddress ip;
    TCPsocket clientSocket;

    if (SDLNet_ResolveHost(&ip, SERVER_IP, PORT) == -1) {
        std::cerr << "SDLNet_ResolveHost failed: " << SDLNet_GetError() << std::endl;
        return 1;
    }

    clientSocket = SDLNet_TCP_Open(&ip);
    if (!clientSocket) {
        std::cerr << "SDLNet_TCP_Open failed: " << SDLNet_GetError() << std::endl;
        return 1;
    }

    char buffer[1024];
    int bytesRead = SDLNet_TCP_Recv(clientSocket, buffer, sizeof(buffer));
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "Server says: " << buffer << std::endl;
    }
    else {
        std::cerr << "Failed to receive data from the server." << std::endl;
    }

    SDLNet_TCP_Close(clientSocket);
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
