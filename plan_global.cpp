/*
///||================================---2018/0i/27---================================||\\\
\\\||================================---Cadre de travail pour histoires interactives---================================||///
*/

//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>
#include <vector>
using namespace std;

//B) Tenter de mettre de la couleur dans nos coeurs?
	/*
	En bref, seules 15 couleurs sont disponibles sur Windows. Ouin, j'ai vraiment pas trouv� mieux en cherchant sur Google. Inexistant.
	
	La bonne nouvelle, c'est toutefois qu'elles peuvent �tre chang�es soit pour toute la console, soit pour seulement le texte
	�crit apr�s le changement de commande.
	
	Donc, en jouant avec les positions, on pourrait faire des bordures de diff�rentes couleurs, des cartes bien lisibles, des menus, etc.
	
	Btw, pour le faire en linux, voir : https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
	et : https://stackoverflow.com/questions/138383/colored-grep/138528#138528
	*/
	

//P-T) Classe personalis�e pour imiter les vecteurs?????
//------------------------------------------------------------------------------------------------------------------------------------------------------
//AIde: https://stackoverflow.com/questions/13431567/how-to-make-an-array-with-a-dynamic-size-general-usage-of-dynamic-arrays-maybe

//Si je cr�e cette classe en tant que TEMPLATE (mod�le g�n�rique accomodant tous les types),
	//je pourrais ne pas seulement me limiter aux integer, mais stocker des arrays de toutes sortes!
	//(th�oriquement, je pourrais m�me utiliser ce template pour stocker mes strings, avec l'avantage qu'elles
	//conserveraient en tout temps leur nombre de caract�res...
		//Mais en m�me temps, les strings sont un objet d�j� l� et utile, et c'est son seul d�faut. Et j'ai plus besoin des op�rations de base
		//(operation overload) des strings ("AC"+"-TG" == "AC-TG") que d'une allocation dynamique de la m�moire.
	//Pour l'instant, je me limite aux int, pour garder �a simple. � upgrader apr�s.

	//Creating the class
	class vect 
	{
	public:
				/*int ar, nb;  //L'array et le nombre d'objets 
				int* pt;     //Le pointeur de l'array (plus pratique)*/    //Obsol�te, car le pointeur seul suffit pour cr�er/r�f�rer un objet!
		int* pt; int nb;  //Cr�er les objets contenus dans la classe, soit le pointeur et le nombre d'objets de l'array point�	
		
		vect() {nb=0};// Cr�er un constructeur par d�faut, pour �tre certaine d'avoir 0 objet quand un nouveau vect est cr��
		
		void add(int nxt) //Cr�er une fonction permettant d'ajouter un integer � la suite du vecteur
		{
			if(*this.nb==0) 
			{
				pt = new int; //Si le vect est nouveau, simplement cr�er array de taille 1
				pt = nxt
			}
			else
			{
				int* nwpt = new int [*this.nb+1];  //D�clarer le nouvel array (transitoire)
				for(int a=0; a < *this.nb; ++a) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
				nwpt[*this.nb] = nxt //Ajouter la nouvelle valeur
				delete[] pt  //�liminer le vieux array trop petit (il semble que si on ne sp�cifie pas combien d'�l�ments �liminer entre braquettes, �a �limine tout)
				pt = nwpt  //Assigner le pointeur � l'array actuel
			}
		} 
		
		void add(vect nxt){}  //�a serait utile d'overloader la fonction, pour permettre d'ajouter � la suite tout un vecteur!
				//je pense bien que je peux r�f�rencer une objet de sa propre classe en d�finissant un membre... � v�rifier...
				
		void rem(int pos){} //Ici, l'integer r�f�re � la position de l'objet � enlever
		void rem(vect pos){} 
		
		//Faudrait aussi quelque chose pour ajouter (ou cr�er l'array principal avec) un array normal, pour prendre avantage de la d�finition
			//simple � l'�criture (int arr [3] = {2,3,4})
			//Mais je ne sais pas quel param�tres mettre... Faudrait un param�tre pour le nombre de caract�res, et un pour l'array en tant que tel?
		void add(int nb, int next)	{} //o� next est l'array en tant que tel. Ou bien son pointeur. Ouin. Mieux vaut travailler en pointeurs tout le temps.		
	} 
	
		//Et l� il reste l'�criture, o� on cr�e les choses pour mieux les effacer ensuite.
	
	
