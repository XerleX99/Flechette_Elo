#pragma once
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

inline std::map<std::string, int> load_elos(const std::string& filename = "../elos.csv") {
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

inline void save_elos(const std::map<std::string, int>& elos, const std::string& filename = "../elos.csv") {
    std::ofstream file(filename);
    for (const auto& [name, elo] : elos) {
        file << name << "," << elo << ",0\n";
    }
}

inline void addNewPlayer(const std::string& name, int elo = 1000, int mean = 0, const std::string& filename = "../elos.csv") {
    const auto elos = load_elos(filename);
    if (name.empty() || elos.find(name) != elos.end()) {
        return;
    }

    std::ofstream file(filename, std::ios::app);
    if (file) {
        file << name << "," << elo << "," << mean << "\n";
    }
}

// Structure pour représenter le résultat d'un joueur pour la partie
struct PlayerResult {
    std::string name;
    int rank; // 1 pour le premier, 2 pour le deuxième, etc. Les ex-æquo ont le même rang.
    int games_played; // Nombre de parties jouées par le joueur (pour ajuster le K)
    float GainMoyenne; 
};




/**
 * Calcule les nouveaux scores Elo après une partie multi-joueurs (3 à 6 joueurs)
 * avec un facteur K adaptatif et un bonus pour le vainqueur.
 * 
 * @param current_elos Map contenant les Elos actuels { "Nom": score }
 * @param results Liste des joueurs avec leur rang final dans la partie
 * @param K_base Le facteur d'impact de base (par défaut 32.0)
 * @return Map contenant les nouveaux scores Elo mis à jour
 */

inline std::map<std::string, int> update_multiplayer_elo(
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