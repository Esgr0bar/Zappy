/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** Map
*/

#include "Map.hpp"

#include <iostream>

Gui::Map::Map() :
    _Window(1280, 720, "Zappy"),
    _InMenu(false),
    _IsFirstView(false),
    _TileCollision({{{0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}}}),
    _PlayerCollision({{{0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}}}),
    _WelcomeSound("gui/resources/welcome.mp3"),
    _LevelupSound("gui/resources/levelup.mp3"),
    _BroadcastSound("gui/resources/broadcast.mp3"),
    _NewPlayerSound("gui/resources/newplayer.mp3"),
    _EndGameSound("gui/resources/endgame.mp3"),
    _EggLayedSound("gui/resources/egglay.mp3"),
    _MasterVolume(1.0f)
{
    _Window.SetTargetFPS(60);
    _GrassModel.Load(raylib::Mesh::Cube(2.0f, 2.0f, 2.0f));
    _GrassModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("gui/resources/grass.png");
    _Chat.push_back(std::tuple<e_chatType, std::string>(SERVER, "Welcome to Zappy!"));
}

Gui::Map::~Map()
{
}

void Gui::Map::GenerateMap(int x, int y, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
    _Tiles.push_back(
        {
            raylib::Vector3(x * 2, 0, y * 2),
            false,
            {
                food,
                linemate,
                deraumere,
                sibur,
                mendiane,
                phiras,
                thystame
            }
        }
    );
}

void Gui::Map::InitCamera()
{
    float gridPos = sqrt(_Tiles.size());
    float camPos = sqrt(_Tiles.size());

    raylib::Camera camera(
        raylib::Vector3((gridPos  * (-1)), (gridPos + 5), gridPos),
        raylib::Vector3(camPos, 0.0f, gridPos),
        raylib::Vector3(0.0f, 1.0f, 0.0f),
        45.0f,
        CAMERA_PERSPECTIVE
    );

    _Camera = camera;
}

void Gui::Map::DrawRessources(int actualTile)
{
    /* ----------------------------- Draw resources ----------------------------- */
    DrawSphere(
        {_Tiles[actualTile].position.GetX(), _Tiles[actualTile].position.GetY() + 1.0f, _Tiles[actualTile].position.GetZ()},
        (_Tiles[actualTile].resources.food) >= 10 ? 0.5f : (_Tiles[actualTile].resources.food) * 0.05,
        raylib::Color::Brown()
    ); 
    DrawSphere(
        {_Tiles[actualTile].position.GetX(), _Tiles[actualTile].position.GetY() + 1.0f, _Tiles[actualTile].position.GetZ() + 0.5f},
        (_Tiles[actualTile].resources.linemate) >= 10 ? 0.5f : (_Tiles[actualTile].resources.linemate) * 0.05,
        raylib::Color::Blue()
    );
    DrawSphere(
        {_Tiles[actualTile].position.GetX() + 0.5f, _Tiles[actualTile].position.GetY() + 1.0f, _Tiles[actualTile].position.GetZ()},
        (_Tiles[actualTile].resources.deraumere) >= 10 ? 0.5f : (_Tiles[actualTile].resources.deraumere) * 0.05,
        raylib::Color::Purple()
    );
    DrawSphere(
        {_Tiles[actualTile].position.GetX() + 0.5f, _Tiles[actualTile].position.GetY() + 1.0f, _Tiles[actualTile].position.GetZ() + 0.5f},
        (_Tiles[actualTile].resources.sibur) >= 10 ? 0.5f : (_Tiles[actualTile].resources.sibur) * 0.05,
        raylib::Color::Green()
    );
    DrawSphere(
        {_Tiles[actualTile].position.GetX(), _Tiles[actualTile].position.GetY() + 1.0f, _Tiles[actualTile].position.GetZ() - 0.5f},
        (_Tiles[actualTile].resources.mendiane) >= 10 ? 0.5f : (_Tiles[actualTile].resources.mendiane) * 0.05,
        raylib::Color::Yellow()
    );
    DrawSphere(
        {_Tiles[actualTile].position.GetX() - 0.5f, _Tiles[actualTile].position.GetY() + 1.0f, _Tiles[actualTile].position.GetZ()},
        (_Tiles[actualTile].resources.phiras) >= 10 ? 0.5f : (_Tiles[actualTile].resources.phiras) * 0.05,
        raylib::Color::Orange()
    );
    DrawSphere(
        {_Tiles[actualTile].position.GetX() - 0.5f, _Tiles[actualTile].position.GetY() + 1.0f, _Tiles[actualTile].position.GetZ() - 0.5f},
        (_Tiles[actualTile].resources.thystame) >= 10 ? 0.5f : (_Tiles[actualTile].resources.thystame) * 0.05,
        raylib::Color::Red()
    );

    /* ------------------- Draw tile's resources when selected ------------------ */
    if (_Tiles[actualTile].selected) {
        DrawCube(
            {_Tiles[actualTile].position.GetX(), _Tiles[actualTile].position.GetY(), _Tiles[actualTile].position.GetZ()},
            2.2f,
            2.2f,
            2.2f,
            raylib::Color::Red()
        );
        _Camera.EndMode();
        raylib::Text::Draw(
            "Ressources of the tile:\nFood: " + std::to_string(_Tiles[actualTile].resources.food)
            + "\nLinemate: " + std::to_string(_Tiles[actualTile].resources.linemate)
            + "\nDeraumere: " + std::to_string(_Tiles[actualTile].resources.deraumere)
            + "\nSibur: " + std::to_string(_Tiles[actualTile].resources.sibur)
            + "\nMendiane: " + std::to_string(_Tiles[actualTile].resources.mendiane)
            + "\nPhiras: " + std::to_string(_Tiles[actualTile].resources.phiras)
            + "\nThystame: " + std::to_string(_Tiles[actualTile].resources.thystame),
            10,
            10,
            20,
            raylib::Color::Black()
        );
        _Camera.BeginMode();
    }
}

