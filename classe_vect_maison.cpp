/*
                ///||================================---2018/0i/27---================================||\\\
\\\||================================---Classe personalis�e pour imiter les vecteurs---================================||///
*/

/*			
	
		#### Il reste � cr�er une sp�cialisation de vect en vect<char>, qui prend des strings comme entr�es (constructeur).
			 Pour faire cela, je pourrais toujours overloader l'op�rateur de "string litteral" ("").
			 Voir https://en.cppreference.com/w/cpp/language/user_literal
			 
			 Mais c'est un peu chiant et inutile. J'ai fait des tests avec les strings normales, et les longueurs de la fct length()
			 semblent convenir et �tre constantes. Du moins sur mon ordinateur.
			 Fait que j'suis mieux d'utiliser simplement les strings pour le d�but, et au pire de bricoler une solution plus personalis�e
			 (moins faillible) plus tard.
			 		
*/


		//ATTENTION: Peut-on modifier les objets appel�s par []?????
		
		//Je ne pense pas, puisque c'est une fonction qui les RETOURNE...
				//Il faudrait peut-�tre overrider l'op�rateur =, pour cel�????
			//Ouin, j'pense que c'est ce qu'il faudrait faire...
		

//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>      //Librairie comprenant les fonctions d'entr�e et de sortie de base
#include <fcntl.h>       //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
	
