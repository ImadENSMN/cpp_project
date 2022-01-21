#pragma once

class Player {
    // Class gérant les informations du joueurs, à savoir son nom et son classement Elo

public:

    

    Player(int _elo, std:: string _name) : elo(_elo), name(_name) {}


    int get_elo()

    {

        return elo;


    }


    std::string get_name()

    {

        return name;


    }

    ~Player() = default;


private:

    int elo;
    std::string name;

};