void Gui::Map::DrawPlayers(int playerToDraw)
{
    /* -------------------- Player's inventory when selected -------------------- */
    _Camera.EndMode();
    {
        if (_Players[playerToDraw].selected) {
            raylib::Rectangle cameraButton(
                _Window.GetSize().GetX() - 180,
                250,
                100,
                30
            );

            raylib::DrawText("Player's inventory:\nFood: " + std::to_string(_Players[playerToDraw].inventory.food)
                + "\nLinemate: " + std::to_string(_Players[playerToDraw].inventory.linemate)
                + "\nDeraumere: " + std::to_string(_Players[playerToDraw].inventory.deraumere)
                + "\nSibur: " + std::to_string(_Players[playerToDraw].inventory.sibur)
                + "\nMendiane: " + std::to_string(_Players[playerToDraw].inventory.mendiane)
                + "\nPhiras: " + std::to_string(_Players[playerToDraw].inventory.phiras)
                + "\nThystame: " + std::to_string(_Players[playerToDraw].inventory.thystame),
                _Window.GetSize().GetX() - 200,
                10,
                20,
                raylib::Color::Black()
            );
            cameraButton.Draw(raylib::Color::White());
            raylib::DrawText("Camera", _Window.GetSize().GetX() - 170, 255, 20, raylib::Color::Black());
            if (cameraButton.CheckCollision(raylib::Mouse::GetPosition())) {
                if (raylib::Mouse::IsButtonPressed(MOUSE_LEFT_BUTTON)) {
                    _Camera.Update(CAMERA_FIRST_PERSON);
                    _IsFirstView = true;
                    _Camera.position = {_Players[playerToDraw].mouvement.position.GetX(), 5.0f, _Players[playerToDraw].mouvement.position.GetZ()};
                    _Camera.target = {_Players[playerToDraw].mouvement.position.GetX() + 0.1f, 4.0f, _Players[playerToDraw].mouvement.position.GetZ()};
                    _Players[playerToDraw].selected = false;
                    _Players[playerToDraw].firstView = true;
                }
            }
        }

        /* ----------------------- Handle first person camera ----------------------- */
        if (_Players[playerToDraw].firstView) {
            raylib::DrawText("Press 'C' to exit camera mode", 10, 10, 20, raylib::Color::Black());
            if (IsKeyPressed(KEY_C)) {
                _Camera.Update(CAMERA_THIRD_PERSON);
                _Players[playerToDraw].firstView = false;
                _IsFirstView = false;
                ResetCamera();
            }
        }
    }
    _Camera.BeginMode();

    /* -------------------- Player's animation -------------------- */
    if (CompareVector3(_Players[playerToDraw].mouvement.position, _Players[playerToDraw].mouvement.newPosition))
        _Players[playerToDraw].mouvement.isMoving = false;

    if (_Players[playerToDraw].mouvement.isMoving) {
        raylib::Vector3 mvmDiff(_Players[playerToDraw].mouvement.newPosition.GetX() - _Players[playerToDraw].mouvement.position.GetX(), 0.0f, _Players[playerToDraw].mouvement.newPosition.GetZ() - _Players[playerToDraw].mouvement.position.GetZ());
        _Players[playerToDraw].mouvement.position += (mvmDiff / 10);
        if (Absolue(mvmDiff.GetX()) < 0.01f && Absolue(mvmDiff.GetZ()) < 0.01f)
            _Players[playerToDraw].mouvement.position = _Players[playerToDraw].mouvement.newPosition;

        _Players[playerToDraw].anim.animFrame++;
        UpdateModelAnimation(_Players[playerToDraw].anim.model, _Players[playerToDraw].anim.anim[0], _Players[playerToDraw].anim.animFrame);
        if (_Players[playerToDraw].anim.animFrame >= _Players[playerToDraw].anim.anim[0].frameCount) _Players[playerToDraw].anim.animFrame = 0;
    } else {
        // Idling player animation
    }
    if (!_Players[playerToDraw].firstView)
        DrawModelEx(_Players[playerToDraw].anim.model, _Players[playerToDraw].mouvement.position, _Players[playerToDraw].rotation, 90.0f, raylib::Vector3(0.02f, 0.02f, 0.02f), _Players[playerToDraw].team.color);
}