//1) Cr�er la classe
	template <class Type> //Cr�er un "template" de type, qui pourra �tre des int, des char... ce que je veux! 
		class vect
		{
		//Valeurs membres	
		public:
			Type* pt;  //D�clarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'ext�rieur 
			int nb;  //D�clarer le nombre d'objets de l'array
		//Constructeurs	
			vect<Type>() {nb=0 ; pt = new Type;}  //Cr�er un constructeur par d�faut, pour initialiser tous les param�tres
			vect<Type>(Type nxt) {nb=1 ; pt = new Type [1]; pt[0] = nxt;}  //Cr�er un constructeur pour cr�er l'objet avec une seule valeur
			vect<Type>(Type nxt[], int nbpos) {nb=nbpos ; pt = new Type [nbpos] ;	for(int a=0; a < nbpos; a++) pt[a] = nxt[a];}  //Cr�er un constructeur pour cr�er � partir d'un array
		//Fonction de modification : ajouter des �l�ments � la suite (Op�rateur +=)	
			void operator += (Type nxt) { //Changer un op�rateur permettant d'ajouter un integer � la suite du vecteur
				Type* nwpt = new Type [nb+1];  //D�clarer le nouvel array (transitoire)
				for(int pos=0; pos < nb; pos++) nwpt[pos] = pt[pos];  //Remplir avec les vieilles valeurs
				nwpt[nb++] = nxt; //Ajouter la nouvelle valeur (en m�me temps de noter que c'est un objet de plus)
				delete[] pt;  //�liminer le vieux array trop petit (il semble que si on ne sp�cifie pas combien d'�l�ments �liminer entre braquettes, �a �limine tout)
				pt = nwpt;  //Assigner le pointeur � l'array actuel
			}		
			void operator += (const vect& nxt) { //M�me fonction, mais overload�e pour ajouter un objet de type vect
				Type* nwpt = new Type [nb+nxt.nb];  //D�clarer le nouvel array (transitoire)
				for(int pos=0; pos < nb; pos++) nwpt[pos] = pt[pos];  //Remplir avec les vieilles valeurs
				for(int pos=0; pos < nxt.nb; pos++) nwpt[pos+nb] = nxt.pt[pos];  //Ajouter les nouvelles valeurs
				nb+=nxt.nb;  //Noter le nombre de valeurs qu'on ajoute
				delete[] pt;  //�liminer le vieux array trop petit (il semble que si on ne sp�cifie pas combien d'�l�ments �liminer entre braquettes, �a �limine tout)
				pt = nwpt;  //Assigner le pointeur � l'array actuel
			}		
		//Fonction de modification: ajouter des posititions	(op�rateur +)  - les ajoutes � la suite de "pos"
			void operator + (int pos) {
				int emptypos = pos + 1;   //Calculer la position qui sera vide
				Type* nwpt = new Type [nb+1];  //D�clarer le nouvel array (transitoire)
				int oldpos = 0;  //D�clarer un compteur pour les vieilles positions				
				for(int nwpos=0; nwpos < nb; nwpos++) {  //Remplir, en laissant une position vide
					if(nwpos==emptypos) {continue;} 
					nwpt[nwpos] = pt[oldpos++];  //Assigner la valeur, en m�me temps de passer � la vielle position suivante
				}
				nb++;   //Noter le nombre de valeur qu'on enl�ve
				delete[] pt;  //�liminer le vieil array
				pt = nwpt;  //Assigner le pointeur � l'array actuel
			}
						//N'EST PAS ENCORE OVERRID� POUR DES OBJETS DE TYPES VECT, CAR JE N'EN VOIS PAS ENCORE L'UTILIT�
		//Fonction de modification: supprimer des positions	(op�rateur -)
			void operator - (int pos) { //Fonction permettant de supprimer les valeurs � une position sp�cifique
				Type* nwpt = new Type [nb-1];  //D�clarer le nouvel array (transitoire)
				int nwpos = 0;  //D�clarer un compteur pour les positions actuelles
				for(int oldpos=0; oldpos < nb; oldpos++) {  //Remplir avec les vieilles valeurs
					if(oldpos==pos) continue;
					nwpt[nwpos++] = pt[oldpos];  //Assigner la valeur, en m�me temps de passer � la position suivante
				}
				nb--;  //Noter le nombre de valeur qu'on enl�ve
				delete[] pt;  //�liminer le viel array
				pt = nwpt;  //Assigner le pointeur � l'array actuel
			}		
			void operator - (const vect<int>& nxt) { //M�me fonction, mais overload�e pour un objet de type vect
				Type* nwpt = new Type [nb+nxt.nb];  //D�clarer le nouvel array (transitoire)
				int nwpos = 0;  //D�clarer un compteur pour les positions actuelles
				bool skip;  //D�clarer un compteur pour les positions � retirer
				for(int oldpos=0; oldpos < nb; oldpos++) {  //Remplir avec les vieilles valeurs
					skip = false;
					for(int nxtpos=0; nxtpos < nxt.nb; nxtpos++) if(oldpos==nxt.pt[nxtpos]) {skip = true; break;}
					if(skip) continue;
					nwpt[nwpos++] = pt[oldpos];  //Assigner la valeur, en m�me temps de passer � la position suivante				
				}
				nb-=nxt.nb;  //Noter le nombre de valeurs qu'on enl�ve
				delete[] pt;  //�liminer le viel array
				pt = nwpt;  //Assigner le pointeur � l'array actuel
			}	
		//Fonctions d'acc�s	: retourner certains positions (Op�rateur [])
			int operator [] (int pos) { //Cr�er une fonction permettant d'aller chercher une valeur de l'array (une seule position)
				return(pt[pos]);
			}
			vect<Type> operator [] (vect<int> pos) { //M�me fonction, mais overload�e pour un objet de type vect (plusieurs positions)
						//Attention: ne peut pas �tre appel� par r�f�rence (const vect<int>&), probablement � cause de pos[a] qui appelle un array au lieu d'un int?
				Type indx[pos.nb];  //D�clarer un array transitoire
				for(int indxpos=0; indxpos<pos.nb; indxpos++)  indx[indxpos] =  pt[pos[indxpos]]; //Remplir avec les valeurs dans les bonnes positions
				vect<Type> gtvc {indx,pos.nb}; //Cr�er un objet vect � l'aide de l'array
				return(gtvc); 
			}
		//Fonctions d'acc�s	: afficher le vecteur en entier
			void out (void) { //Cr�er une fonction pour simplement afficher l'array dans la console
				std::wcout << "[";
				for(int pos=0; pos< nb-1; pos++) std::wcout << pt[pos] << ",";
				std::wcout << pt[nb-1] << "]";
			}
	};

