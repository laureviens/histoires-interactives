/*
                ///||================================---2018/0i/27---================================||\\\
\\\||================================---Classe personalisée pour imiter les vecteurs---================================||///
*/

/*			
	
		#### Il reste à créer une spécialisation de vect en vect<char>, qui prend des strings comme entrées (constructeur).
			 Pour faire cela, je pourrais toujours overloader l'opérateur de "string litteral" ("").
			 Voir https://en.cppreference.com/w/cpp/language/user_literal
			 
			 Mais c'est un peu chiant et inutile. J'ai fait des tests avec les strings normales, et les longueurs de la fct length()
			 semblent convenir et être constantes. Du moins sur mon ordinateur.
			 Fait que j'suis mieux d'utiliser simplement les strings pour le début, et au pire de bricoler une solution plus personalisée
			 (moins faillible) plus tard.
			 		
*/


		//ATTENTION: Peut-on modifier les objets appelés par []?????
		
		//Je ne pense pas, puisque c'est une fonction qui les RETOURNE...
				//Il faudrait peut-être overrider l'opérateur =, pour celà????
			//Ouin, j'pense que c'est ce qu'il faudrait faire...
		

//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>      //Librairie comprenant les fonctions d'entrée et de sortie de base
#include <fcntl.h>       //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
	
