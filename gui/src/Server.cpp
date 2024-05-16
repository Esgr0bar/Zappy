/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** Main
*/

#include "Server.hpp"

Gui::Server::Server()
{
    _map = {};
    _sockfd = 0;
    _player = {};
    _team = {};
}

Gui::Server::~Server()
{
}

int Gui::Server::ConnectServer(int port, std::string ip)
{
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("ERROR opening socket\n");
        throw std::exception();
        return (84);
    }
    server = gethostbyname(ip.c_str());
    if (server == NULL) {
        printf("ERROR, no such host\n");
        throw std::exception();
        return (84);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
        (char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length
    );
    serv_addr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("ERROR connecting\n");
        throw std::exception();
        return (84);
    }
    this->_sockfd = sockfd;
    return 0;
}

int Gui::Server::SendCommand(std::string command)
{
    int n;
    n = write(this->_sockfd, command.c_str(), command.length());
    if (n < 0) {
        throw std::invalid_argument("ERROR writing to socket\n");
        return (84);
    }
    return (0);
}

std::vector<int> getNumberFromString(std::string s) {
   std::stringstream str_strm;
   str_strm << s;
   std::string temp_str;
   int temp_int;
   std::vector<int> result;
   while(!str_strm.eof()) {
      str_strm >> temp_str;
      if(std::stringstream(temp_str) >> temp_int) {
        result.push_back(temp_int);
      }
      temp_str = "";
   }
   return result;
}

