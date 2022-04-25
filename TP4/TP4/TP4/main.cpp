
/*-----------------------------------------------------------------------------------------------------------*/
/*FICHIER: TP4Q1_Code_Equipe-L.cpp                                                                             */
/*AUTEUR: Hicham LAKHAL                                                                                         */
/*DATE: 12 Avril 2022                                                                                         */
/*DESCRIPTION:  programme doit, en tout premier lieu, lire le fichier texte "Musique .txt"                     */
/*                (disponible sur Moodle) pour initialiser un tableau d'enregistrement représentant votre      */
/*                inventaire musical. Chaque ligne du fichier présente les informations décrivant un album     */
/*                de musique (Titre de l'album, Nom de l'artiste, Genre musical et Nombre de pièces musicales  */
/*                - séparés par des espaces).                                                                     */
/*-----------------------------------------------------------------------------------------------------------*/

// Ajoute des librairies
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

// Déclaration des variables globales
enum Type_GenreMusical { JAZZ, POP, ROCK, RAP, QUEBECOIS };
struct Type_Album
{
    string Titre;
    string Artiste;
    Type_GenreMusical Genre;
    int NombrePieces;
};
const int SIZE = 50;

//Déclaration des fonctions
void LireFichier(Type_Album Tableau[]); // LireFichier s'occupe de voir si le fichier existe et le lire
void AfficherInventaire(Type_Album Tableau[]); // AfficherInventaire lit et affiche tout les lignes dans le fichier
int AfficherMenu(void);// AfficheMenu affiche le menu d'accueil
void AfficherUnAlbum(Type_Album AlbumRechercher, Type_Album Tableau[]);// AfficherUnAlbum affiche une seule ligne avec l'entete
int RechercherUnAlbum(int Choix, Type_Album ChercheLalbum, Type_Album Tableau[]);// RechercherUnAlbum recherche un album par titre
Type_Album AjouterUnAlbum( Type_Album NouveauAlbum[],  Type_Album Tableau[]); // AjouterUnAlbum enregistre temporairement une ligne ajouté par l'utilisateur
void Enregistrement(Type_Album NouveauAlbum[], Type_Album Tableau[]); // Enregistrement sauvegarde diffinitivement la ligne ajouter
void AfficherAlbumsDunArtiste(Type_Album Tableau[]);// afficherAlbumDunArtiste recherche et affiche tout les albums d'un artiste selectionné
bool Quitter(int x); // Quitter retourn une valeur true si l'utilisateur veux sortir du programme

/*=========================================== Fonction coeur ===========================================*/
int main(void) {
    //Déclaration des variables
    Type_Album Tableau[SIZE];
    int Album;
    Type_Album NouveauAlbum[SIZE];
    Type_Album ChercheLalbum;

    //Definir la langue
    setlocale(LC_CTYPE, "fr-FR");
    LireFichier(Tableau);
    Album = 0;
    int Choix = 0;// x represente le numero du menu choisi
    
    do {
        Choix = AfficherMenu();

        switch (Choix)
        {
        case 1:
            AfficherInventaire(Tableau);
            break;
        case 2:
            RechercherUnAlbum(Album, ChercheLalbum, Tableau);
            break;
        case 3:
            AjouterUnAlbum(NouveauAlbum,Tableau);
            break;
        case 4:
            AfficherAlbumsDunArtiste(Tableau);
            break;
        default:
            Enregistrement(NouveauAlbum, Tableau);
            Quitter(Choix);
            break;
        }

    } while (Quitter(Choix));
    return 0;
}

/*=========================================== Fonction Initial *===========================================*/
// Structure est utiliser pour surligner un element
void Structure(string text) {
    string txt = text;
    int imax = text.length();
    int i;
    for (i = 0; i < imax; i++)
    {
        cout << '-';
    }
}
void LireFichier(Type_Album Tableau[]) {
    ifstream MusiqueLire("Musique.txt");
     
    int Genres;
    if(MusiqueLire.is_open()){
    for (int ligne = 0; !MusiqueLire.eof() && ligne <= SIZE; ++ligne)
    {
        MusiqueLire >> Tableau[ligne].Titre >> Tableau[ligne].Artiste >> Genres >> Tableau[ligne].NombrePieces;
        Tableau[ligne].Genre = Type_GenreMusical(Genres);
    };
    }
    else {
        cout << "ERREUR ! FICHIER NON TROUVABLE OU ENDOMMAGER. VOUS ALLEZ QUITTER ! \n";
        system("pause");
        exit(0);
    }
    MusiqueLire.close();
}

