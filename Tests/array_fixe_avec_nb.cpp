#include <iostream>   //Pour les entrées/sorties
using namespace std;


			//Testing a class of fixed arrays (no dynamic memory usage) including the number of elements
			
				//iii) classe : arr ; sauvegarde un array avec son nombre d'éléments
						//Les membres spéciaux ont été copiés de : http://www.cplusplus.com/doc/tutorial/classes2/
	template <class Type>
		class arr {
			//Valeurs membres	
			public:
				Type* pt;  //Déclarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'extérieur 
				int nb;  //Déclarer le nombre d'objets de l'array
			//Constructeurs	: attention, le constructeur rend nul tous les pointeurs qu'on lui donne! Comme un "move-constructor"!
				arr<Type>() : nb(0), pt(nullptr) {cout << "\nAttention: cet objet arr<> est vide (nullptr)";}  //Défaut 
				arr<Type>(Type& nxt) : nb(1), pt(&nxt) {nxt = nullptr;}  //Une seule valeur
				arr<Type>(Type nxt[], int nbpos) : nb(nbpos), pt(nxt) {nxt = nullptr;}  //Array pré-existant
				arr<Type>(Type nxt1,Type nxt2) : nb(2) {Type pt [2] = {nxt1,nxt2};}    //2 éléments
				arr<Type>(Type nxt1,Type nxt2,Type nxt3) : nb(3) {Type pt [3] = {nxt1,nxt2,nxt3};}    //...
				arr<Type>(Type nxt1,Type nxt2,Type nxt3,Type nxt4) : nb(4) {Type pt [4] = {nxt1,nxt2,nxt3,nxt4};}
				arr<Type>(Type nxt1,Type nxt2,Type nxt3,Type nxt4,Type nxt5) : nb(5) {Type pt [5] = {nxt1,nxt2,nxt3,nxt4,nxt5};}
				arr<Type>(Type nxt1,Type nxt2,Type nxt3,Type nxt4,Type nxt5,Type nxt6) : nb(6) {Type pt [6] = {nxt1,nxt2,nxt3,nxt4,nxt5,nxt6};}
				arr<Type>(Type nxt1,Type nxt2,Type nxt3,Type nxt4,Type nxt5,Type nxt6,Type nxt7) : nb(7) {Type pt [7] = {nxt1,nxt2,nxt3,nxt4,nxt5,nxt6,nxt7};}
				arr<Type>(Type nxt1,Type nxt2,Type nxt3,Type nxt4,Type nxt5,Type nxt6,Type nxt7,Type nxt8) : nb(8) {Type pt [8] = {nxt1,nxt2,nxt3,nxt4,nxt5,nxt6,nxt7,nxt8};}
				
	   		//Opérateur d'accès : []
			   Type operator[] (int pos) {
			   		return(pt[pos]);
			   }			
		};	
		
		
	int main (void) {
		
		//Créer un array
		int test1 [3] {1,2,3};
		
		//Tenter de le mettre dans ma classe
		arr<int> arrtest {test1, 3};
		
		//Voir si ça a marché
		cout << "Taille de l'array: " << arrtest.nb<< "\n";
		for(int a=0; a<arrtest.nb; a++) cout << arrtest.pt[a];       //Devrait s'afficher
		for(int a=0; a<arrtest.nb; a++) cout << test1[a];       			//Ne devrait pas s'afficher; s'affiche quand même.
																				//Probablement parce que je ne l'ai pas passé par référence
																						//Ce qui ne se fait pas tant, pour des arrays de taille dfférentes
																					//Je pourrais toujours y aller avec un template <int NB>, mais ce serait chiant.
																					//Quoi que ma méthode d'initialisation est boueteuse aussi, ici.
																						//Bon.
																					//Ce que je viens d'écrire marche, ça va être ça pour le moment.
		//Et maintenant, pour l'extension avec plein de nombres...
		//arr<char> test2 {'S','a','l','u','t'};
		arr<char> test2 {1,1,1,1,1};
		cout << "\n";
		for(int a=0; a<test2.nb; a++) cout << test2.pt[a];                    //Mh.... les caractères ne s'affichent pas correctement, par contre. Why?++
		cout << " est un mot de " << test2.nb << " lettres.";                     //Mh, whatever. F'rai ça plus tard.
																//... probablement à cause du conflit Type* pt  VS  Type pt [n] = {1,2,...,n}  ???
	}