void Gui::Map::CheckTileSelection(int tileToCheck)
{
    if (_IsFirstView) {
        _Tiles[tileToCheck].selected = false;
    } else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !IsCursorHidden()) {
        _TileCollision = GetRayCollisionBox(
            _Ray,
            {
                {_Tiles[tileToCheck].position.GetX(), _Tiles[tileToCheck].position.GetY(), _Tiles[tileToCheck].position.GetZ()},
                {_Tiles[tileToCheck].position.GetX() + 2, _Tiles[tileToCheck].position.GetY(), _Tiles[tileToCheck].position.GetZ() + 2}
            }
        );
        if (_TileCollision.hit)
            _Tiles[tileToCheck].selected = true;
        else
            _Tiles[tileToCheck].selected = false;
    }
}

void Gui::Map::CheckPlayerSelection(int playerToCheck)
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !IsCursorHidden()) {
        _PlayerCollision = GetRayCollisionBox(
            _Ray,
            {
                {_Players[playerToCheck].mouvement.position.GetX(), _Players[playerToCheck].mouvement.position.GetY(), _Players[playerToCheck].mouvement.position.GetZ() - 1},
                {_Players[playerToCheck].mouvement.position.GetX() + 4, _Players[playerToCheck].mouvement.position.GetY(), _Players[playerToCheck].mouvement.position.GetZ() + 1}
            }
        );
        if (_PlayerCollision.hit)
            _Players[playerToCheck].selected = true;
        else
            _Players[playerToCheck].selected = false;
    }
}