// TransformerEnumGenreMusical comme son nom indique la fonction transforme les numeros en carractaire
void TransformerEnumGenreMusical(int t, Type_Album Tableau[]) {
    cout << setw(20) << right << Tableau[t].Titre;
    cout << setw(24) << right << Tableau[t].Artiste;
    switch (Tableau[t].Genre)
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
    cout << setw(8) << right << Tableau[t].NombrePieces;
    cout << "\n";
}

/*=========================================== Fonction Primaire *===========================================*/
// Cette fonction affiche l'entete du tableau
void AfficherEntet(void) {
    string Titre = "TITRE";
    string Artiste = "ARTISTE";
    string Genre = "GENRE";
    string Nb = "PiECES";
    cout << setw(20) << right << Titre
        << setw(24) << right << Artiste
        << setw(12) << right << Genre
        << setw(8) << right << Nb
        << "\n";
    cout << setw(16) << right;  Structure(Titre);
    cout << setw(18) << right;  Structure(Artiste);
    cout << setw(8) << right;  Structure(Genre);
    cout << setw(3) << right;  Structure(Nb);
    cout << "\n";
}

// LigneVide est utilisé pour retourner le numero de la ligne vide et pour faire le classement des enregistrements
int LigneVide(Type_Album Tableau[])
{
    int imax = 0;
    LireFichier(Tableau);
    for (int i = 0; i < SIZE; i++)
    {
        if (!Tableau[i].Titre.empty()) {
            imax++;
        }
    }
    imax = imax + 1;
    return imax;
}

// EstDansLinventaire verifie l'existance de l'élément rechercher dans le fichier
bool EstDansLinventaire(Type_Album ChercheLalbum, Type_Album Tableau[]) {
    string y;
    LireFichier(Tableau);
    for (int i = 0; i < SIZE; i++)
    {
        if (Tableau[i].Titre == ChercheLalbum.Titre)
        {
            ChercheLalbum.Titre = Tableau[i].Titre;
            ChercheLalbum.Artiste = Tableau[i].Artiste;
            ChercheLalbum.Genre = Tableau[i].Genre;
            ChercheLalbum.NombrePieces = Tableau[i].NombrePieces;
            return true;
        }
    }
    return false;
}


void Enregistrement(Type_Album NouveauAlbum[], Type_Album Tableau[]) {
    int Ligne = LigneVide(Tableau);
    Type_Album VerifieNouveauAlbum;
    VerifieNouveauAlbum.Titre = NouveauAlbum[Ligne].Titre;
    if (!NouveauAlbum[Ligne].Titre.empty() && EstDansLinventaire(VerifieNouveauAlbum, Tableau) != true)
    {
        LireFichier(Tableau);
        Tableau[Ligne] = NouveauAlbum[Ligne];
        ofstream MusiqueEcrire;
        MusiqueEcrire.open("Musique.txt", ios::app);
        if (!MusiqueEcrire.fail())
        {
            MusiqueEcrire << "\n" << setw(20) << Tableau[Ligne].Titre
                << setw(24) << Tableau[Ligne].Artiste
                << setw(12) << Tableau[Ligne].Genre
                << setw(8) << Tableau[Ligne].NombrePieces;
        }
        if (!Tableau[Ligne].Titre.empty())
        {
            cout << "* * * ALBUM ENREGISTRÉ * * *" << endl;
        }
        else {
            cout << "* * * ERREUR ! * * *" << endl;
        }
        MusiqueEcrire.close();
    }

}

/*=========================================== Fonction élémentaire ===========================================*/

