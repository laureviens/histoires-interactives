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
	En bref, seules 15 couleurs sont disponibles sur Windows. Ouin, j'ai vraiment pas trouvé mieux en cherchant sur Google. Inexistant.
	
	La bonne nouvelle, c'est toutefois qu'elles peuvent être changées soit pour toute la console, soit pour seulement le texte
	écrit après le changement de commande.
	
	Donc, en jouant avec les positions, on pourrait faire des bordures de différentes couleurs, des cartes bien lisibles, des menus, etc.
	
	Btw, pour le faire en linux, voir : https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
	et : https://stackoverflow.com/questions/138383/colored-grep/138528#138528
	*/
	

//P-T) Classe personalisée pour imiter les vecteurs?????
//------------------------------------------------------------------------------------------------------------------------------------------------------
//AIde: https://stackoverflow.com/questions/13431567/how-to-make-an-array-with-a-dynamic-size-general-usage-of-dynamic-arrays-maybe

//Si je crée cette classe en tant que TEMPLATE (modèle générique accomodant tous les types),
	//je pourrais ne pas seulement me limiter aux integer, mais stocker des arrays de toutes sortes!
	//(théoriquement, je pourrais même utiliser ce template pour stocker mes strings, avec l'avantage qu'elles
	//conserveraient en tout temps leur nombre de caractères...
		//Mais en même temps, les strings sont un objet déjà là et utile, et c'est son seul défaut. Et j'ai plus besoin des opérations de base
		//(operation overload) des strings ("AC"+"-TG" == "AC-TG") que d'une allocation dynamique de la mémoire.
	//Pour l'instant, je me limite aux int, pour garder ça simple. À upgrader après.

	//Creating the class
	class vect 
	{
	public:
				/*int ar, nb;  //L'array et le nombre d'objets 
				int* pt;     //Le pointeur de l'array (plus pratique)*/    //Obsolète, car le pointeur seul suffit pour créer/référer un objet!
		int* pt; int nb;  //Créer les objets contenus dans la classe, soit le pointeur et le nombre d'objets de l'array pointé	
		
		vect() {nb=0};// Créer un constructeur par défaut, pour être certaine d'avoir 0 objet quand un nouveau vect est créé
		
		void add(int nxt) //Créer une fonction permettant d'ajouter un integer à la suite du vecteur
		{
			if(*this.nb==0) 
			{
				pt = new int; //Si le vect est nouveau, simplement créer array de taille 1
				pt = nxt
			}
			else
			{
				int* nwpt = new int [*this.nb+1];  //Déclarer le nouvel array (transitoire)
				for(int a=0; a < *this.nb; ++a) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
				nwpt[*this.nb] = nxt //Ajouter la nouvelle valeur
				delete[] pt  //Éliminer le vieux array trop petit (il semble que si on ne spécifie pas combien d'éléments éliminer entre braquettes, ça élimine tout)
				pt = nwpt  //Assigner le pointeur à l'array actuel
			}
		} 
		
		void add(vect nxt){}  //Ça serait utile d'overloader la fonction, pour permettre d'ajouter à la suite tout un vecteur!
				//je pense bien que je peux référencer une objet de sa propre classe en définissant un membre... à vérifier...
				
		void rem(int pos){} //Ici, l'integer réfère à la position de l'objet à enlever
		void rem(vect pos){} 
		
		//Faudrait aussi quelque chose pour ajouter (ou créer l'array principal avec) un array normal, pour prendre avantage de la définition
			//simple à l'écriture (int arr [3] = {2,3,4})
			//Mais je ne sais pas quel paramètres mettre... Faudrait un paramètre pour le nombre de caractères, et un pour l'array en tant que tel?
		void add(int nb, int next)	{} //où next est l'array en tant que tel. Ou bien son pointeur. Ouin. Mieux vaut travailler en pointeurs tout le temps.		
	} 
	
		//Et là il reste l'écriture, où on crée les choses pour mieux les effacer ensuite.
	
	