void Gui::Map::DrawMap()
{
        _Window.BeginDrawing();
        {
            _Window.ClearBackground(raylib::Color::Gray());

            if (IsKeyDown(KEY_SPACE)) {
                ShowCursor();
            } else {
                HideCursor();
                _Camera.Update(CAMERA_THIRD_PERSON);
            }
            if (IsKeyPressed(KEY_P))
                _InMenu = true;
            _Camera.BeginMode();
            {
                _Ray = raylib::Mouse::GetRay(raylib::Mouse::GetPosition(), _Camera);

                for (unsigned long i = 0; i < _Tiles.size(); i++) {
                    _GrassModel.Draw(_Tiles[i].position, 1.0f, raylib::Color::White());
                    CheckTileSelection(i);
                    DrawRessources(i);
                }
                for (unsigned long i = 0; i < _Players.size(); i++) {
                    DrawPlayers(i);
                    CheckPlayerSelection(i);
                }
            }
            _Camera.EndMode();
            DrawChat();
        }
        _Window.EndDrawing();
}

void Gui::Map::AddPlayer(int id, float x, float y, int level, e_orientation orientation, std::string team)
{
    unsigned int animCount = 0;
    t_teams tmp_team = {
        team,
        raylib::Color::Black()
    };

    t_anim anim = {
        LoadModel("gui/resources/player.iqm"),
        LoadModelAnimations("gui/resources/dance.iqm", &animCount),
        static_cast<int>(animCount),
        0
    };

    t_mouvement tmp_mouvement = {
        raylib::Vector3(x * 2, 1.0f, y * 2),
        raylib::Vector3(0.0f, 0.0f, 0.0f),
        false
    };

    for (unsigned long i = 0; i < _Teams.size(); i++) {
        if (_Teams[i].name == team) {
            tmp_team.color = _Teams[i].color;
            break;
        }
    }

    anim.model.transform = raylib::Matrix::RotateXYZ(raylib::Vector3(0.0f, 0.0f, 90.0f * static_cast<int>(orientation) * DEG2RAD));

    _Players.push_back(
        {
            id,
            tmp_mouvement,
            {
                -1.0f,
                0.0f,
                0.0f
            },
            orientation,
            tmp_team,
            anim,
            false,
            {0, 0, 0, 0, 0, 0, 0},
            false,
            level
        }
    );

    _Chat.push_back(std::tuple<e_chatType, std::string>(NEW_PLAYER, "[" + team + "] " + std::to_string(id) + " joined the game !"));
    _NewPlayerSound.Play();
}

void Gui::Map::CreateTeams(std::vector<std::string> teams)
{
    std::vector<raylib::Color> colors = {
        raylib::Color::Red(),
        raylib::Color::Blue(),
        raylib::Color::Green(),
        raylib::Color::Yellow(),
        raylib::Color::Orange(),
        raylib::Color::Purple(),
        raylib::Color::Pink(),
        raylib::Color::Brown(),
        raylib::Color::LightGray(),
        raylib::Color::DarkGray(),
        raylib::Color::White()
    };

    for (unsigned long i = 0; i < teams.size(); i++) {
        _Teams.push_back(
            {
                teams[i],
                colors[i]
            }
        );
    }
}

void Gui::Map::UpdatePlayerPosition(int id, float x, float y, e_orientation orientation)
{
    unsigned long player_id = 0;

    for (; player_id < _Players.size(); player_id++) {
        if (_Players[player_id].id == id)
            break;
    }
    if (!CompareVector3(_Players[player_id].mouvement.position, raylib::Vector3(x * 2, 1.0f, y * 2))) {
        _Players[player_id].mouvement.newPosition = raylib::Vector3(x * 2, 1.0f, y * 2);
        _Players[player_id].mouvement.isMoving = true;
    }
    if (_Players[player_id].orientation != orientation) {
        _Players[player_id].anim.model.transform = raylib::Matrix::RotateXYZ(raylib::Vector3(0.0f, 0.0f, 90.0f * static_cast<int>(orientation) * DEG2RAD));
        _Players[player_id].orientation = orientation;
    }
}

float Gui::Map::Absolue(float nbr)
{
    return abs(nbr);
}

void Gui::Map::UpdatePlayerInventory(int id, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
    unsigned long player_id = 0;

    for (; player_id < _Players.size(); player_id++) {
        if (_Players[player_id].id == id)
            break;
    }
    _Players[player_id].inventory.food = food;
    _Players[player_id].inventory.linemate = linemate;
    _Players[player_id].inventory.deraumere = deraumere;
    _Players[player_id].inventory.sibur = sibur;
    _Players[player_id].inventory.mendiane = mendiane;
    _Players[player_id].inventory.phiras = phiras;
    _Players[player_id].inventory.thystame = thystame;
}

