

// Fonction permettant de split un string par un séparateur
// On prend le séparateur égal à un espace
std::vector<string> get_elo_name(string str, string delimiter = " ")


{
    std::vector<string> elo_name = { "0","0" };



    int start = 0;
    int end = str.find(delimiter);
    while (end != -1) 
    
    {
        //cout << str.substr(start, end - start) << endl;
        elo_name[0] = str.substr(start, end - start);
        

        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }

        //cout << str.substr(start, end - start);
        elo_name[1] = str.substr(start, end - start);


        return elo_name;
}

std::vector<Player*> make_players()
// Fonction permettant de créer nos joueur à partir du fichier texte dans "input_output_files/players_informations.txt"

    
{
    std::vector<Player*> list_of_players;

    string line;
    ifstream myfile("input_output_files/players_informations.txt");
    if (myfile.is_open())
    {

        int compteur = 0;
        while (getline(myfile, line))
        {


            // On récupere nom du joueur et son Elo en splittant par un espace
            std::vector<string> elo_name = get_elo_name(line);
            
            // Il faut convertir l'Elo en un int
            int elo = std::stoi(elo_name[1]); // convert elo string to elo int
            
            string player_name = elo_name[0]; 
      
            // On dispose alors de toutes les inforamtions pour construire notre joueur
            Player* new_Player = new Player(elo, player_name);

             
            // On ajoute dynamiquement notre joueur à list_of_players
            list_of_players.push_back(new_Player);

            compteur++;

        }

        // On ferme le fichier car nous n'en avons plus besoin
        myfile.close();


        return list_of_players;
    }

    

    else cout << "Unable to open file";



}
