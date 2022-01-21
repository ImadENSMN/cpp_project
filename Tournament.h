#pragma once
#include <fstream>


#define SIZE 8 // Nombre de joueurs participant au tournoi
#define N 1000 // Nombre de simulations pour estimer les probabilites
using namespace std;

class Tournament {
	std::vector<Player*> Players;


public:


	Tournament(const std::vector<Player*> _Player)
	{

		Players.reserve(SIZE); // On reserve SIZE "places" dans le vecteur Players
		Players = _Player;
	}

	

	void save_results()
		// Fonction permettant de sauvegarder la matrice des résultats tu tournoi dans un fichier texte
		// Le fichier texte sera ecrit dans le dossier contenant le projet


	{

		ofstream myfile;
		myfile.open("/tournament_results.txt");

		for (int i = 0; i < SIZE; i++)
		{


			for (int j = 0; j < SIZE; j++)
			{

				myfile << resultats[i][j] << ' ';


			}
			myfile << std::endl;


		}


		myfile.close();

	}


	void show_me_results()
		// Permet d'afficher la matrice des duels

	{

		for (int i = 0; i < SIZE; i++)
		{


			for (int j = 0; j < SIZE; j++)
			{

				std::cout << resultats[i][j] << ' ';


			}
			std::cout << std::endl; // pour un affichage matricielle confortable, à chaque ligne, on saute une ligne



		}

	}

	void show_me_score()
		// Permet d'afficher la liste des scores

	{


		printf("\n");
		for (int i = 0; i < SIZE; i++)
		{



			std::cout << Players[i]->get_name() << "-->" << score[i] << '\n';



		}


	}


	void montecarlo()
	{

		// On construit un array qui va compter les victoires de chaque joueur
		float montecarlo_list[SIZE] = { 0 };
	




		for (int i = 0; i < N; i++)
		{

			clear_matrix(); // On  nettoie la matrice en initialisant chacune de ses valeurs à zéro
			simulate_n_rounds(2); // aux candidats, il s'est deroulé 2 rounds
			int winner = pick_winner(); // apres avoir simulé les deux rounds, on récupère notre gagnant
			montecarlo_list[winner]++; // on incrémente d'une unité dans la case du gagnant

		}


		// Une fois les simulations effectuées, on affiche les résultats :
		for (int i = 0; i < SIZE; i++)
		{

			// p designe la probabilité que le joueur i gagne le tournoi
			float p = montecarlo_list[i]/N;

			// à partir de p, on peut construire un intervalle de confiance sur p à partir de formules mathématiques
			std::vector<float> lower_upper_bound = get_intervalle_de_confiance(p);


			// On affiche les résultats
			std::cout << Players[i]->get_name() << " --> " << p << " -->  [" << lower_upper_bound[0] << "," << lower_upper_bound[1] << "]" << '\n' ;
	
		}




	}


private:






	// On prend des float car les joueurs peuvent faire match nul = 1/2 point
	float resultats[SIZE][SIZE] = { 0 };
	float score[SIZE] = { 0 };


	void simulate_n_rounds(int n)
		// On simule un round du tournoi
		// Tous les joueurs s'affrontent une fois
		// Cela fait n(n-1)/2 oppositions avec n le nombre de joueurs


	{

		for (int k = 0; k < n; k++)
			// k représente le k-ème round

		{


			for (int i = 0; i < SIZE; i++)
			{


				for (int j = 0; j < SIZE; j++)
				{

					if (j > i)
					{

						Duel i_VS_j(Players[i], Players[j]); // On crée un élément de la classe Duel
						float simulation = i_VS_j.simulate_one_game();



						resultats[i][j] = resultats[i][j] + simulation;

						resultats[j][i] = resultats[j][i] + (1 - simulation); // Si le joueur i gagne contre j , alors j a perdu (c'est ce qu'exprime ce 1-...)


					}



				}




			}
		}

		refresh_score(); // On actualise le score
	}

	
	int pick_winner()
		// fonction permettant de désigner un gagnant

		/*
		La FIDE utilise les règles suivantes pour décider du gagnant:

		- Le joueur qui a le plus de points

		S'il y a égalité entre deux joueurs:

		- Le joueur qui a scoré le plus contre l'autre joueur avec qui il y a égalité
		- S'il y a toujours égalité, on comptabilise le joueur qui a le plus de victoires



		*/
	{


		std::vector<int> winners_index;
		std::vector<int> temp;


		float* max_list = get_maximum_and_its_index();
		int index = *(max_list + 1);
		float max_score = *(max_list);


		int* winner = new int;
		int compteur = 0;




		for (int i = 0; i < SIZE; i++)
		{

			if (score[i] == max_score)
			{

				winners_index.push_back(i);
				compteur++;

			}


		}


		if (compteur == 1)
			// s'il n'y a qu'un seul gagnant sans ex-aequo, on peut directement renvoyer l'index du gagnant
		{

	

			return index;

		}



		// On departage les gagnants ex-aequo en regardant les scores qu'ils ont obtenus contre chacun
		for (auto a = winners_index.begin(); a != winners_index.end(); ++a) 
		
		{
			
			for (auto b = winners_index.begin(); b != winners_index.end(); ++b)

			{

				if (*a < *b)
				{


					if (resultats[*a][*b] >= resultats[*b][*a])
					{



						*winner = *a;

					}

					else
					{



						*winner = *b;

					}

				}


			}
		
		}



		
		return *winner;

	}


	void clear_matrix()
		//Permet de nettoyer la matrice, en intialisant toutes ses valeurs à zéro
	{
	

		for (int i = 0; i < SIZE; i++)
		{


			for (int j = 0; j < SIZE; j++)
			{
				resultats[i][j] = 0;

			}

		}

	
	}

	std::vector<float> get_intervalle_de_confiance(float p)
	{
		// le float p designe la probabilité de victoire du joueur
		// Par les formules de Monte Carlo, on peut alors définir un intervalle de confiance à 95%



		float lower_bound = 0;
		float upper_bound = 0;

		// Formule permettant de calculer l'erreur par une méthode de Monte Carlo
		float erreur = 1.96*sqrt(p-p*p)/sqrt(N);
		lower_bound = p - erreur;
		upper_bound = p + erreur;

		
		std::vector<float> lower_upper_bound = { lower_bound,upper_bound };

		return lower_upper_bound;



	}


	// comment retourner un vecteur, on passe par un pointeur? 

	void refresh_score()
		// Permet d'actualiser le score, après que la matrice RESULTATS ait été modifiée

	{
		for (int i = 0; i < SIZE; i++)
		{

			float somme = 0;

			for (int j = 0; j < SIZE; j++)
			{


				somme = somme + resultats[i][j];

			}

			score[i] = somme;

		}

	}

	float* get_maximum_and_its_index()
		// Permet de récuperer le maximum d'une liste ainsi que l'indice de ce maximum
	{

		float liste[2] = { 0 };

		for (int i = 0; i < SIZE; i++)
		{

			if (score[i] > *(liste))
			{

				*liste = score[i];
				*(liste+1)= i;



			}



		}



		return liste;
	}



};
