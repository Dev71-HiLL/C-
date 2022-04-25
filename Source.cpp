#include<iostream> // Ajoute les fonctions d'une librairie (dans ce cas-ci, les cin et cout)
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
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

void LireFichier(Type_Album Tableau[]);
void TransformerEnumGenreMusical(int t, Type_Album Tableau[]);
void AfficherInventaire(Type_Album Tableau[]);
void Structure(string text);
int AfficherMenu(void);

void AfficherEntet(void);
void AfficherUnAlbum(Type_Album AlbumRechercher, Type_Album Tableau[]);
int RechercherUnAlbum(int Choix, Type_Album ChercheLalbum, Type_Album Tableau[]);
bool EstDansLinventaire(Type_Album AlbumRechercher, Type_Album Tableau[]);
/*void AjouterUnAlbum(Type_Album NouveauAlbum, Type_Album Tableau[]);
void AfficherAlbumsDunArtiste(Type_Album Tableau[]);
void Enregistrement(Type_Album Tableau[]);
bool Quitter(void); */


void main(void) {
	Type_Album Tableau[SIZE];
	int album;
	Type_Album NouveauAlbum;
	Type_Album ChercheLalbum;
	int Option;
	int Emplacement;

	setlocale(LC_CTYPE, "fr-FR");
	album = 0;
	int x = 1;
	int y = 1;
	
	
	setlocale(LC_CTYPE, "fr-FR");
	do {
		x = AfficherMenu();

		switch (x)
		{
		case 1:
			AfficherInventaire(Tableau);
			break;
		case 2:
			RechercherUnAlbum(album, ChercheLalbum, Tableau);
			break;
		case 3:
			//AjouterUnAlbum(NouveauAlbum, Tableau);
			break;
		case 4:
			//AfficherAlbumsDunArtiste(Tableau);
			break;
		default:
			int y = 0;
			//Quitter();
			break;
		}

	} while (x <= 4);

}
void LireFichier(Type_Album Tableau[]) {
	ifstream MusiqueOuv("Musique.txt");
	 
	int Genres;
	for (int ligne = 0; !MusiqueOuv.eof() && ligne <= SIZE; ++ligne)
	{
		MusiqueOuv >> Tableau[ligne].Titre >> Tableau[ligne].Artiste >> Genres >> Tableau[ligne].NombrePieces;
		Tableau[ligne].Genre = Type_GenreMusical(Genres);
		
	};
	MusiqueOuv.close();
}
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
void AfficherInventaire(Type_Album Tableau[]) {
	
	LireFichier(Tableau);
	AfficherEntet();
	for (int t = 0; t < SIZE && !Tableau[t].Titre.empty(); t++)
	{
		TransformerEnumGenreMusical(t, Tableau);
	}
	
}
void Structure(string text) {
	string txt = text;
	int imax = text.length();
	int i;
	for (i = 0; i < imax; i++)
	{
		cout << '-';
	}
}
int AfficherMenu(void) {

	int x = 0;
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
	cin >> x;
	return x;
}
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

void AfficherUnAlbum(Type_Album ChercheLalbum, Type_Album Tableau[]) {
	AfficherEntet();
	
	cout << setw(20) << right << ChercheLalbum.Titre
		<< setw(24) << right << ChercheLalbum.Artiste = Tableau.Artiste210
		<< setw(12) << right << ChercheLalbum.Genre
		<< setw(8) << right << ChercheLalbum.NombrePieces
		<< "\n"; 
	
}
int RechercherUnAlbum(int Choix, Type_Album ChercheLalbum, Type_Album Tableau[]) {
	
	
	cout << "Quel est le titre de l'album (sans accent/sans espace) recherché? " << endl;
	cin >> ChercheLalbum.Titre;
	

	cout << "0" << ChercheLalbum.Titre << endl;
	

	if (EstDansLinventaire(ChercheLalbum, Tableau) == true) {
		AfficherUnAlbum(ChercheLalbum, Tableau);
	}
	else {
		cout << "hel";
	}
	/*AfficherUnAlbum(Tableau);*/
	/*for (int i = 0; i < SIZE; i++)
	{
		if (Tableau[i].Titre == titreRechercher) {
			AfficherUnAlbum(Tableau);
		}
	}*/
	return 1 ;
}
bool EstDansLinventaire(Type_Album ChercheLalbum, Type_Album Tableau[]) {
	string y;
	LireFichier(Tableau);
	for (int i = 0; i < SIZE ; i++)
	{
		if( Tableau[i].Titre == ChercheLalbum.Titre){
			ChercheLalbum.Titre = Tableau[i].Titre;
			ChercheLalbum.Artiste = Tableau[i].Artiste;
			ChercheLalbum.Genre = Tableau[i].Genre;
			ChercheLalbum.NombrePieces = Tableau[i].NombrePieces;
			return true;
		}
		
	}
	
	/*for (int i = 0; i < SIZE; i++)
	{
		cout << "1" << AlbumRechercher << endl;
		cout << "2" << Tableau[i].Titre << endl;
		return true;
	}*/
}
/*void AjouterUnAlbum(Type_Album NouveauAlbum, Type_Album Tableau[]) {

}
void AfficherAlbumsDunArtiste(Type_Album Tableau[]) {

}
void Enregistrement(Type_Album Tableau[]) {

}
bool Quitter(void) {

}*/