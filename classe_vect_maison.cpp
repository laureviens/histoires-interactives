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
#include <iostream>
using namespace std;

	
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
				cout << "[";
				for(int a=0; a< nb-1; a++) cout << pt[a] << ",";
				cout << pt[nb-1] << "]";
			}
					
	};


//2) Tester
int main()
{
	cout << "\nFait que là... \n\n\n";
	vect<int> test;
	test+=3;
	cout << "\nSupposé contenir la valeur 3 (avec référence normale): " << test.pt[0];
	cout << "\nSupposé contenir la valeur 3 (avec fonction membre): " << test[0];

	test+=44;
	cout << "\nEt là, supposé avoir 44 en deuxième position (avec référence normale) : " << test.pt[1];
	cout << "\nEt là, supposé avoir 44 en deuxième position (avec fonction membre) : " << test[1];	
	
	test+=22;
	cout << "\nEt si j'ose une troisième augmentation, avec 22 : " << test[2];	
	
	cout << "\n\nAu total, l'objet ressemble à: "; ~test;
	
	cout << "\n\nOk, là j'vais essayer de créer un nouveau vecteur et d'additionner tout:";
	vect<int> test2;
	test2+=55;
	cout << "\nTest 2 ressemble maintenant à: "; ~test2;
	cout << "\nEt là j'ajoute le premier objet au deuxième:";
	test2+=test;
	cout << "\n\nEt le deuxième ressemble maintenant à: ";
	~test2;
	
	cout << "\n\nOk, et si j'essaie d'ajouter un array complet:";
	int arr[3] {4,4,4};
	vect<int> test3 = {arr,3};
	test2+=test3;
	cout << "\nEt maintenant, Test 2 ressemble à:";
	~test2;
	
	cout << "\n\n Et si j'essaie de voir ce qu'il y a en position [0,2,4] (faire +1 pour comprendre les positions de C++): \n";
	int arrget[3] {0,2,4}; vect<int> testget = {arrget,3};
	~test2[testget];
	
	cout << "\n\nEt là, je vais enlever la deuxième position:\n";
	test2-1;
	~test2;
	
	cout << "\n\nEt là, les positions [0,2,3] (faire +1 pour comprendre les positions de C++): \n";
	int arrdel[3] {0,2,3}; vect<int> testdel {arrdel,3};
	test2-testdel;
	~test2;
	
	cout << "\n\nMais, disons, si je veux tester l'opérateur [] des arr... Voir ce que [0,2,4] cache en position [0,2]: \n";
	int arrget2[2] = {0,2} ; vect<int> testget2 {arrget2,2};
	vect<int> testget3 = testget[testget2];
	~testget3;
	
	cout << "\n\nEt... maintenant, encore avec arr[], qu'est-ce que ça donne... avec des doubles? Voir [0.23,0.34,0.45], même positions: \n";
	double arrget3[3] = {0.23,0.34,0.45}; 
	vect<double> testget4 {arrget3,3};
	vect<double> testget5 = testget4[testget2];
	~testget5;	
	}	

