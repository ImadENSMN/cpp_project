# cpp_project


Méthode de Monte-Carlo appliquée à la prédiction du gagnant du tournoi des candidats aux échecs
Imad AYAD – 30/01/2022
Ce projet a été effectué seul.

Introduction

Pour devenir champion du monde d’échecs, il est nécessaire de gagner le « tournoi des candidats », tournoi opposant les meilleurs joueurs du monde. Le gagnant d’un tel tournoi aura alors le privilège d’affronter le champion du monde en titre lors d’un match, dont l’issue déterminera le nouveau champion du monde.
On se propose dans ce projet de mettre en œuvre les méthodes de Monte Carlo afin de prédire le gagnant du tournoi des candidats de l’année 2021.

Système Elo des échecs

La Fédération internationale des échecs (FIDE) se sert d’un classement Elo, qui attribue à chaque joueur un nombre de points, appelé Elo. Le classement d’un joueur dépend alors de ses performances passées. Plus précisément, lorsque ce dernier vainc un adversaire supposé meilleur que lui, il se voit récompenser par une hausse de points de son classement Elo. Au contraire, si ce dernier cède face à un adversaire normalement moins fort, il est pénalisé et voit son classement Elo baisser.
Le classement Elo vers lequel converge un joueur après un nombre important de parties correspond au niveau du joueur.
Or, ce système est tel qu’il permet d’estimer la probabilité qu’un joueur A gagne contre un joueur B. En effet, notons R_A et R_B leurs Elo respectifs.

Alors le joueur A a espérance de gain  E_A=1/(1+10^((R_B-R_A)/400) ) 
Néanmoins, cette espérance de gain ne permet pas de distinguer les matchs nuls des victoires. On utilise alors un seconde formule empirique développée par une seconde source https://wismuth.com/elo/calculator.html.
On dispose alors de tous les outils pour mener à bien notre étude.
Exemple :
	Joueur MVL de classement 2767
	Joueur Liren de classement 2805

D’où : 
Probabilité que MVL gagne contre Liren : 16%
Probabilité que MVL fasse match nul contre Liren : 57%
Probabilité que MVL perde contre Liren : 27%


Tournoi des candidats

Le tournoi des candidats se joue en deux tours entre 8 joueurs. Tous les joueurs se rencontrent deux fois.
Une victoire équivaut à 1 point, un match nul vaut 1/2 point, une défaite ne rapportant pas de points.
Le joueur Nepomniachtchi est le gagnant du tournoi des candidats de 2021, ainsi, il va être intéressant de calculer la probabilité de sa victoire au tournoi.

Instructions pour la compilation

Le projet est composé de 5 fichiers :
	player.h
	readplayers.h
	duel.h
	tournament.h
	final_cpp_project.cpp

Ces fichiers suffisent pour compiler le projet, et il ne nécessite aucune manœuvre en particulier à mener pour compiler le projet. 
Néanmoins, le code permet de charger les données sur les joueurs du tournoi directement depuis un fichier texte. Ainsi, il est important que le fichier input_output_files/players_informations.txt existe et soit correctement rempli. Le formatage choisit est le suivant (nom du joueur Elo):

 

Le projet doit avoir la structure suivante :

 

 

Instruction pour l’exécution

	Avant de lancer le programme, il faut avoir rempli les informations sur les joueurs dans le fichier input_output_files/players_informations.txt
	Par défaut, le tournoi se joue avec 8 joueurs. Si vous augmentez ou diminuez ce nombre, il faut alors changer la valeur SIZE définie à la compilation dans le fichier Tournament.h :

 
	Une fois ces deux étapes effectuées, vous pouvez alors exécuter le code.

Résultats

A l’exécution, on obtient un résultat similaire à celui-ci (modulo les paramètres utilisés plus haut) : 
 


Considérons la première ligne :
MVL→0.063→[0.047941,0.078059]
Cela signifie que le joueur MVL a une probabilité de gagner le tournoi comprise dans l’intervalle  [0.047941,0.078059] avec une valeur moyenne de gain égale à 6,3% (milieu de l’intervalle)

Il s’en suit alors la matrice des duels. Le coefficient i,j de cette matrice désigne le score du joueur i contre le joueur j lors de la dernière simulation. Par exemple, MVL a gagné 1.5 points (1 victoire + 1 match nul) contre Liren. Cette matrice est alors automatiquement sauvegardée dans le fichier input_output_files/tournament_results.txt


	
 
Difficultés rencontrées :

	Lecture et écriture dans un fichier texte
	Structure du code : quelles classes créer et introduire ?
	Manipulation de matrices
 
	Division entière  Je ne comprenais pas pourquoi 1/2 renvoyait 0… Il fallait écrire 1.0/2  dans le code


