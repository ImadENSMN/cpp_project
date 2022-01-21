#pragma once


class Duel
    // La classe Duel permet de simuler l'affrontement entre deux joueurs

{

public:

    Duel(Player* _PlayerA, Player* _PlayerB) : PlayerA(_PlayerA), PlayerB(_PlayerB){ }


    Player* PlayerA;

    Player* PlayerB;



    int get_elo_difference()
        // Permet d'obtenir la différence de niveua entre les deux joueurs

    {

        return (PlayerA->get_elo()-PlayerB->get_elo());


    }

    Player* get_strongest_player()
        // Renvoie le plus fort des deux joueurs
    {

        int a = PlayerA->get_elo();

        int b = PlayerB->get_elo();

        int max = (a < b) ? b : a; // formule qui permet de calculer le maximum entre a et b

        if (a == max)
        {

            return PlayerA;

        }
        
        else
        {

            return PlayerB;


        }

    }

    Player* get_weakest_player()
    {
       // Renvoie le plus faible des deux joueurs

        int a = PlayerA->get_elo();

        int b = PlayerB->get_elo();

        int max = (a < b) ? b : a; // formule qui permet de calculer le maximum entre a et b

        if (a == max)
        {

            return PlayerB;

        }

        else
        {

            return PlayerA;


        }

    }


    int get_mean_elo()
        // Renvoie la probabilité que le joueur A gagne
        // Formule utilisée par la FIDE (Fédération internationale des echecs)

    {


        return (PlayerA->get_elo() + PlayerB->get_elo()) / 2;
    }

    float get_odds(int delta)
    // Renvoie la probabilité que le joueur A gagne
    // Formule utilisée par la FIDE (Fédération internationale des echecs)

    {

        float odd = 1 / (1 + pow(10.0, (delta) / 400.0));

        
        return odd;
    }




    float simulate_one_game()
     //Retourne 1 si PlayerA gagne, 1/2 si match nul, 0 sinon


    {
        // Le code qui suit permet de generer un nombre entre 0 et 1
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<float> distr(0, 1);
        //

        float random = distr(eng);
        float mean_elo = get_mean_elo();

        float elo_per_pawn = eloperpawn(mean_elo);
        float eloshift = elo_per_pawn * 0.6;
        float expected_score = elonormal(get_elo_difference());


        float player_A_wins = elonormal(get_elo_difference() - eloshift);

        // Probabilité de faire match nul!!
        float draw_probability = (expected_score - player_A_wins) * 2;


        

        if (random < draw_probability)
        {
            // Match nul!
            return 1.0 / 2;


        }
        else if ((draw_probability < random) && (random < draw_probability + player_A_wins))
            // Dans ce cas de figure, c'est le joueur A qui gagne

        {

            return 1;

        }
        else
        {

            // Dans ce cas de figure, c'est le joueur B qui gagne
            return 0;

        }

    
        

    }





private:

    float eloperpawn(int elo)
        //Fonction arbitraire nécessaire lors de calculs

    {

        // Formule mathématique, trouvée dans la littérature échiquéene
        return exp(elo / 1020.0) * 26.59;


    }

    float elonormal(float value)
        //Fonction arbitraire nécessaire lors de calculs


    {

        // Formule mathématique, trouvée dans la littérature échiquéene
        // Source de la formule à mettre dans le rapport
        // ILLUSTRER avec des données réelles 
        return erfc(-value / ((2000.0 / 7) * sqrt(2))) / 2;



    }


};