int AfficherMenu(void) {
    int Choix = 0;
    string txt = "INVENTAIRE MUSICAL";
    string espace = "                ";
    Structure(espace + txt + espace); cout << endl;
    cout << espace + txt + espace << endl;
    Structure(espace + txt + espace); cout << endl;
    cout << "Veuillez sélectionner parmi les choix suivants :" << endl;
    cout << "1- Afficher les informations de tous les albums" << endl;
    cout << "2- Rechercher un album" << endl;
    cout << "3- Ajouter un nouvel album" << endl;
    cout << "4- Afficher les albums d'un artiste" << endl;
    cout << "5- Quitter" << endl;
    Structure(espace + txt + espace); cout << endl;
    cout << "Quel est votre choix ? ";
    cin >> Choix;
    return Choix;
}

void AfficherInventaire(Type_Album Tableau[]) {
    LireFichier(Tableau);
    AfficherEntet();
    for (int Ligne = 0; Ligne < SIZE && !Tableau[Ligne].Titre.empty(); Ligne++)
    {
        TransformerEnumGenreMusical(Ligne, Tableau);
    }
}


int RechercherUnAlbum(int Choix, Type_Album ChercheLalbum, Type_Album Tableau[]) {
    cout << "Quel est le titre de l'album (sans accent/sans espace) recherché? " << endl;
    cin >> ChercheLalbum.Titre;
    cout << ChercheLalbum.Titre << endl;
    if (EstDansLinventaire(ChercheLalbum, Tableau) == true)
    {
        AfficherUnAlbum(ChercheLalbum, Tableau);
    }
    else {
        cout << "* * * ERREUR ! * * *" << endl;
    }
    
    return 1 ;
}
void AfficherUnAlbum(Type_Album ChercheLalbum, Type_Album Tableau[]) {
    AfficherEntet();
    for (int Ligne = 0; Ligne < SIZE; Ligne++)
    {
        if (ChercheLalbum.Titre == Tableau[Ligne].Titre)
        {
            cout << setw(20) << right << Tableau[Ligne].Titre
                << setw(24) << right << Tableau[Ligne].Artiste
                << setw(12) << right << Tableau[Ligne].Genre
                << setw(8) << right << Tableau[Ligne].NombrePieces
                << "\n";
        }
    }
}

Type_Album AjouterUnAlbum( Type_Album NouveauAlbum[], Type_Album Tableau[]) {
    Type_Album VerifieNouveauAlbum;
    int genre, Ligne;
    
    Ligne = 0;
    genre = 0;
    Ligne = LigneVide(Tableau);
        cout << "Quel est le titre de l�album (sans accent/sans espace)?";
        cin >> NouveauAlbum[Ligne].Titre;
        cout << "Quel est le nom de l'artiste (sans accent/sans espace)?";
        cin >> NouveauAlbum[Ligne].Artiste;
        cout << "Quel est le genre musical (0:Jazz, l:Pop, 2:Rock, 3:Rap, 4 : Québécois)?";
        cin >> genre;
        NouveauAlbum[Ligne].Genre = Type_GenreMusical(genre);
        cout << "Cet album contient combien de pi�ces musicales?";
        cin >> NouveauAlbum[Ligne].NombrePieces;
        VerifieNouveauAlbum.Titre = NouveauAlbum[Ligne].Titre;
        
        if (!NouveauAlbum[Ligne].Titre.empty() && EstDansLinventaire(VerifieNouveauAlbum, Tableau) != true)
        {
            cout << "* * * ALBUM AJOUTÉ * * *" << endl;
            return NouveauAlbum[Ligne];
        }
        else
        {
            cout << "* * * ERREUR ! * * *" << endl;
            
            return NouveauAlbum[Ligne];
        }
        
}


void AfficherAlbumsDunArtiste(Type_Album Tableau[]) {
    string  ArtisteRechercher;
    LireFichier(Tableau);
    cout << "Quel est le nom de l'artiste (sans accent/sans espace) recherché? " << endl;
    cin >> ArtisteRechercher;
    AfficherEntet();
    for (int i = 0; i < SIZE; i++)
    {
        if (Tableau[i].Artiste == ArtisteRechercher)
        {
            TransformerEnumGenreMusical(i, Tableau);
        }
    }
}
bool Quitter(int x) {

    
        if (x < 1 || x>=4)
        {
            return false;
        }
        else
        {
        
            return true;
        }
}