//2) Cr�er la classe-fille avec des strings

	class s : public vect<char> {
		public:
	//Constructeur sp�cialis�
		s (std::string str) {
			nb = str.length();
			pt = new char [nb];
			for(int pos=0; pos < nb; pos++) pt[pos] = str[pos];
		};
	//Fonction de modification : ajouter des �l�ments � la suite (Op�rateur +=)	
		void operator += (const std::string nxt) { //M�me fonction qu'en haut, mais overload�e pour ajouter un objet de type string
			char* nwpt = new char [nb+nxt.length()];  //D�clarer le nouvel array (transitoire)
			for(int pos=0; pos < nb; pos++) nwpt[pos] = pt[pos];  //Remplir avec les vieilles valeurs
			for(int pos=0; pos < nxt.length(); pos++) nwpt[pos+nb] = nxt[pos];  //Ajouter les nouvelles valeurs
			nb+=nxt.length();  //Noter le nombre de valeurs qu'on ajoute
			delete[] pt;  //�liminer le vieux array trop petit 
			pt = nwpt;  //Assigner le pointeur � l'array actuel
		}			
	//Fonctions d'acc�s	: afficher le vecteur en entier 
							//Attention: overload de l'ancienne fonction!	
		void out (void) { //Cr�er une fonction pour simplement afficher la phrase
			for(int pos=0;pos<nb;pos++){
				if(pt[pos]=='�') std::wcout << L"\u00C0";
				else if(pt[pos]=='�') std::wcout << L"\u00E0";
				else if(pt[pos]=='�') std::wcout << L"\u00C7";		
				else if(pt[pos]=='�') std::wcout << L"\u00E7";
				else if(pt[pos]=='�') std::wcout << L"\u00C9";		
				else if(pt[pos]=='�') std::wcout << L"\u00E9";
				else if(pt[pos]=='�') std::wcout << L"\u00C8";
				else if(pt[pos]=='�') std::wcout << L"\u00E8";
				else if(pt[pos]=='�') std::wcout << L"\u00CE";
				else if(pt[pos]=='�') std::wcout << L"\u00EE";
				else if(pt[pos]=='�') std::wcout << L"\u00CF";
				else if(pt[pos]=='�') std::wcout << L"\u00EF";						
				else if(pt[pos]=='�') std::wcout << L"\u00D4";
				else if(pt[pos]=='�') std::wcout << L"\u00F4";
				else if(pt[pos]=='�') std::wcout << L"\u00D9";
				else if(pt[pos]=='�') std::wcout << L"\u00F9";	
				else if(pt[pos]=='�') std::wcout << L"\u00DB";
				else if(pt[pos]=='�') std::wcout << L"\u00FB";	
				else {std::wcout << pt[pos];}
			}
		}
	};
	


//3) Tester
/*
int main(){
	
	//Important: permet de mettre le output en unicode (je pense)! De la librairie <fcntl.h> 
	_setmode(_fileno(stdout), _O_U16TEXT);
	
	std::wcout << "\nOk, l� on passe aux choses s�rieuses.";
	std::wcout << "\n\nOn va essayer de faire un beau vecteur sans accent:\n       ";
	s phrase {"J'aime les bananes au pot, mmmmmhhhh...'"}; phrase.out();
	std::wcout << "\n(ca devrait parler de bananes)";
	
	s phrase2 {"\n\nEh, mais l�, �a veut dire... \n                que j'ai m�me plus besoin de jouer avec des \"std::cout\" pour �crire!"}; phrase2.out();
	
	s phrase3 {"\n        Wouhouooooo! �a a march�, comme d�, le code a la p�che!"}; phrase3.out();
	
}	*/

