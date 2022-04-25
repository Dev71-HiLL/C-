//
//  main.cpp
//  Projet-Tp4
//
//  Created by Hicham Lakhal on 2022-04-11.
//

//
//  test.cpp
//  TP4
//
//  Created by Hicham Lakhal on 2022-04-11.
//

/*----------------------------------------------------------------------------------------------*/
/*FICHIER: TP4_F.cpp                                                                            */
/*AUTEUR: Hicham Lakhal                                                                         */
/*DATE: 07 Avril 2022                                                                           */
/*DESCRIPTION:                                                                                  */
/*----------------------------------------------------------------------------------------------*/

#include<iostream> // Ajoute les fonctions d'une librairie (dans ce cas-ci, les cin et cout)
#include<iomanip>
#include <fstream>
#include <algorithm>
#include<string>
        


using namespace std;

enum Type_GenreMusical { JAZZ, POP, ROCK, RAP, QUEBECOIS };
struct Type_Album
{
    string Titre;
    string Artiste;
    Type_GenreMusical Genre;
    int NombrePieces;
};
const int SIZE = 50;
Type_Album type[SIZE];
ifstream Musique;
ifstream in("Musique.txt");


void Structure(string text) {
    string txt = text;
    int imax = 0;
    imax = text.length();
    int i;
    for (i = 0; i < imax; i++)
    {
        cout << '-';
    }
}
int Index(int x) {
    x = 0;
    string txt = "INVENTAIRE MUSICAL";
    string espace = "                ";
    Structure(espace + txt + espace); cout << endl;
    cout << espace + txt + espace << endl;
    Structure(espace + txt + espace); cout << endl;
    cout << "Veuillez sÈlectionner parmi les choix suivants :" << endl;
    cout << "1- Afficher les informations de tous les albums" << endl;
    cout << "2- Rechercher un album" << endl;
    cout << "3- Ajouter un nouvel album" << endl;
    cout << "4- Afficher les albums d'un artiste" << endl;
    cout << "5- Quitter" << endl;
    Structure(espace + txt + espace); cout << endl;
    cout << "Quel est votre choix ? ";
    cin >> x;
    return x;
}
void EnteteTable(void) {
    string Titre = "TITRE";
    string Artiste = "ARTISTE";
    string Genre = "GENRE";
    string Nb = "PiECES";
    
    cout << setw(20) << right << Titre;
    cout << setw(24) << right << Artiste;
    cout << setw(12) << right << Genre;
    cout << setw(8) << right << Nb;
    cout << "\n";
    cout << setw(16) << right;  Structure(Titre);
    cout << setw(18) << right;  Structure(Artiste);
    cout << setw(8) << right;  Structure(Genre);
    cout << setw(3) << right;  Structure(Nb);
    cout << "\n";
}
void LireTable(void)
{
    int ligne = 0;
    int Genres;
    
    while (!in.eof())
    {
        in >> type[ligne].Titre >> type[ligne].Artiste >> Genres >> type[ligne].NombrePieces;
        type[ligne].Genre = Genres /*Type_GenreMusical(Genres)*/;
        ++ligne;
    };
    
}
void ContenuTable(int i) {
    cout << setw(20) << right << type[i].Titre;
    cout << setw(24) << right << type[i].Artiste;
    switch (type[i].Genre)
    {
    case 0:
        cout << setw(12) << right << "JAZZ";
        break;
    case 1:
        cout << setw(12) << right << "POP";
        break;
    case 2:
        cout << setw(12) << right << "ROCK";
        break;
    case 3:
        cout << setw(12) << right << "RAP";
        break;
    case 4:
        cout << setw(12) << right << "QUEBECOIS";
        break;
    };

    cout << setw(8) << right << type[i].NombrePieces;
    cout << "\n";

}

int LigneVide(int imax) {
    
    for (int i = 0; i < SIZE; i++)
    {
        if (!type[i].Titre.empty()) {
            imax++;
        }
    }
    
    
    return imax;
}

bool Quitter(void) {
        return true;
}

int main() {
    setlocale(LC_CTYPE, "fr-FR");
    int x = 0;
    int imax = 0;
    
    string  ArtisteRechercher;
    string titreRechercher;
    
    
    int Genres;
    do {
        x = Index(x);
        
        switch (x)
        {
        case 1:
            LireTable();
            EnteteTable();
            for (int i = 0; i < SIZE; i++)
            {
                if (!type[i].Titre.empty()) {
                    ContenuTable(i);
                    
                }
            }
            break;
        case 2:
            LireTable();
            cout << "Quel est le titre de l'album (sans accent/sans espace) recherchÈ? " << endl;
            cin >> titreRechercher;
            EnteteTable();
            for (int i = 0; i < SIZE; i++)
            {
                if (type[i].Titre == titreRechercher) {
                    ContenuTable(i);
                }
            }
            break;
        case 3:
            
            imax = LigneVide(imax);
            imax = imax + 1;
            if (type[imax].Titre.empty()) {
                ofstream in("Musique.txt");
                cout << "Quel est le titre de líalbum (sans accent/sans espace)?";
                cin >> type[imax].Titre;
                cout << "Quel est le nom de l'artiste (sans accent/sans espace)?";
                cin >> type[imax].Artiste;
                cout << "Quel est le genre musical (0:Jazz, l:Pop, 2:Rock, 3:Rap, 4 : QuÈbÈcois)?";
                cin >> Genres;
                cout << "Cet album contient combien de piËces musicales?";
                cin >> type[imax].NombrePieces;
                in << type[imax].Titre << type[imax].Artiste << Genres << type[imax].NombrePieces;
                in.close();
            }
            
            break;
        case 4:
            LireTable();
            cout << "Quel est le nom de l'artiste (sans accent/sans espace) recherchÈ? " << endl;
            cin >> ArtisteRechercher;
            EnteteTable();
            for (int i = 0; i < SIZE; i++)
            {
                if (type[i].Artiste == ArtisteRechercher) {
                    ContenuTable(i);
                }
            }
            break;
        default :
            exit(0);
            break;
        }
        in.close();
    } while (Quitter());
    system("pause");
    return 0;
}


