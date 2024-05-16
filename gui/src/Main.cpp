/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** Main
*/

#include "Main.hpp"
#include "Map.hpp"
#include "RaylibWrapper/raylib-cpp.hpp"
#include <chrono>

template <
    class result_t   = std::chrono::milliseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

int main(int ac, char **av)
{
    auto start = std::chrono::steady_clock::now();
    std::string ip = "";
    std::string port = "";

    try {
        if (ac == 5) {
            port = av[2];
            ip = av[4];
        } else if (ac == 3) {
            port = av[2];
            ip = "localhost";
        } else {
            std::cout << "USAGE: ./zappy_ai -p port -h machine\nport\t\tis the port number\nmachine\t\tis the name of the machine; localhost by default" << std::endl;
            throw std::exception();
        }
    } catch (std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 84;
    }

    Gui::Server main;
    raylib::Rectangle inputIp(100, 130, 250, 30);
    raylib::Rectangle inputPort(100, 230, 250, 30);
    raylib::Rectangle connectButton(100, 300, 250, 30);
    int key = 0;
    bool mouseOnIp = false;
    bool mouseOnPort = false;
    while (!main._Map._Window.ShouldClose()) {
        key = GetKeyPressed();
        if (mouseOnIp) {
            if (key == KEY_BACKSPACE) {
                if (ip.size() > 0)
                    ip.pop_back();
            } else if (key == KEY_ENTER) {
                mouseOnIp = false;
            } else if (key != 0) {
                ip += key;
            }
        }
        if (mouseOnPort) {
            if (key == KEY_BACKSPACE) {
                if (port.size() > 0)
                    port.pop_back();
            } else if (key == KEY_ENTER) {
                mouseOnPort = false;
            } else if (key != 0) {
                port += key;
            }
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            mouseOnIp = false;
            mouseOnPort = false;
            if (inputIp.CheckCollision(raylib::Mouse::GetPosition())) {
                ip.clear();
                mouseOnIp = true;
            } else if (inputPort.CheckCollision(raylib::Mouse::GetPosition())) {
                port.clear();
                mouseOnPort = true;
            }
        }
        main._Map._Window.BeginDrawing();
        {
            main._Map._Window.ClearBackground(BLACK);
         
            inputIp.Draw(raylib::Color::White());
            inputPort.Draw(raylib::Color::White());

            if (mouseOnIp)
                inputIp.DrawLines(raylib::Color::Red());
            if (mouseOnPort)
                inputPort.DrawLines(raylib::Color::Red());

            raylib::DrawText("Zappy", 100, 30, 40, WHITE);
            raylib::DrawText("Ip:", 100, 100, 20, WHITE);
            raylib::DrawText(ip.c_str(), 110, 135, 20, BLACK);
            raylib::DrawText("Port:", 100, 200, 20, WHITE);
            raylib::DrawText(port.c_str(), 110, 235, 20, BLACK);
            connectButton.Draw(raylib::Color::White());
            raylib::DrawText("Connect", 150, 305, 20, BLACK);
            if (connectButton.CheckCollision(raylib::Mouse::GetPosition())) {
                connectButton.DrawLines(raylib::Color::Red());
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    break;
                }
            }
        }
        main._Map._Window.EndDrawing();
    }

    try {
        main.ConnectServer(std::stoi(port), ip);
    } catch (std::exception &e) {
        while (!main._Map._Window.ShouldClose()) {
            main._Map._Window.BeginDrawing();
            {
                main._Map._Window.ClearBackground(raylib::Color::Black());
                raylib::DrawText("Error while connecting to server !", 100, 100, 40, raylib::Color::Red());
                raylib::DrawText("Press ESCAPE to quit", 100, 150, 30, raylib::Color::Red());
            }
            main._Map._Window.EndDrawing();
        }
        std::cout << "Error: " << e.what() << std::endl;
        return 84;
    }
    main.SendCommand("GRAPHIC\n");
    main.ReceiveCommand();
    main.GetMap();

    for (int x = 0; x < main._map.at(0) ; x++) {
        for (int y = 0; y < main._map.at(1); y++) {
            main.ContentTile(x,y);
            main._Map.GenerateMap(x, y, main._tile.at(0), main._tile.at(1), main._tile.at(2), main._tile.at(3), main._tile.at(4), main._tile.at(5), main._tile.at(6));
        }
    }

    main._Map.InitCamera();
    main.NameTeam();
    main._Map.CreateTeams(main._team);
    main._Map.PlayWelcomeSound();
    main.ListenServer();
    while (!main._Map._Window.ShouldClose()) {
        main.ListenServer();
        if (main._Map._InMenu)
            main._Map.DrawMenu();
        else {
            main.ListenServer();
            if (since(start).count() > 3000) {
                for (unsigned long i = 0; i < main._player.size(); i++) {
                    main.PlayerPosition(std::to_string(main._player.at(i)));
                    main.PlayerLevel(std::to_string(main._player.at(i)));
                    main.PlayerInventory(std::to_string(main._player.at(i)));
                }
                for (int x = 0; x < main._map.at(0) ; x++) {
                    for (int y = 0; y < main._map.at(1); y++) {
                        main.ContentTile(x,y);
                        main._Map.UpdateMapTile(x, y, main._tile.at(0), main._tile.at(1), main._tile.at(2), main._tile.at(3), main._tile.at(4), main._tile.at(5), main._tile.at(6));
                    }
                }
                start = std::chrono::steady_clock::now();
            }
            main.ListenServer();
            main._Map.DrawMap();
        }
    }

    return 0;
}