void Gui::Map::UpdatePlayerLevel(int id, int level)
{
    unsigned long player_id = 0;

    for (; player_id < _Players.size(); player_id++) {
        if (_Players[player_id].id == id)
            break;
    }

    if (_Players[player_id].level != level) {
        _LevelupSound.Play();
        _Players[player_id].level = level;
        _Chat.push_back(std::tuple<e_chatType, std::string>(LEVEL_UP, "[" + _Players[player_id].team.name + "] " + std::to_string(id) + " is now level " + std::to_string(level)));
    }
}

bool Gui::Map::CompareVector3(raylib::Vector3 vec1, raylib::Vector3 vec2)
{
    if (vec1.x != vec2.x || vec1.y != vec2.y || vec1.z != vec2.z)
        return false;
    return true;
}

void Gui::Map::BroadcastPlayer(int id, std::string message)
{
    unsigned long player_id = 0;

    for (; player_id < _Players.size(); player_id++) {
        if (_Players[player_id].id == id)
            break;
    }
    _BroadcastSound.Play();
    _Chat.push_back(std::tuple<e_chatType, std::string>(BROADCAST, "[" + _Players[player_id].team.name + "] " + std::to_string(id) + ": " + message));
}

void Gui::Map::DrawMenu()
{
    if (IsCursorHidden())
        ShowCursor();
    _Window.BeginDrawing();
    {
        _Window.ClearBackground(raylib::Color::Black());

        raylib::DrawText("Zappy", 20, 10, 50, raylib::Color::White());

        raylib::DrawText("Window settings", 20, 100, 30, raylib::Color::White());

        raylib::Rectangle fullscreen = {30, 150, 200, 30};
        raylib::Rectangle windowed = {30, 200, 200, 30};

        raylib::Rectangle sound = {30, 300, 200, 30};
        raylib::Rectangle soundBar = {30, 300, _MasterVolume * 200.0f, 30};

        if (_Window.IsFullscreen()) {
            fullscreen.Draw(raylib::Color::Green());
            if (windowed.CheckCollision(raylib::Mouse::GetPosition())) {
                windowed.Draw(raylib::Color::DarkGray());
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    _Window.SetFullscreen(false);
                    _Window.SetSize(raylib::Vector2(1280, 720));
                }
            } else
                DrawRectangleRec(windowed, raylib::Color::Gray());
        } else {
            windowed.Draw(raylib::Color::Green());
            if (fullscreen.CheckCollision(raylib::Mouse::GetPosition())) {
                DrawRectangleRec(fullscreen, raylib::Color::DarkGray());
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    _Window.SetSize(raylib::Vector2(GetMonitorWidth(0), GetMonitorHeight(0)));
                    _Window.SetFullscreen(true);
                }
            } else
                fullscreen.Draw(raylib::Color::Gray());
        }

        if (sound.CheckCollision(raylib::Mouse::GetPosition())) {
            DrawRectangleRec(sound, raylib::Color::DarkGray());
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                _MasterVolume = (GetMouseX() - 30) / 200.0f;
                SetMasterVolume(_MasterVolume);
            }
        } else
            DrawRectangleRec(sound, raylib::Color::Gray());
        soundBar.Draw(raylib::Color::White());

        raylib::DrawText("Sound", 35, 270, 20, raylib::Color::White());

        raylib::DrawText("Fullscreen", 35, 150, 20, raylib::Color::White());
        raylib::DrawText("Windowed", 35, 200, 20, raylib::Color::White());

        if (IsKeyPressed(KEY_P))
            _InMenu = false;
    }
    _Window.EndDrawing();
}