//1) Créer la classe
	template <class Type> //Créer un "template" de type, qui pourra être des int, des char... ce que je veux! 
		class vect
		{
		//Valeurs membres	
		public:
			Type* pt;  //Déclarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'extérieur 
			int nb;  //Déclarer le nombre d'objets de l'array
		//Constructeurs	
			vect<Type>() {nb=0 ; pt = new Type;}  //Créer un constructeur par défaut, pour initialiser tous les paramètres
			vect<Type>(Type nxt) {nb=1 ; pt = new Type [1]; pt[0] = nxt;}  //Créer un constructeur pour créer l'objet avec une seule valeur
			vect<Type>(Type nxt[], int nbpos) {nb=nbpos ; pt = new Type [nbpos] ;	for(int a=0; a < nbpos; a++) pt[a] = nxt[a];}  //Créer un constructeur pour créer à partir d'un array
		//Fonction de modification : ajouter des éléments à la suite (Opérateur +=)	
			void operator += (Type nxt) { //Changer un opérateur permettant d'ajouter un integer à la suite du vecteur
				Type* nwpt = new Type [nb+1];  //Déclarer le nouvel array (transitoire)
				for(int pos=0; pos < nb; pos++) nwpt[pos] = pt[pos];  //Remplir avec les vieilles valeurs
				nwpt[nb++] = nxt; //Ajouter la nouvelle valeur (en même temps de noter que c'est un objet de plus)
				delete[] pt;  //Éliminer le vieux array trop petit (il semble que si on ne spécifie pas combien d'éléments éliminer entre braquettes, ça élimine tout)
				pt = nwpt;  //Assigner le pointeur à l'array actuel
			}		
			void operator += (const vect& nxt) { //Même fonction, mais overloadée pour ajouter un objet de type vect
				Type* nwpt = new Type [nb+nxt.nb];  //Déclarer le nouvel array (transitoire)
				for(int pos=0; pos < nb; pos++) nwpt[pos] = pt[pos];  //Remplir avec les vieilles valeurs
				for(int pos=0; pos < nxt.nb; pos++) nwpt[pos+nb] = nxt.pt[pos];  //Ajouter les nouvelles valeurs
				nb+=nxt.nb;  //Noter le nombre de valeurs qu'on ajoute
				delete[] pt;  //Éliminer le vieux array trop petit (il semble que si on ne spécifie pas combien d'éléments éliminer entre braquettes, ça élimine tout)
				pt = nwpt;  //Assigner le pointeur à l'array actuel
			}		
		//Fonction de modification: ajouter des posititions	(opérateur +)  - les ajoutes à la suite de "pos"
			void operator + (int pos) {
				int emptypos = pos + 1;   //Calculer la position qui sera vide
				Type* nwpt = new Type [nb+1];  //Déclarer le nouvel array (transitoire)
				int oldpos = 0;  //Déclarer un compteur pour les vieilles positions				
				for(int nwpos=0; nwpos < nb; nwpos++) {  //Remplir, en laissant une position vide
					if(nwpos==emptypos) {continue;} 
					nwpt[nwpos] = pt[oldpos++];  //Assigner la valeur, en même temps de passer à la vielle position suivante
				}
				nb++;   //Noter le nombre de valeur qu'on enlève
				delete[] pt;  //Éliminer le vieil array
				pt = nwpt;  //Assigner le pointeur à l'array actuel
			}
						//N'EST PAS ENCORE OVERRIDÉ POUR DES OBJETS DE TYPES VECT, CAR JE N'EN VOIS PAS ENCORE L'UTILITÉ
		//Fonction de modification: supprimer des positions	(opérateur -)
			void operator - (int pos) { //Fonction permettant de supprimer les valeurs à une position spécifique
				Type* nwpt = new Type [nb-1];  //Déclarer le nouvel array (transitoire)
				int nwpos = 0;  //Déclarer un compteur pour les positions actuelles
				for(int oldpos=0; oldpos < nb; oldpos++) {  //Remplir avec les vieilles valeurs
					if(oldpos==pos) continue;
					nwpt[nwpos++] = pt[oldpos];  //Assigner la valeur, en même temps de passer à la position suivante
				}
				nb--;  //Noter le nombre de valeur qu'on enlève
				delete[] pt;  //Éliminer le viel array
				pt = nwpt;  //Assigner le pointeur à l'array actuel
			}		
			void operator - (const vect<int>& nxt) { //Même fonction, mais overloadée pour un objet de type vect
				Type* nwpt = new Type [nb+nxt.nb];  //Déclarer le nouvel array (transitoire)
				int nwpos = 0;  //Déclarer un compteur pour les positions actuelles
				bool skip;  //Déclarer un compteur pour les positions à retirer
				for(int oldpos=0; oldpos < nb; oldpos++) {  //Remplir avec les vieilles valeurs
					skip = false;
					for(int nxtpos=0; nxtpos < nxt.nb; nxtpos++) if(oldpos==nxt.pt[nxtpos]) {skip = true; break;}
					if(skip) continue;
					nwpt[nwpos++] = pt[oldpos];  //Assigner la valeur, en même temps de passer à la position suivante				
				}
				nb-=nxt.nb;  //Noter le nombre de valeurs qu'on enlève
				delete[] pt;  //Éliminer le viel array
				pt = nwpt;  //Assigner le pointeur à l'array actuel
			}	
		//Fonctions d'accès	: retourner certains positions (Opérateur [])
			int operator [] (int pos) { //Créer une fonction permettant d'aller chercher une valeur de l'array (une seule position)
				return(pt[pos]);
			}
			vect<Type> operator [] (vect<int> pos) { //Même fonction, mais overloadée pour un objet de type vect (plusieurs positions)
						//Attention: ne peut pas être appelé par référence (const vect<int>&), probablement à cause de pos[a] qui appelle un array au lieu d'un int?
				Type indx[pos.nb];  //Déclarer un array transitoire
				for(int indxpos=0; indxpos<pos.nb; indxpos++)  indx[indxpos] =  pt[pos[indxpos]]; //Remplir avec les valeurs dans les bonnes positions
				vect<Type> gtvc {indx,pos.nb}; //Créer un objet vect à l'aide de l'array
				return(gtvc); 
			}
		//Fonctions d'accès	: afficher le vecteur en entier
			void out (void) { //Créer une fonction pour simplement afficher l'array dans la console
				std::wcout << "[";
				for(int pos=0; pos< nb-1; pos++) std::wcout << pt[pos] << ",";
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
			for(int pos=0; pos < nb; pos++) pt[pos] = str[pos];
		};
	//Fonction de modification : ajouter des éléments à la suite (Opérateur +=)	
		void operator += (const std::string nxt) { //Même fonction qu'en haut, mais overloadée pour ajouter un objet de type string
			char* nwpt = new char [nb+nxt.length()];  //Déclarer le nouvel array (transitoire)
			for(int pos=0; pos < nb; pos++) nwpt[pos] = pt[pos];  //Remplir avec les vieilles valeurs
			for(int pos=0; pos < nxt.length(); pos++) nwpt[pos+nb] = nxt[pos];  //Ajouter les nouvelles valeurs
			nb+=nxt.length();  //Noter le nombre de valeurs qu'on ajoute
			delete[] pt;  //Éliminer le vieux array trop petit 
			pt = nwpt;  //Assigner le pointeur à l'array actuel
		}			
	//Fonctions d'accès	: afficher le vecteur en entier 
							//Attention: overload de l'ancienne fonction!	
		void out (void) { //Créer une fonction pour simplement afficher la phrase
			for(int pos=0;pos<nb;pos++){
				if(pt[pos]=='À') std::wcout << L"\u00C0";
				else if(pt[pos]=='à') std::wcout << L"\u00E0";
				else if(pt[pos]=='Ç') std::wcout << L"\u00C7";		
				else if(pt[pos]=='ç') std::wcout << L"\u00E7";
				else if(pt[pos]=='É') std::wcout << L"\u00C9";		
				else if(pt[pos]=='é') std::wcout << L"\u00E9";
				else if(pt[pos]=='È') std::wcout << L"\u00C8";
				else if(pt[pos]=='è') std::wcout << L"\u00E8";
				else if(pt[pos]=='Î') std::wcout << L"\u00CE";
				else if(pt[pos]=='î') std::wcout << L"\u00EE";
				else if(pt[pos]=='Ï') std::wcout << L"\u00CF";
				else if(pt[pos]=='ï') std::wcout << L"\u00EF";						
				else if(pt[pos]=='Ô') std::wcout << L"\u00D4";
				else if(pt[pos]=='ô') std::wcout << L"\u00F4";
				else if(pt[pos]=='Ù') std::wcout << L"\u00D9";
				else if(pt[pos]=='ù') std::wcout << L"\u00F9";	
				else if(pt[pos]=='Û') std::wcout << L"\u00DB";
				else if(pt[pos]=='û') std::wcout << L"\u00FB";	
				else {std::wcout << pt[pos];}
			}
		}
	};
	


//3) Tester
/*
int main(){
	
	//Important: permet de mettre le output en unicode (je pense)! De la librairie <fcntl.h> 
	_setmode(_fileno(stdout), _O_U16TEXT);
	
	std::wcout << "\nOk, là on passe aux choses sérieuses.";
	std::wcout << "\n\nOn va essayer de faire un beau vecteur sans accent:\n       ";
	s phrase {"J'aime les bananes au pot, mmmmmhhhh...'"}; phrase.out();
	std::wcout << "\n(ca devrait parler de bananes)";
	
	s phrase2 {"\n\nEh, mais là, ça veut dire... \n                que j'ai même plus besoin de jouer avec des \"std::cout\" pour écrire!"}; phrase2.out();
	
	s phrase3 {"\n        Wouhouooooo! Ça a marché, comme dû, le code a la pêche!"}; phrase3.out();
	
}	*/