//A) Fonction pour rep�rer des mots
//------------------------------------------------------------------------------------------------------------------------------------------------------
				// x est le mot � rep�rer,
				// p est la phrase dans laquelle rep�rer le mot
	
		//ATTENTION: J'aurais aussi tr�s bien pu utiliser la fonction .find, d�j� incluse comme membre de la classe string (dans std).
	
		//ATTENTION!!! Pour trouver la longueur des strings, j'utilise .length(), qui calcule la m�moire utilis�e.
		//�a va bien quand j'utilise de simples char, car leur taille est 1 bt. Mais les accents vont probablement pas entrer l�-dedans...
				
		//ATTENTION!!! Je pourrais utiliser, au lieu de string comme type, de mettre const string&.
		//Pr�sentement (avec string), le string est copi� pour caller la fonction.
		//Avec l'alternative (const string&), seulement une r�f�rence (pointeur) est copi�e, et "const"	assure que l'objet original n'est pas chang�.	
				
	//i) Logical
	/*bool lfind(string x, string p)
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();  //La synthaxe semble obligatoire; length(x) ne marche pas (la fonction length() seule n'est pas d�finie).
															 //En fait, ici length() est une fonction membre de la classe string...
		//Cr�er des compteurs
		int xpos = 0 ; int ppos = 0;
		while(true)
		{
			if(x[xpos]==p[ppos])
			{
				if(xpos==xnchar-1) return(true); //Si le mot � rep�rer a �t� rep�r� au complet, on arr�te la fonction
				xpos++;  //Si le mot n'est pas termin�, on passe � la prochaine lettre
			} 
			else xpos = 0; //Si ce n'�tait pas le mot, on retourne � la premi�re lettre
			ppos++; //Dans tous les cas, on va � la prochaine lettre de la phrase
			if(ppos>pnchar) return(false); //Si la phrase est termin�e sans avoir trouv� le mot  
		}
	}*/
	//Optimis�e
	bool lfind(string x, string p)  //Pour "logical find" 
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Cr�er des compteurs
		int xpos = 0 ; int ppos = 0;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //�valuer pour la pr�sente lettre, mais en profiter pour passer � la prochaine
			{
				if(xpos==xnchar) return(true); //Si le mot � rep�rer a �t� rep�r� au complet, on arr�te la fonction
			} 
			else xpos = 0; //Si ce n'�tait pas le mot, on retourne � la premi�re lettre
			if(ppos>pnchar) return(false); //Si la phrase est termin�e sans avoir trouv� le mot  
		}
	}														
														
	//ii) Position premi�re occurence
	int pfind(string x, string p)  //Pour "position find"
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Cr�er des compteurs
		int xpos = 0 ; int ppos = 0;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //�valuer pour la pr�sente lettre, mais en profiter pour passer � la prochaine
			{
				if(xpos==xnchar) return(ppos-xpos); //Si le mot � rep�rer a �t� rep�r� au complet, retourner la position de la premi�re lettre
			} 
			else xpos = 0; //Si ce n'�tait pas le mot, on retourne � la premi�re lettre
			if(ppos>pnchar) return(-1); //Si la phrase est termin�e sans avoir trouv� le mot, retourner -1 (valeur d'erreur choisie ici)  
		}
	}												
	//iii) Position toutes occurences  //Pour "multiple find"
		//Attention: Ici, j'utilise la classe "vector", que je ne ma�trise pas tout � fait
		//ISSSSHHHHHHKKKKK!!! Je n'arrive pas � retourner un array complet! Comment retourner plusieurs valeurs??
				//Il semble que je doive retourner UN SEUL objet, mais d'un type qui me permet de stocker plusieurs informations.
				//How 'bout je cr�e un objet de type "array" personalis�, qui poss�de le pointeur + le nombre d'objets contenus?
				//Je pourrais tant qu'� faire simplement cr�er mon type personalis� genre "vecteur", seulement pour les int.
				//Pour avoir un raccourci � utiliser dans ce code-ci.
	int mfind(string x, string p)
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Cr�er des compteurs
		int xpos = 0 ; int ppos = 0; int xnb = 0;
		//Cr�er un vecteur (personalis�) pour contenir chaque occurence
		vect mult;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //�valuer pour la pr�sente lettre, mais en profiter pour passer � la prochaine
			{
				if(xpos==xnchar) 
				{
				vec.push_back(ppos-xpos); xnb++;  //Si le mot � rep�rer a �t� rep�r� au complet, sauvegarder sa position dans le vecteur
				cout << "\n>� l'assignation: " << ppos-xpos;	
				xpos = 0; //Puisque c'est termin� avec cette it�ration, on remet le mot � son d�but
				}	
			} 
			else xpos = 0; //Si ce n'�tait pas le mot, on retourne � la premi�re lettre
			if(ppos>pnchar) //Si on est rendues � la fin de la phrase, transformer le vecteur en format exportable (array)
			{
				if(xnb!=0)
				{
					//Je devrais: Soit passer l'array + SON NOMBRE D'�L�MENTS en return(),
					//ou bien simplement passer le vecteur (ou tout autre type de classe que je d�cide de cr�er � sa place)
					
					int * arr;
					arr = new int [xnb]; //D�clarer l'array (en tant que dynamique, point� par l'objet arr)
					cout << "\nIl y a " << xnb << " occurences de " << x;
					for(int a=0 ; a<xnb ; a++) 
					{
						arr[a] = vec.at(a) ; 
						cout << "\nDans le vecteur: "<< vec.at(a); cout << "\nDans l'array: "<< arr[a];
					}
					cout << "\nDans la fonction, l'array montre: " << *arr;
					return(*arr);
				}
				else return(-1); //Si la phrase est termin�e sans avoir trouv� le mot, retourner -1 (valeur d'erreur choisie ici)  
			}
		}
	}	

//Z) Test, en utilisant la fonction main() ; va �tre r��crit beaucoup, c'est juste pour voir si tout marche
int main()
{
	string x = "salade" ; string p = "J'aime la Salade.";
	cout << "\n" << x << " est pr�sent dans " << p << " : " << lfind(x,p); 
	cout << "\nDe plus, " << x << " commence � la lettre " << pfind(x,p); 
	string z = "�t" ; string d = "j'�tais �tonn�e et �tourdie."; 
	cout << "\nDans " << d << ", " << z << " se trouve aux emplacements " << mfind(z,d);
}