void Gui::Map::UpdateMapTile(int x, int y, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
    for (unsigned long i = 0; i < _Tiles.size(); i++) {
        if (_Tiles[i].position.x == x && _Tiles[i].position.y == y) {
            _Tiles[i].resources.food = food;
            _Tiles[i].resources.linemate = linemate;
            _Tiles[i].resources.deraumere = deraumere;
            _Tiles[i].resources.sibur = sibur;
            _Tiles[i].resources.mendiane = mendiane;
            _Tiles[i].resources.phiras = phiras;
            _Tiles[i].resources.thystame = thystame;
            return;
        }
    }
}

void Gui::Map::ResetCamera()
{
    float gridPos = sqrt(_Tiles.size());
    float camPos = sqrt(_Tiles.size());

    _Camera.SetPosition(raylib::Vector3((gridPos  * (-1)), (gridPos + 5), gridPos));
    _Camera.SetTarget(raylib::Vector3(camPos, 0.0f, gridPos));
}

void Gui::Map::DrawChat()
{
    int chatBoxLength = 0;
    std::vector<raylib::Color> chatColor = {
        raylib::Color::Purple(),
        raylib::Color::White(),
        raylib::Color::Green(),
        raylib::Color::Gray(),
        raylib::Color::Maroon(),
        raylib::Color::SkyBlue(),
        raylib::Color::Gold()
    };

    if (_Chat.size() > 10)
        _Chat.erase(_Chat.begin());
    
    for (unsigned long i = 0; i < _Chat.size(); i++) {
        if (chatBoxLength < static_cast<int>(std::get<1>(_Chat[i]).length()))
            chatBoxLength = static_cast<int>(std::get<1>(_Chat[i]).length());
    }
    
    raylib::Rectangle chatBox = {0, _Window.GetHeight() - 220.0f, chatBoxLength * 11.5f, 220};

    chatBox.Draw(raylib::Color(0, 0, 0, 200));

    for (unsigned long i = _Chat.size(); i > 0; i--) {
        raylib::DrawText(std::get<1>(_Chat[i - 1]).c_str(), 10, _Window.GetHeight() - 30 - (20 * (_Chat.size() - i)), 20, chatColor.at(std::get<0>(_Chat[i - 1])));
    }
}

void Gui::Map::DeadPlayer(int id)
{
    unsigned long player_id = 0;

    for (; player_id < _Players.size(); player_id++) {
        if (_Players[player_id].id == id)
            break;
    }
    
    _Chat.push_back(std::tuple<e_chatType, std::string>(DEATH, "[" + _Players[player_id].team.name + "] " + std::to_string(id) + " is dead"));

    _Players.erase(_Players.begin() + player_id);
}

void Gui::Map::EndGame(std::string team)
{
    _EndGameSound.Play();

    _Chat.push_back(std::tuple<e_chatType, std::string>(SERVER, " "));
    _Chat.push_back(std::tuple<e_chatType, std::string>(SERVER, " "));
    _Chat.push_back(std::tuple<e_chatType, std::string>(SERVER, " "));
    _Chat.push_back(std::tuple<e_chatType, std::string>(SERVER, " "));
    _Chat.push_back(std::tuple<e_chatType, std::string>(SERVER, " "));
    _Chat.push_back(std::tuple<e_chatType, std::string>(END, "---------------------------------"));
    _Chat.push_back(std::tuple<e_chatType, std::string>(END, "Game is over!"));
    _Chat.push_back(std::tuple<e_chatType, std::string>(END, "Team " + team + " won the game!"));
    _Chat.push_back(std::tuple<e_chatType, std::string>(END, "---------------------------------"));
    _Chat.push_back(std::tuple<e_chatType, std::string>(SERVER, "Press ESC to quit the game"));
}

void Gui::Map::LayEgg(int playerId)
{
    unsigned long playerID = 0;

    for (unsigned long i = 0; i < _Players.size(); i++) {
        if (_Players[i].id == playerId) {
            playerID = _Players[i].id;
            break;
        }
    }

    _EggLayedSound.Play();

    _Chat.push_back(std::tuple<e_chatType, std::string>(EGG, "[" + _Players[playerID].team.name + "] " + std::to_string(playerId) + " layed an egg"));
}

void Gui::Map::PlayWelcomeSound()
{
    _WelcomeSound.Play();
}