void Gui::Server::GetMap()
{
    try {
        this->SendCommand("msz\n");
        std::string s = this->ReceiveCommand();
        _map = getNumberFromString(s);
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void Gui::Server::ContentTile(int x, int y)
{
    try {
        this->SendCommand("bct " + std::to_string(x) + " " + std::to_string(y) + "\n");
        std::string s = this->ReceiveCommand();
        if (s.find("bct") != std::string::npos) {
            _tile = getNumberFromString(s);
            _tile = getNumberFromString(s);
            _tile.erase(_tile.begin());
            _tile.erase(_tile.begin());
        }
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

std::vector<int> static PinGetArgs(std::string str)
{
    str.erase(0, 4);
    std::vector<int> result = {0};
    std::string word = "";

    for (unsigned long i = 0; i < str.length(); i++) {
        if (str[i] == ' ' || str[i] == '\n') {
            result.push_back(std::stoi(word));
            word = "";
        } else
            word += str[i];
    }
    return result;
}

void Gui::Server::PlayerPosition(std::string player)
{
    try {
        this->SendCommand("ppo " + player + "\n");
        std::string s = this->ReceiveCommand();
        if (s.find("ppo") != std::string::npos){
            std::vector<int> result = PinGetArgs(s);
            Gui::Map::e_orientation o = result.at(4) == 1 ? Gui::Map::e_orientation::NORTH : result.at(4) == 2 ? Gui::Map::e_orientation::EAST : result.at(4) == 3 ? Gui::Map::e_orientation::SOUTH : Gui::Map::e_orientation::WEST;
            _Map.UpdatePlayerPosition(result.at(1), result.at(2), result.at(3), o);
        }
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void Gui::Server::PlayerInventory(std::string player)
{
    try {
        this->SendCommand("pin " + player + "\n");
        std::string s = this->ReceiveCommand();
        if (s.find("pin") != std::string::npos) {
            std::vector<int> result = PinGetArgs(s);
            _Map.UpdatePlayerInventory(result.at(0), result.at(1), result.at(2), result.at(3), result.at(4), result.at(5), result.at(6), result.at(7));
        }
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void Gui::Server::PlayerLevel(std::string player)
{
    try {
        this->SendCommand("plv " + player + "\n");
        std::string s = this->ReceiveCommand();
        if (s.find("plv") != std::string::npos){
            std::vector<int> result = PinGetArgs(s);
            _Map.UpdatePlayerLevel(result.at(1), result.at(2));
        }
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

std::string Gui::Server::ReceiveCommand()
{
    char buffer[1024];
    int n;
    bzero(buffer, 1024);
    int flags = fcntl(this->_sockfd, F_GETFL, 0);
    fcntl(this->_sockfd, F_SETFL, flags & ~O_NONBLOCK);
    n = read(this->_sockfd, buffer, 1024);
    buffer[n] = '\0';
    if (n < 0) {
        throw std::invalid_argument("ERROR reading from socket\n");
    }
    findPnw(buffer);
    return buffer;
}

std::string Gui::Server::ReceiveCommandNonBlock()
{
    static int c = 0;
    char *buffer = new char[1024];
    bzero(buffer, 1024);
    int flags = fcntl(this->_sockfd, F_GETFL, 0);
    fcntl(this->_sockfd, F_SETFL, flags | O_NONBLOCK);
    int n = read(this->_sockfd, buffer, 1024);
    //buffer[n + 1] = '\0';
    if (n < 0) {
        c++;
        if (c == 1)
            return "end";
    }
    return buffer;
}

void Gui::Server::TimeUnit()
{
    try
    {
        this->SendCommand("sgt\n");
        this->ReceiveCommand();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Gui::Server::TimeUnitModification(int time)
{
    try
    {
        this->SendCommand("sst " + std::to_string(time) + "\n");
        this->ReceiveCommand();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Gui::Server::NameTeam()
{
    try
    {
        this->SendCommand("tna\n");
        std::string s = this->ReceiveCommand();
        std::string s2 = this->ReceiveCommand();
        std::string delimiter = "\n";
        size_t pos = 0;
        std::string token;
        while ((pos = s2.find(delimiter)) != std::string::npos) {
            token = s2.substr(0, pos);
            token.erase(0, 4);
            if (token == "end")
                break;
            _team.push_back(token);
            s2.erase(0, pos + delimiter.length());
        }
        s.erase(0, 4);
        _team.push_back(s);
        _team.push_back(s2);
        _team.pop_back();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Gui::Server::GetAllMap()
{
    try
    {
        this->SendCommand("mct\n");
        std::string s = this->ReceiveCommand();
        _tile = getNumberFromString(s);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

std::tuple<std::vector<int>, std::string> static PnwGetArgs(std::string s)
{
    std::vector<int> result;
    std::string team;
    std::string delimiter = " ";
    std::string token;
    int spcNbr = 0;
    s.erase(0, 4);
    unsigned long i = 0;

    for (; spcNbr != 5; i++) {
        if (s[i] == ' ') {
            result.push_back(std::stoi(token));
            token.clear();
            spcNbr++;
        } else {
            token += s[i];
        }
    }
    for (; i < s.length() - 1; i++) {
        team += s[i];
    }

    return std::make_tuple(result, team);
}

void Gui::Server::findPnw(std::string s)
{
    if (s.find("pnw") != std::string::npos) {
        std::tuple<std::vector<int>, std::string> result = PnwGetArgs(s);
        Gui::Map::e_orientation o = std::get<0>(result).at(2) == 0 ? Gui::Map::e_orientation::NORTH : std::get<0>(result).at(2) == 2 ? Gui::Map::e_orientation::EAST : std::get<0>(result).at(2) == 3 ? Gui::Map::e_orientation::SOUTH : Gui::Map::e_orientation::WEST;
        _player.push_back(std::get<0>(result).at(0));
        _Map.AddPlayer(std::get<0>(result).at(0), std::get<0>(result).at(1), std::get<0>(result).at(2), std::get<0>(result).at(4), o, std::get<1>(result));
    }
}

void Gui::Server::ListenServer()
{
    std::string s;
    s = this->ReceiveCommandNonBlock();
    if (s != "end") {
        findPnw(s);
        if (s.find("pbc") != std::string::npos) {
            int n = std::stoi(s.substr(4, 1));
            std::string message = s.substr(6, s.length() - 1);
            message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
            _Map.BroadcastPlayer(n, message);
        }
        if (s.find("pdi") != std::string::npos) {
            int n = std::stoi(s.erase(0, 4));
            _Map.DeadPlayer(n);
        }
        if (s.find("seg") != std::string::npos) {
            std::string team = s.substr(4, s.length() - 1);
            team.erase(std::remove(team.begin(), team.end(), '\n'), team.end());
            _Map.EndGame(team);
        }
        if (s.find("enw") != std::string::npos) {
            int spacenbr = 0;
            std::string playerId = "";
            for (unsigned long i = 0; spacenbr != 4; i++) {
                if (s[i] == ' ')
                    spacenbr++;
                else if (spacenbr == 2) {
                    playerId += s[i];
                }
            }
            _Map.LayEgg(stoi(playerId));
        }
    }
}