/*
                ///||================================---2018/0i/27---================================||\\\
\\\||================================---Classe personalisée pour imiter les vecteurs---================================||///
*/

//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>
using namespace std;

//1) Créer une classe d'array permettant une synthaxe facile
class vect; //Déclarer la classe de vecteur pour pouvoir y référer comme friend

template <int N>
class arr 
{
	friend class vect;	//Déclarer vect comme ami de arr, pour que vect puisse avoir accès aux valeurs privées de arr
    static const int nb = N;  //Associer N avec le nombre d'éléments dans l'array; private, pour être sûre
public:
    int pt[N];  //Créer un array fixe (pas dynamique) de la bonne taille; publique, pour pouvoir le changer et le créer facilement
    
};

//2) Créer la classe
	class vect 
	{
	//Valeurs membres	
	public:
		int* pt;  //Créer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'extérieur 
	private:
		int nb;  //Créer le nombre d'objets de l'array comme privé, pour qu'on ne puisse que le changer par += et -=.
	public:
	//Constructeurs	
		vect() {nb=0 ; pt = new int;}  //Créer un constructeur par défaut, pour initialiser tous les paramètres
		vect(int nxt) {nb=1 ; pt = new int [1]; pt[0] = nxt;}  //Créer un constructeur pour créer l'objet avec une seule valeur
	template <int N>
		vect(arr<N> nxt) {nb=nxt.nb ; pt = new int [nxt.nb] ;	for(int a=0; a < nxt.nb; a++) pt[a] = nxt.pt[a];}  //Créer un constructeur pour arr
	//Opérateur +=	
		void operator += (int nxt) { //Changer un opérateur permettant d'ajouter un integer à la suite du vecteur
			int* nwpt = new int [nb+1];  //Déclarer le nouvel array (transitoire)
			for(int a=0; a < nb; a++) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
			nwpt[nb++] = nxt; //Ajouter la nouvelle valeur (en même temps de noter que c'est un objet de plus)
			delete[] pt;  //Éliminer le vieux array trop petit (il semble que si on ne spécifie pas combien d'éléments éliminer entre braquettes, ça élimine tout)
			pt = nwpt;  //Assigner le pointeur à l'array actuel
		}		
		void operator += (const vect& nxt) { //Même fonction, mais overloadée pour ajouter un objet de type vect
			int* nwpt = new int [nb+nxt.nb];  //Déclarer le nouvel array (transitoire)
			for(int a=0; a < nb; a++) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
			for(int a=0; a < nxt.nb; a++) nwpt[a+nb] = nxt.pt[a];  //Ajouter les nouvelles valeurs
			nb+=nxt.nb;  //Noter le nombre de valeurs qu'on ajoute
			delete[] pt;  //Éliminer le vieux array trop petit (il semble que si on ne spécifie pas combien d'éléments éliminer entre braquettes, ça élimine tout)
			pt = nwpt;  //Assigner le pointeur à l'array actuel
		}	
	template <int N>
		void operator += (const arr<N>& nxt) { //Même fonction, mais overloadée pour ajouter un objet de type arr
			int* nwpt = new int [nb+nxt.nb];  //Déclarer le nouvel array (transitoire)
			for(int a=0; a < nb; a++) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
			for(int a=0; a < nxt.nb; a++) nwpt[a+nb] = nxt.pt[a];  //Ajouter les nouvelles valeurs
			nb+=nxt.nb;  //Noter le nombre de valeurs qu'on ajoute
			delete[] pt;  //Éliminer le vieux array trop petit (il semble que si on ne spécifie pas combien d'éléments éliminer entre braquettes, ça élimine tout)
			pt = nwpt;  //Assigner le pointeur à l'array actuel
		}			
	//Opérateur -=	
		void operator -= (int pos) { //Changer un opérateur permettant de supprimer les valeurs à une position spécifique
			int* nwpt = new int [nb-1];  //Déclarer le nouvel array (transitoire)
			int nwpos = 0;  //Déclarer un compteur pour les positions actuelles
			for(int a=0; a < nb; a++) {  //Remplir avec les vieilles valeurs
				if(a==pos) continue;
				nwpt[nwpos++] = pt[a];  //Assigner la valeur, en même temps de passer à la position suivante
			}
			nb--;  //Noter le nombre de valeur qu'on enlève
			delete[] pt;  //Éliminer le viel array
			pt = nwpt;  //Assigner le pointeur à l'array actuel
		}		
		void operator -= (const vect& nxt) { //Même fonction, mais overloadée pour un objet de type vect
			int* nwpt = new int [nb+nxt.nb];  //Déclarer le nouvel array (transitoire)
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
		void operator -= (const arr<N>& nxt)  { //Même fonction, mais overloadée pour ajouter un objet de type arr
			int* nwpt = new int [nb+nxt.nb];  //Déclarer le nouvel array (transitoire)
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
	//Fonctions d'accès	
		int get(int pos) { //Créer une fonction permettant d'aller chercher les valeurs de l'array???
			return(pt[pos]);
		}
		
		int see(void) { //Créer une fonction pour simplement afficher l'array
			cout << "[";
			for(int a=0; a< nb-1; a++) cout << pt[a] << ",";
			cout << pt[nb-1] << "]";
		}
				
};

	
//3) Tester
int main()
{
	cout << "\nFait que là... \n\n\n";
	vect test;
	test+=3;
	cout << "\nSupposé contenir la valeur 3 (avec référence normale): " << test.pt[0];
	cout << "\nSupposé contenir la valeur 3 (avec fonction membre): " << test.get(0);

	test+=44;
	cout << "\nEt là, supposé avoir 44 en deuxième position (avec référence normale) : " << test.pt[1];
	cout << "\nEt là, supposé avoir 44 en deuxième position (avec fonction membre) : " << test.get(1);	
	
	test+=(22);
	cout << "\nEt si j'ose une troisième augmentation, avec 22 : " << test.get(2);	
	
	cout << "\n\nAu total, l'objet ressemble à: ";
	test.see();
	
	cout << "\n\nOk, là j'vais essayer de créer un nouveau vecteur et d'additionner tout:";
	vect test2;
	test2+=(55);
	cout << "\nTout ce qui vient de s'écrire s'est passé dans le deuxième objet.";
	cout << "\nEt là j'ajoute le premier objet au deuxième:";
	test2+=test;
	cout << "\n\nEt le deuxième ressemble maintenant à: ";
	test2.see();
	
	cout << "\n\nOk, et si j'essaie d'ajouter un objet arr";
	arr<3> testarr = {{4,4,4}};
	test2+=testarr;
	cout << "\nEt maintenant, ça ressemble à:";
	test2.see();
	
	cout << "\n\nEt là, je vais enlever la deuxième position:\n";
	test2-=1;
	test2.see();
	
	cout << "\n\nEt là, les positions [0,2,3] (faire +1 pour comprendre les positions en C++): \n";
	arr<3> testenl = {{0,2,3}};
	test2-=testenl;
	test2.see();
	
}	

