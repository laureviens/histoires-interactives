/*
                ///||================================---2018/0i/27---================================||\\\
\\\||================================---Classe personalisée pour imiter les vecteurs---================================||///
*/

/*		
						
		#### L'indexation de arr à partir de vect ne marche toujours pas...				
					##Au pire, 	
						
		#### Finalement, il faudrait également élargir cette classe à des entrées autres que des integers.
		     Genre les doubles, qui ne devraient pas causer de problèmes.
		     Surtout les characters, probablement du type wchar_t. Pour que ce soit en unicode.
			 		#### Dans le fond, si je me fie à mon prototype pour afficher des phrases avec accents,
					     tout pourrait se passer seulement dans la fonction qui affiche, pas dans l'entreposage.
						 Donc je n'aurais qu'à trouver des manières rapides de convertir des strings (normales)
						 en classe de type "arr" ou "vect" (qui contiennent "naturellement" le nombre de caractères).
						 
						 En même temps, l'utilisation de caractères spéciaux du type \n rend le tout problématique,
						 car ils ne compteraient pas pour un seul caractère.   ##2019-05-10: En fait, oui. Voir le test.
						 Je pourrais toujours utiliser un caractère genre ¤ ou ¢, ou § ou ¶ pour sauter une ligne.
						 Et en prendre un autre pour faire des caractères "transparents".
						 
						 Pour utiliser le raccourci "string", je suis obligée, je crois, d'employer la fonction membre "length". Ou l'objet "size_t".
						 Mais ça ne donne pas le nombre de caractères contenus dans l'objet, mais la taille totale de l'objet.
						 Donc ne fonctionne pas.
						 Donc... Faudrait essayer de copier cette synthaxe facile dans un objet custom (genre "arr")?
						 
						 Officiellement, ici, https://en.cppreference.com/w/cpp/language/user_literal, ça dit qu'on peut le faire!
						 On peut overloader un "" string litteral operator?
						 
						 ##2019-05-10: J'ai testé la fonction "length" des strings, et elle semble fonctionner comme je l'entends.
						 	Au pire, je peux toujours débuter en mettant des strings en entrée, à la fois aux arr et aux vect, 
						 	et modifier par la suite en créant des syntaxes maison avec l'overload de string litteral operator,
						 	si je rencontre des problèmes avec les strings.
						 	
						 
		#### Voir http://www.cplusplus.com/reference/string/string/, qui donne toutes les fonctions membres de "string",
		     ce qui donne des belles idées sur les opérateurs utiles à inclure.				 	
*/



//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>
using namespace std;


//1) Créer une classe d'array permettant une synthaxe facile

template <class T> //Créer un "template" de type, qui pourra être des int, des char... ce que je veux! 
	
	class vect; //Déclarer la classe de vecteur pour pouvoir y référer comme friend
	
	template <class T, int N>
	class arr 
		{
		//Valeurs membres	
		public:
	    	static const int nb = N;  //Déclarer le nombre d'éléments dans l'array comme N
		    T pt[nb];  //Déclarer un array fixe (pas dynamique) de la bonne taille; publique, pour pouvoir le changer et le créer facilement
		//Fonctions d'accès	: retourner certains positions (Opérateur [])
			int operator [] (int pos) { //Créer une fonction permettant d'aller chercher une valeur de l'array (une seule position)
				return(pt[pos]);
			}			
			/*  
			vect<T> operator [] (vect<int> pos) { //Même fonction, mais overloadée pour un objet de type vect (plusieurs positions)
				arr<T,pos.nb> gtar;  //Déclarer un arr transitoire
				for(int a=0; a<pos.nb; a++)  gtar.pt[a] =  pt[pos[a]]; //Remplir avec les valeurs dans les bonnes positions
				vect<T> gtvc = gtar; //Créer un objet vect à l'aide de l'arr
				return(gtvc); 
			}*/                                    //Ne semble pas se compiler ici, probablement parce que vect n'est pas encore bien explicité?
			template<int M>            //Créer un nouveau template, pour que N et M diffèrent (habituellement, M<N)
			vect<T> operator [] (arr<int,M> pos) { //Même fonction, mais overloadée pour un objet de type arr (plusieurs positions)
				arr<T,pos.nb> gtar;  //Déclarer un arr transitoire
				for(int a=0; a<pos.nb; a++)  gtar.pt[a] =  pt[pos[a]]; //Remplir avec les valeurs dans les bonnes positions
				vect<T> gtvc = gtar; //Créer un objet vect à l'aide de l'arr
				return(gtvc);
			}
	};
	