//A) Fonction pour repérer des mots
//------------------------------------------------------------------------------------------------------------------------------------------------------
				// x est le mot à repérer,
				// p est la phrase dans laquelle repérer le mot
	
		//ATTENTION: J'aurais aussi très bien pu utiliser la fonction .find, déjà incluse comme membre de la classe string (dans std).
	
		//ATTENTION!!! Pour trouver la longueur des strings, j'utilise .length(), qui calcule la mémoire utilisée.
		//Ça va bien quand j'utilise de simples char, car leur taille est 1 bt. Mais les accents vont probablement pas entrer là-dedans...
				
		//ATTENTION!!! Je pourrais utiliser, au lieu de string comme type, de mettre const string&.
		//Présentement (avec string), le string est copié pour caller la fonction.
		//Avec l'alternative (const string&), seulement une référence (pointeur) est copiée, et "const"	assure que l'objet original n'est pas changé.	
				
	//i) Logical
	/*bool lfind(string x, string p)
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();  //La synthaxe semble obligatoire; length(x) ne marche pas (la fonction length() seule n'est pas définie).
															 //En fait, ici length() est une fonction membre de la classe string...
		//Créer des compteurs
		int xpos = 0 ; int ppos = 0;
		while(true)
		{
			if(x[xpos]==p[ppos])
			{
				if(xpos==xnchar-1) return(true); //Si le mot à repérer a été repéré au complet, on arrête la fonction
				xpos++;  //Si le mot n'est pas terminé, on passe à la prochaine lettre
			} 
			else xpos = 0; //Si ce n'était pas le mot, on retourne à la première lettre
			ppos++; //Dans tous les cas, on va à la prochaine lettre de la phrase
			if(ppos>pnchar) return(false); //Si la phrase est terminée sans avoir trouvé le mot  
		}
	}*/
	//Optimisée
	bool lfind(string x, string p)  //Pour "logical find" 
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Créer des compteurs
		int xpos = 0 ; int ppos = 0;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //Évaluer pour la présente lettre, mais en profiter pour passer à la prochaine
			{
				if(xpos==xnchar) return(true); //Si le mot à repérer a été repéré au complet, on arrête la fonction
			} 
			else xpos = 0; //Si ce n'était pas le mot, on retourne à la première lettre
			if(ppos>pnchar) return(false); //Si la phrase est terminée sans avoir trouvé le mot  
		}
	}														
														
	//ii) Position première occurence
	int pfind(string x, string p)  //Pour "position find"
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Créer des compteurs
		int xpos = 0 ; int ppos = 0;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //Évaluer pour la présente lettre, mais en profiter pour passer à la prochaine
			{
				if(xpos==xnchar) return(ppos-xpos); //Si le mot à repérer a été repéré au complet, retourner la position de la première lettre
			} 
			else xpos = 0; //Si ce n'était pas le mot, on retourne à la première lettre
			if(ppos>pnchar) return(-1); //Si la phrase est terminée sans avoir trouvé le mot, retourner -1 (valeur d'erreur choisie ici)  
		}
	}												
	//iii) Position toutes occurences  //Pour "multiple find"
		//Attention: Ici, j'utilise la classe "vector", que je ne maîtrise pas tout à fait
		//ISSSSHHHHHHKKKKK!!! Je n'arrive pas à retourner un array complet! Comment retourner plusieurs valeurs??
				//Il semble que je doive retourner UN SEUL objet, mais d'un type qui me permet de stocker plusieurs informations.
				//How 'bout je crée un objet de type "array" personalisé, qui possède le pointeur + le nombre d'objets contenus?
				//Je pourrais tant qu'à faire simplement créer mon type personalisé genre "vecteur", seulement pour les int.
				//Pour avoir un raccourci à utiliser dans ce code-ci.
	int mfind(string x, string p)
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Créer des compteurs
		int xpos = 0 ; int ppos = 0; int xnb = 0;
		//Créer un vecteur (personalisé) pour contenir chaque occurence
		vect mult;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //Évaluer pour la présente lettre, mais en profiter pour passer à la prochaine
			{
				if(xpos==xnchar) 
				{
				vec.push_back(ppos-xpos); xnb++;  //Si le mot à repérer a été repéré au complet, sauvegarder sa position dans le vecteur
				cout << "\n>À l'assignation: " << ppos-xpos;	
				xpos = 0; //Puisque c'est terminé avec cette itération, on remet le mot à son début
				}	
			} 
			else xpos = 0; //Si ce n'était pas le mot, on retourne à la première lettre
			if(ppos>pnchar) //Si on est rendues à la fin de la phrase, transformer le vecteur en format exportable (array)
			{
				if(xnb!=0)
				{
					//Je devrais: Soit passer l'array + SON NOMBRE D'ÉLÉMENTS en return(),
					//ou bien simplement passer le vecteur (ou tout autre type de classe que je décide de créer à sa place)
					
					int * arr;
					arr = new int [xnb]; //Déclarer l'array (en tant que dynamique, pointé par l'objet arr)
					cout << "\nIl y a " << xnb << " occurences de " << x;
					for(int a=0 ; a<xnb ; a++) 
					{
						arr[a] = vec.at(a) ; 
						cout << "\nDans le vecteur: "<< vec.at(a); cout << "\nDans l'array: "<< arr[a];
					}
					cout << "\nDans la fonction, l'array montre: " << *arr;
					return(*arr);
				}
				else return(-1); //Si la phrase est terminée sans avoir trouvé le mot, retourner -1 (valeur d'erreur choisie ici)  
			}
		}
	}	

//Z) Test, en utilisant la fonction main() ; va être réécrit beaucoup, c'est juste pour voir si tout marche
int main()
{
	string x = "salade" ; string p = "J'aime la Salade.";
	cout << "\n" << x << " est présent dans " << p << " : " << lfind(x,p); 
	cout << "\nDe plus, " << x << " commence à la lettre " << pfind(x,p); 
	string z = "ét" ; string d = "j'étais étonnée et étourdie."; 
	cout << "\nDans " << d << ", " << z << " se trouve aux emplacements " << mfind(z,d);
}

