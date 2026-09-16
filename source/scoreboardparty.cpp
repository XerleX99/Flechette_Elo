#include "../include/scoreboardparty.h"
#include "../include/newparty.h"
#include "../include/newplayer.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <fstream>
#include <sstream>


ScoreBoardParty::ScoreBoardParty(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ScoreBoardFlechettes)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &ScoreBoardParty::onNouvellePartie);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &ScoreBoardParty::onInscrireJoueur);
}

void ScoreBoardParty::onNouvellePartie()
{
    NewParty *fenetre = new NewParty();
    fenetre->show();
}

void ScoreBoardParty::onInscrireJoueur()
{
    NewPlayer *fenetre = new NewPlayer();
    fenetre->show();
}

// Structure pour représenter le résultat d'un joueur pour la partie
struct PlayerResult {
    std::string name;
    int rank; // 1 pour le premier, 2 pour le deuxième, etc. Les ex-æquo ont le même rang.
    int games_played; // Nombre de parties jouées par le joueur (pour ajuster le K)
    float GainMoyenne; 
};


// Sauvegarder la base d'élo dans un fichier
void save_elos(const std::map<std::string, int>& elos, const std::string& filename = "elos.csv") {
    std::ofstream file(filename);
    for (const auto& [name, elo] : elos) {
        file << name << "," << elo << "\n";
    }
}

// Charger la base d'élo depuis un fichier
std::map<std::string, int> load_elos(const std::string& filename = "elos.csv") {
    std::map<std::string, int> elos;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, elo_str;
        std::getline(ss, name, ',');
        std::getline(ss, elo_str, ',');
        if (!name.empty() && !elo_str.empty()) {
            elos[name] = std::stoi(elo_str);
        }
    }
    return elos;
}



/**
 * Calcule les nouveaux scores Elo après une partie multi-joueurs (3 à 6 joueurs)
 * avec un facteur K adaptatif et un bonus pour le vainqueur.
 * 
 * @param current_elos Map contenant les Elos actuels { "Nom": score }
 * @param results Liste des joueurs avec leur rang final dans la partie
 * @param K_base Le facteur d'impact de base (par défaut 32.0)
 * @return Map contenant les nouveaux scores Elo mis à jour
 */

std::map<std::string, int> update_multiplayer_elo(
    const std::map<std::string, int>& current_elos, 
    const std::vector<PlayerResult>& results, 
    double K_base = 32.0) 
{
    int N = results.size();
    std::map<std::string, int> new_elos = current_elos;

    // Protection si le nombre de joueurs est insuffisant pour éviter une division par zéro
    if (N <= 1) return new_elos;

    // 1. Calcul du K effectif de base pour la partie selon le nombre de joueurs
    // Formule : K_base / sqrt(N - 1)
    double K_partie = K_base / std::sqrt(N - 1);

    // Parcourir chaque joueur de la partie
    for (int i = 0; i < N; ++i) {
        std::string p1_name = results[i].name;
        int p1_rank = results[i].rank;
        double p1_current_elo = current_elos.at(p1_name);
        double total_delta = 0.0;

        // 2. Ajustement du K pour le joueur (Bonus de 20% si rang 1)
        double K_joueur = K_partie;
        if (p1_rank == 1) {
            K_joueur *= 1.2; 
        }

        // Comparer ce joueur (p1) avec tous les autres joueurs (p2)
        for (int j = 0; j < N; ++j) {
            if (i == j) continue; // On ne se compare pas à soi-même

            std::string p2_name = results[j].name;
            int p2_rank = results[j].rank;
            double p2_current_elo = current_elos.at(p2_name);

            // Calcul de l'espérance de victoire de p1 face à p2
            double E_p1 = 1.0 / (1.0 + std::pow(10.0, (p2_current_elo - p1_current_elo) / 400.0));

            // Détermination du score réel du duel selon le rang
            double S_p1 = 0.0;
            if (p1_rank < p2_rank) {
                S_p1 = 1.0;  // Gagne le duel
            } else if (p1_rank > p2_rank) {
                S_p1 = 0.0;  // Perds le duel
            } else {
                S_p1 = 0.5;  // Égalité (Ex-æquo)
            }

            // Accumulation de la variation pour ce duel avec le K spécifique du joueur
            total_delta += K_joueur * (S_p1 - E_p1);
        }

        // 3. Application de la moyenne des duels et arrondi
        double final_elo = p1_current_elo + (total_delta / (N - 1));
        new_elos[p1_name] = std::round(final_elo);
    }

    return new_elos;
}

int main() {
    // Base de données des joueurs et leurs Élos actuels
    std::map<std::string, int> database_elos = load_elos();

    // Exemple de partie à 5 joueurs
    // Béatrice gagne, Esteban fait sensation en finissant 2e, etc.
    std::vector<PlayerResult> game_results = {
        {"Gabriel", 1}, // Gagnante -> profitera du bonus de K
        {"Luc",  2},
        {"Yassine",  3},
        {"Maïlys",   4},
        {"Martin",    5}
    };

    std::cout << "--- Élos avant la partie (5 joueurs) ---" << std::endl;
    for (const auto& player : game_results) {
        std::cout << player.name << " : " << database_elos[player.name] << std::endl;
    }

    // Calcul de la mise à jour (K_base fixé à 32)
    std::map<std::string, int> updated_elos = update_multiplayer_elo(database_elos, game_results, 32.0);

    std::cout << "\n--- Nouveaux Élos après calcul (K adaptatif + Bonus Vainqueur) ---" << std::endl;
    for (const auto& player : game_results) {
        int ancien = database_elos[player.name];
        int nouveau = updated_elos[player.name];
        int variation = nouveau - ancien;

        std::cout << player.name << " (Rang " << player.rank << ") : " 
                  << nouveau << " (" << (variation >= 0 ? "+" : "") << variation << ")" << std::endl;
    }

    save_elos(updated_elos); // Sauvegarde des nouveaux Élos dans un fichier CSV

    return 0;
}