//2) Créer la classe
	template <class T> //Créer un "template" de type, qui pourra être des int, des char... ce que je veux! 
		class vect
		{
		//Valeurs membres	
		public:
			T* pt;  //Déclarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'extérieur 
		private:
			int nb;  //Déclarer le nombre d'objets de l'array comme privé, pour qu'on ne puisse que le changer par += et -=.
		public:
		//Constructeurs	
			vect<T>() {nb=0 ; pt = new T;}  //Créer un constructeur par défaut, pour initialiser tous les paramètres
			vect<T>(int nxt) {nb=1 ; pt = new T [1]; pt[0] = nxt;}  //Créer un constructeur pour créer l'objet avec une seule valeur
		template <int N>
			vect(arr<T,N> nxt) {nb=nxt.nb ; pt = new T [nxt.nb] ;	for(int a=0; a < nxt.nb; a++) pt[a] = nxt.pt[a];}  //Créer un constructeur pour arr
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
		template <int N>
			void operator += (const arr<T,N>& nxt) { //Même fonction, mais overloadée pour ajouter un objet de type arr
				T* nwpt = new T [nb+nxt.nb];  //Déclarer le nouvel array (transitoire)
				for(int a=0; a < nb; a++) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
				for(int a=0; a < nxt.nb; a++) nwpt[a+nb] = nxt.pt[a];  //Ajouter les nouvelles valeurs
				nb+=nxt.nb;  //Noter le nombre de valeurs qu'on ajoute
				delete[] pt;  //Éliminer le vieux array trop petit (il semble que si on ne spécifie pas combien d'éléments éliminer entre braquettes, ça élimine tout)
				pt = nwpt;  //Assigner le pointeur à l'array actuel
			}			
		//Fonction de modification: supprimer des positions	
			void del (int pos) { //Fonction permettant de supprimer les valeurs à une position spécifique
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
			void del (const vect<int>& nxt) { //Même fonction, mais overloadée pour un objet de type vect
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
		template <int N>
			void del (const arr<T,N>& nxt)  { //Même fonction, mais overloadée pour ajouter un objet de type arr
				T* nwpt = new T [nb+nxt.nb];  //Déclarer le nouvel array (transitoire)
				int nwpos = 0;  //Déclarer un compteur pour les positions actuelles
				bool skip;  //Déclarer un compteur pour les positions à retirer
				for(int a=0; a < nb; a++) {   //Remplir avec les vieilles valeurs
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
				arr<T,pos.nb> gtar;  //Déclarer un arr transitoire
				for(int a=0; a<pos.nb; a++)  gtar.pt[a] =  pt[pos[a]]; //Remplir avec les valeurs dans les bonnes positions
				vect<T> gtvc = gtar; //Créer un objet vect à l'aide de l'arr
				return(gtvc); 
			}
		template <int N>
			vect<T> operator [] (arr<int,N> pos) { //Même fonction, mais overloadée pour un objet de type arr (plusieurs positions)
				arr<T,pos.nb> gtar;  //Déclarer un arr transitoire
				for(int a=0; a<pos.nb; a++)  gtar.pt[a] =  pt[pos[a]]; //Remplir avec les valeurs dans les bonnes positions
				vect<T> gtvc = gtar; //Créer un objet vect à l'aide de l'arr
				return(gtvc);
			}
		//Fonctions d'accès	: afficher le vecteur			
			void see(void) { //Créer une fonction pour simplement afficher l'array
				cout << "[";
				for(int a=0; a< nb-1; a++) cout << pt[a] << ",";
				cout << pt[nb-1] << "]";
			}
					
	};
	
	/*		        
	//Tenter de définir l'indexation de arr par vect ici (après avoir bien défini vect):
		//template<class T>
			template <class T, int N>
			vect<T> arr<T,N>::operator [] (vect<int> pos) { //Même fonction, mais overloadée pour un objet de type vect (plusieurs positions)
				arr<T,pos.nb> gtar;  //Déclarer un arr transitoire
				for(int a=0; a<pos.nb; a++)  gtar.pt[a] =  pt[pos[a]]; //Remplir avec les valeurs dans les bonnes positions
				vect<T> gtvc = gtar; //Créer un objet vect à l'aide de l'arr
				return(gtvc); 
			}*/	
	
			//Ok, si mettons j'essaie de simplement overloader avec une fonction dummy, juste pour voir si j'ACCÈDE au moins à l'overload?
			
	/*		
	//Tenter de définir l'indexation de arr par vect ici (après avoir bien défini vect):
			template <class T, int N>
			void arr<T,N>::operator [] (vect<int> pos) { //Même fonction, mais overloadée pour un objet de type vect (plusieurs positions)
				cout << "hello world"; 
			}		
	*/                                   //Ne marche même pas.  'Pense que je vais laisser tomber.
	
	
//3) Tester
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
	
	test+=(22);
	cout << "\nEt si j'ose une troisième augmentation, avec 22 : " << test[2];	
	
	cout << "\n\nAu total, l'objet ressemble à: "; test.see();
	
	cout << "\n\nOk, là j'vais essayer de créer un nouveau vecteur et d'additionner tout:";
	vect<int> test2;
	test2+=(55);
	cout << "\nTest 2 ressemble maintenant à: "; test2.see();
	cout << "\nEt là j'ajoute le premier objet au deuxième:";
	test2+=test;
	cout << "\n\nEt le deuxième ressemble maintenant à: ";
	test2.see();
	
	cout << "\n\nOk, et si j'essaie d'ajouter un objet arr";
	arr<int,3> testarr = {{4,4,4}};
	test2+=testarr;
	cout << "\nEt maintenant, Test 2 ressemble à:";
	test2.see();
	
	cout << "\n\n Et si j'essaie de voir ce qu'il y a en position [0,2,4] (faire +1 pour comprendre les positions de C++): \n";
	arr<int,3> testget = {{0,2,4}};
	test2[testget].see();
	
	cout << "\n\nEt là, je vais enlever la deuxième position:\n";
	test2.del(1);
	test2.see();
	
	cout << "\n\nEt là, les positions [0,2,3] (faire +1 pour comprendre les positions de C++): \n";
	arr<int,3> testdel = {{0,2,3}};
	test2.del(testdel);
	test2.see();
	
	/*cout << "\n\nMais, disons, si je veux tester l'opérateur [] des arr... Voir ce que [0,2,4] cache en position [0,2]: \n";
	arr<int,2> testget2 = {{0,2}};
	vect<int> testget3 = testget[testget2];
	testget3.see(); */                          //Ne marche pas encore!!!!
	
	cout << "\n\nMais, disons, si je veux tester l'opérateur [] des arr... Voir ce que [0,2,4] cache en position [0,2]: \n";
	arr<int,2> testget2 = {{0,2}};
	vect<int> testget3 = testget[testget2];
	testget3.see();
	
	cout << "\n\nEt... maintenant, encore avec arr[], qu'est-ce que ça donne... avec des doubles? Voir [0.23,0.34,0.45], même positions: \n";
	arr<double,3> testget4 = {{0.23,0.34,0.45}};
	vect<double> testget5 = testget4[testget2];
	testget5.see();	
}	

