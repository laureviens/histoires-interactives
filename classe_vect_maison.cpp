/*
                ///||================================---2018/0i/27---================================||\\\
\\\||================================---Classe personalisée pour imiter les vecteurs---================================||///
*/

/*			
		#### Je vais essayer de me débarrasser de la classe arr; car elle m'encombre et est redondante.
			 C'est bien, le code est ainsi beaucoup plus clair.	

			 #### Le seul désavantage, c'est que je perds la définition facile des arrays (en une ligne).
			      Au moins, pour les strings, je vais avoir un moyen facile de définir tout ensemble de characters.
			      Pour les autres listes que je compte faire, elles seront probablement davantage des listes de "strings".
			      Ou peut-être pas. Je verrai rendue là si je réssucite les arr.
			  
	
		#### L'opérateur [] semble faire une job similaire à -, mais en plus efficace.
			 Penser à simplifier - (et peut-être +=)? basé sur cela.
	
		#### Il reste à créer une spécialisation de vect en vect<char>, qui prend des strings comme entrées (constructeur).
			 Pour faire cela, je pourrais toujours overloader l'opérateur de "string litteral" ("").
			 Voir https://en.cppreference.com/w/cpp/language/user_literal
			 
			 Mais c'est un peu chiant et inutile. J'ai fait des tests avec les strings normales, et les longueurs de la fct length()
			 semblent convenir et être constantes. Du moins sur mon ordinateur.
			 Fait que j'suis mieux d'utiliser simplement les strings pour le début, et au pire de bricoler une solution plus personalisée
			 (moins faillible) plus tard.
			 		
*/


//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>      //Librairie comprenant les fonctions d'entrée et de sortie de base
#include <fcntl.h>       //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
	
//1) Créer la classe
	template <class T> //Créer un "template" de type, qui pourra être des int, des char... ce que je veux! 
		class vect
		{
		//Valeurs membres	
		public:
			T* pt;  //Déclarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'extérieur 
			int nb;  //Déclarer le nombre d'objets de l'array
		//Constructeurs	
			vect<T>() {nb=0 ; pt = new T;}  //Créer un constructeur par défaut, pour initialiser tous les paramètres
			vect<T>(T nxt) {nb=1 ; pt = new T [1]; pt[0] = nxt;}  //Créer un constructeur pour créer l'objet avec une seule valeur
			vect<T>(T nxt[], int nbpos) {nb=nbpos ; pt = new T [nbpos] ;	for(int a=0; a < nbpos; a++) pt[a] = nxt[a];}  //Créer un constructeur pour créer à partir d'un array
		//Fonction de modification : ajouter des éléments à la suite (Opérateur +=)	
			void operator += (T nxt) { //Changer un opérateur permettant d'ajouter un integer à la suite du vecteur
				T* nwpt = new T [nb+1];  //Déclarer le nouvel array (transitoire)
				for(int a=0; a < nb; a++) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
				nwpt[nb++] = nxt; //Ajouter la nouvelle valeur (en même temps de noter que c'est un objet de plus)
				delete[] pt;  //Éliminer le vieux array trop petit (il semble que si on ne spécifie pas combien d'éléments éliminer entre braquettes, ça élimine tout)
				pt = nwpt;  //Assigner le pointeur à l'array actuel
			}		
			void operator += (const vect& nxt) { //Même fonction, mais overloadée pour ajouter un objet de type vect
				T* nwpt = new T [nb+nxt.nb];  //Déclarer le nouvel array (transitoire)
				for(int a=0; a < nb; a++) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
				for(int a=0; a < nxt.nb; a++) nwpt[a+nb] = nxt.pt[a];  //Ajouter les nouvelles valeurs
				nb+=nxt.nb;  //Noter le nombre de valeurs qu'on ajoute
				delete[] pt;  //Éliminer le vieux array trop petit (il semble que si on ne spécifie pas combien d'éléments éliminer entre braquettes, ça élimine tout)
				pt = nwpt;  //Assigner le pointeur à l'array actuel
			}		
		//Fonction de modification: supprimer des positions	(opérateur -)
			void operator - (int pos) { //Fonction permettant de supprimer les valeurs à une position spécifique
				T* nwpt = new T [nb-1];  //Déclarer le nouvel array (transitoire)
				int nwpos = 0;  //Déclarer un compteur pour les positions actuelles
				for(int a=0; a < nb; a++) {  //Remplir avec les vieilles valeurs
					if(a==pos) continue;
					nwpt[nwpos++] = pt[a];  //Assigner la valeur, en même temps de passer à la position suivante
				}
				nb--;  //Noter le nombre de valeur qu'on enlève
				delete[] pt;  //Éliminer le viel array
				pt = nwpt;  //Assigner le pointeur à l'array actuel
			}		
			void operator - (const vect<int>& nxt) { //Même fonction, mais overloadée pour un objet de type vect
				T* nwpt = new T [nb+nxt.nb];  //Déclarer le nouvel array (transitoire)
				int nwpos = 0;  //Déclarer un compteur pour les positions actuelles
				bool skip;  //Déclarer un compteur pour les positions à retirer
				for(int a=0; a < nb; a++) {  //Remplir avec les vieilles valeurs
					skip = false;
					for(int b=0; b < nxt.nb; b++) if(a==nxt.pt[b]) {skip = true; break;}
					if(skip) continue;
					nwpt[nwpos++] = pt[a];  //Assigner la valeur, en même temps de passer à la position suivante				
				}
				nb-=nxt.nb;  //Noter le nombre de valeurs qu'on enlève
				delete[] pt;  //Éliminer le viel array
				pt = nwpt;  //Assigner le pointeur à l'array actuel
			}	
		//Fonctions d'accès	: retourner certains positions (Opérateur [])
			int operator [] (int pos) { //Créer une fonction permettant d'aller chercher une valeur de l'array (une seule position)
				return(pt[pos]);
			}
			vect<T> operator [] (vect<int> pos) { //Même fonction, mais overloadée pour un objet de type vect (plusieurs positions)
						//Attention: ne peut pas être appelé par référence (const vect<int>&), probablement à cause de pos[a] qui appelle un array au lieu d'un int?
				T indx[pos.nb];  //Déclarer un array transitoire
				for(int a=0; a<pos.nb; a++)  indx[a] =  pt[pos[a]]; //Remplir avec les valeurs dans les bonnes positions
				vect<T> gtvc {indx,pos.nb}; //Créer un objet vect à l'aide de l'array
				return(gtvc); 
			}
		//Fonctions d'accès	: afficher le vecteur en entier (Opérateur ~)
								//Attention! L'opérateur ~ doit être placé au-devant de l'objet vect!			
			void operator ~ (void) { //Créer une fonction pour simplement afficher l'array
				std::wcout << "[";
				for(int a=0; a< nb-1; a++) std::cout << pt[a] << ",";
				std::wcout << pt[nb-1] << "]";
			}
	};

