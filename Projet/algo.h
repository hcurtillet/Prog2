// Cette fonction a pour objectif de trouver le plus court chemin entre le sommet de départ et le sommet d'arrivé
// en utilisant un algorithme Depth First Search
int ParcoursEnProfondeur(int depart, int arrivee, graph_t graphe);

// Cette fonction permet d'initialiser les valeurs de cout des sommets du graphe, 0 pour le départ et + l'infini pour les autres
graph_t  InitGraphe(int depart, graph_t graphe);

// Cette fonction a pour utilité de créer une liste représentant le chemin le plus court parcouru pour aller du départ à l'arrivée
chemin_t LectureDeChemin(int depart, int arrivee, graph_t graphe);

// Cette fonction affiche correctement un chemin donnée
void printChemin( chemin_t chemin, graph_t graphe);

// Cette fonction utilise l'algotithme BFS afin de trouver le chemin qle plus efficace
int ParcoursEnLargeur(int depart, int arrivee, graph_t graphe);
