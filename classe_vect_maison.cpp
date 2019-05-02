/*
                ///||================================---2018/0i/27---================================||\\\
\\\||================================---Classe personalis�e pour imiter les vecteurs---================================||///
*/

//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>
using namespace std;

//1) Cr�er une classe d'array permettant une synthaxe facile
class vect; //D�clarer la classe de vecteur pour pouvoir y r�f�rer comme friend

template <int N>
class arr 
{
	friend class vect;	//D�clarer vect comme ami de arr, pour que vect puisse avoir acc�s aux valeurs priv�es de arr
    static const int nb = N;  //Associer N avec le nombre d'�l�ments dans l'array; private, pour �tre s�re
public:
    int pt[N];  //Cr�er un array fixe (pas dynamique) de la bonne taille; publique, pour pouvoir le changer et le cr�er facilement
    
};

//2) Cr�er la classe
	class vect 
	{
	//Valeurs membres	
	public:
		int* pt;  //Cr�er l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'ext�rieur 
	private:
		int nb;  //Cr�er le nombre d'objets de l'array comme priv�, pour qu'on ne puisse que le changer par += et -=.
	public:
	//Constructeurs	
		vect() {nb=0 ; pt = new int;}  //Cr�er un constructeur par d�faut, pour initialiser tous les param�tres
		vect(int nxt) {nb=1 ; pt = new int [1]; pt[0] = nxt;}  //Cr�er un constructeur pour cr�er l'objet avec une seule valeur
	template <int N>
		vect(arr<N> nxt) {nb=nxt.nb ; pt = new int [nxt.nb] ;	for(int a=0; a < nxt.nb; a++) pt[a] = nxt.pt[a];}  //Cr�er un constructeur pour arr
	//Op�rateur +=	
		void operator += (int nxt) { //Changer un op�rateur permettant d'ajouter un integer � la suite du vecteur
			int* nwpt = new int [nb+1];  //D�clarer le nouvel array (transitoire)
			for(int a=0; a < nb; a++) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
			nwpt[nb++] = nxt; //Ajouter la nouvelle valeur (en m�me temps de noter que c'est un objet de plus)
			delete[] pt;  //�liminer le vieux array trop petit (il semble que si on ne sp�cifie pas combien d'�l�ments �liminer entre braquettes, �a �limine tout)
			pt = nwpt;  //Assigner le pointeur � l'array actuel
		}		
		void operator += (const vect& nxt) { //M�me fonction, mais overload�e pour ajouter un objet de type vect
			int* nwpt = new int [nb+nxt.nb];  //D�clarer le nouvel array (transitoire)
			for(int a=0; a < nb; a++) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
			for(int a=0; a < nxt.nb; a++) nwpt[a+nb] = nxt.pt[a];  //Ajouter les nouvelles valeurs
			nb+=nxt.nb;  //Noter le nombre de valeurs qu'on ajoute
			delete[] pt;  //�liminer le vieux array trop petit (il semble que si on ne sp�cifie pas combien d'�l�ments �liminer entre braquettes, �a �limine tout)
			pt = nwpt;  //Assigner le pointeur � l'array actuel
		}	
	template <int N>
		void operator += (const arr<N>& nxt) { //M�me fonction, mais overload�e pour ajouter un objet de type arr
			int* nwpt = new int [nb+nxt.nb];  //D�clarer le nouvel array (transitoire)
			for(int a=0; a < nb; a++) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
			for(int a=0; a < nxt.nb; a++) nwpt[a+nb] = nxt.pt[a];  //Ajouter les nouvelles valeurs
			nb+=nxt.nb;  //Noter le nombre de valeurs qu'on ajoute
			delete[] pt;  //�liminer le vieux array trop petit (il semble que si on ne sp�cifie pas combien d'�l�ments �liminer entre braquettes, �a �limine tout)
			pt = nwpt;  //Assigner le pointeur � l'array actuel
		}			
	//Op�rateur -=	
		void operator -= (int pos) { //Changer un op�rateur permettant de supprimer les valeurs � une position sp�cifique
			int* nwpt = new int [nb-1];  //D�clarer le nouvel array (transitoire)
			int nwpos = 0;  //D�clarer un compteur pour les positions actuelles
			for(int a=0; a < nb; a++) {  //Remplir avec les vieilles valeurs
				if(a==pos) continue;
				nwpt[nwpos++] = pt[a];  //Assigner la valeur, en m�me temps de passer � la position suivante
			}
			nb--;  //Noter le nombre de valeur qu'on enl�ve
			delete[] pt;  //�liminer le viel array
			pt = nwpt;  //Assigner le pointeur � l'array actuel
		}		
		void operator -= (const vect& nxt) { //M�me fonction, mais overload�e pour un objet de type vect
			int* nwpt = new int [nb+nxt.nb];  //D�clarer le nouvel array (transitoire)
			int nwpos = 0;  //D�clarer un compteur pour les positions actuelles
			bool skip;  //D�clarer un compteur pour les positions � retirer
			for(int a=0; a < nb; a++) {  //Remplir avec les vieilles valeurs
				skip = false;
				for(int b=0; b < nxt.nb; b++) if(a==nxt.pt[b]) {skip = true; break;}
				if(skip) continue;
				nwpt[nwpos++] = pt[a];  //Assigner la valeur, en m�me temps de passer � la position suivante				
			}
			nb-=nxt.nb;  //Noter le nombre de valeurs qu'on enl�ve
			delete[] pt;  //�liminer le viel array
			pt = nwpt;  //Assigner le pointeur � l'array actuel
		}	
	template <int N>
		void operator -= (const arr<N>& nxt)  { //M�me fonction, mais overload�e pour ajouter un objet de type arr
			int* nwpt = new int [nb+nxt.nb];  //D�clarer le nouvel array (transitoire)
			int nwpos = 0;  //D�clarer un compteur pour les positions actuelles
			bool skip;  //D�clarer un compteur pour les positions � retirer
			for(int a=0; a < nb; a++) {   //Remplir avec les vieilles valeurs
				skip = false;
				for(int b=0; b < nxt.nb; b++) if(a==nxt.pt[b]) {skip = true; break;}
				if(skip) continue;
				nwpt[nwpos++] = pt[a];  //Assigner la valeur, en m�me temps de passer � la position suivante				
			}
			nb-=nxt.nb;  //Noter le nombre de valeurs qu'on enl�ve
			delete[] pt;  //�liminer le viel array
			pt = nwpt;  //Assigner le pointeur � l'array actuel
		}	
	//Fonctions d'acc�s	
		int get(int pos) { //Cr�er une fonction permettant d'aller chercher les valeurs de l'array???
			return(pt[pos]);
		}
		
		int see(void) { //Cr�er une fonction pour simplement afficher l'array
			cout << "[";
			for(int a=0; a< nb-1; a++) cout << pt[a] << ",";
			cout << pt[nb-1] << "]";
		}
				
};

	
//3) Tester
int main()
{
	cout << "\nFait que l�... \n\n\n";
	vect test;
	test+=3;
	cout << "\nSuppos� contenir la valeur 3 (avec r�f�rence normale): " << test.pt[0];
	cout << "\nSuppos� contenir la valeur 3 (avec fonction membre): " << test.get(0);

	test+=44;
	cout << "\nEt l�, suppos� avoir 44 en deuxi�me position (avec r�f�rence normale) : " << test.pt[1];
	cout << "\nEt l�, suppos� avoir 44 en deuxi�me position (avec fonction membre) : " << test.get(1);	
	
	test+=(22);
	cout << "\nEt si j'ose une troisi�me augmentation, avec 22 : " << test.get(2);	
	
	cout << "\n\nAu total, l'objet ressemble �: ";
	test.see();
	
	cout << "\n\nOk, l� j'vais essayer de cr�er un nouveau vecteur et d'additionner tout:";
	vect test2;
	test2+=(55);
	cout << "\nTout ce qui vient de s'�crire s'est pass� dans le deuxi�me objet.";
	cout << "\nEt l� j'ajoute le premier objet au deuxi�me:";
	test2+=test;
	cout << "\n\nEt le deuxi�me ressemble maintenant �: ";
	test2.see();
	
	cout << "\n\nOk, et si j'essaie d'ajouter un objet arr";
	arr<3> testarr = {{4,4,4}};
	test2+=testarr;
	cout << "\nEt maintenant, �a ressemble �:";
	test2.see();
	
	cout << "\n\nEt l�, je vais enlever la deuxi�me position:\n";
	test2-=1;
	test2.see();
	
	cout << "\n\nEt l�, les positions [0,2,3] (faire +1 pour comprendre les positions en C++): \n";
	arr<3> testenl = {{0,2,3}};
	test2-=testenl;
	test2.see();
	
}	