//2) Créer la classe-fille avec des strings

	class s : public vect<char> {
		public:
	//Constructeur spécialisé
		s (std::string str) {
			nb = str.length();
			pt = new char [nb];
			for(int a=0; a < nb; a++) pt[a] = str[a];
		};
	//Fonction de modification : ajouter des éléments à la suite (Opérateur +=)	
		void operator += (const std::string nxt) { //Même fonction qu'en haut, mais overloadée pour ajouter un objet de type string
			char* nwpt = new char [nb+nxt.length()];  //Déclarer le nouvel array (transitoire)
			for(int a=0; a < nb; a++) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
			for(int a=0; a < nxt.length(); a++) nwpt[a+nb] = nxt[a];  //Ajouter les nouvelles valeurs
			nb+=nxt.length();  //Noter le nombre de valeurs qu'on ajoute
			delete[] pt;  //Éliminer le vieux array trop petit (il semble que si on ne spécifie pas combien d'éléments éliminer entre braquettes, ça élimine tout)
			pt = nwpt;  //Assigner le pointeur à l'array actuel
		}			
	//Fonctions d'accès	: afficher le vecteur en entier (Opérateur ~)
							//Attention: overload de l'ancienne fonction!	
		void operator ~ (void) { //Créer une fonction pour simplement afficher la phrase
			for(int a=0;a<nb;a++){
				if(pt[a]=='À') std::wcout << L"\u00C0";
				else if(pt[a]=='à') std::wcout << L"\u00E0";
				else if(pt[a]=='Ç') std::wcout << L"\u00C7";		
				else if(pt[a]=='ç') std::wcout << L"\u00E7";
				else if(pt[a]=='É') std::wcout << L"\u00C9";		
				else if(pt[a]=='é') std::wcout << L"\u00E9";
				else if(pt[a]=='È') std::wcout << L"\u00C8";
				else if(pt[a]=='è') std::wcout << L"\u00E8";
				else if(pt[a]=='Î') std::wcout << L"\u00CE";
				else if(pt[a]=='î') std::wcout << L"\u00EE";
				else if(pt[a]=='Ï') std::wcout << L"\u00CF";
				else if(pt[a]=='ï') std::wcout << L"\u00EF";						
				else if(pt[a]=='Ô') std::wcout << L"\u00D4";
				else if(pt[a]=='ô') std::wcout << L"\u00F4";
				else if(pt[a]=='Ù') std::wcout << L"\u00D9";
				else if(pt[a]=='ù') std::wcout << L"\u00F9";	
				else if(pt[a]=='Û') std::wcout << L"\u00DB";
				else if(pt[a]=='û') std::wcout << L"\u00FB";	
				else {std::wcout << pt[a];}
			}
		}
	};
	


//3) Tester
int main(){
	
	//Important: permet de mettre le output en unicode (je pense)! De la librairie <fcntl.h> 
	_setmode(_fileno(stdout), _O_U16TEXT);
	
	std::wcout << "\nOk, là on passe aux choses sérieuses.";
	std::wcout << "\n\nOn va essayer de faire un beau vecteur sans accent:\n       ";
	s phrase {"J'aime les bananes au pot, mmmmmhhhh...'"}; ~phrase;
	std::wcout << "\n(ca devrait parler de bananes)";
	
	s phrase2 {"\n\nEh, mais là, ça veut dire... \n                que j'ai même plus besoin de jouer avec des \"std::cout\" pour écrire!"}; ~phrase2;
	
	s phrase3 {"\n        Wouhouooooo! Ça a marché, comme dû, le code a la pêche!"}; ~phrase3;
	
}	

