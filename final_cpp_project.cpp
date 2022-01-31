// final_cpp_project.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <cmath>        // std::abs
#include <random>
#include <iomanip>
#include <math.h>

#include <fstream> // write in file
#include <string> // read file

#include "player.h"
#include "duel.h"
#include "Tournament.h"

#include "readplayers.h"


using namespace std;


int main()
{



    // On récupere les informations sur les joueurs depuis un fichier texte
    std::vector<Player*> list_of_players = make_players();

    // A partir de la liste des joueurs créée, on peut construire un tournoi
    Tournament* tournoi = new Tournament(list_of_players);



    // On fait s'affronter les joueurs
    tournoi->montecarlo();
    // On sauvgarde les résultats dans le fichier "input_output_files/tournament_results.txt"
    tournoi->save_results();

    printf("\n \n");
    // On affiche les resultats dans la console
    tournoi->show_me_results();

    printf("\n \n");
    printf("\n \n");


    cout << 1 / 2;

    system("pause");


}
