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


//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>
using namespace std;


//1) Cr�er une classe d'array permettant une synthaxe facile

template <class T> //Cr�er un "template" de type, qui pourra �tre des int, des char... ce que je veux! 
	
	class vect; //D�clarer la classe de vecteur pour pouvoir y r�f�rer comme friend
	
	template <class T, int N>
	class arr 
		{
		//Valeurs membres	
		public:
	    	static const int nb = N;  //D�clarer le nombre d'�l�ments dans l'array comme N
		    T pt[nb];  //D�clarer un array fixe (pas dynamique) de la bonne taille; publique, pour pouvoir le changer et le cr�er facilement
		//Fonctions d'acc�s	: retourner certains positions (Op�rateur [])
			int operator [] (int pos) { //Cr�er une fonction permettant d'aller chercher une valeur de l'array (une seule position)
				return(pt[pos]);
			}			
			template<int M>            //Cr�er un nouveau template, pour que N et M diff�rent (habituellement, M<N)
			vect<T> operator [] (arr<int,M> pos) { //M�me fonction, mais overload�e pour un objet de type arr (plusieurs positions)
				arr<T,pos.nb> indx;  //D�clarer un arr transitoire
				for(int a=0; a<pos.nb; a++)  indx.pt[a] =  pt[pos[a]]; //Remplir avec les valeurs dans les bonnes positions
				vect<T> gtvc = indx; //Cr�er un objet vect � l'aide de l'arr
				return(gtvc);
			}
			vect<T> operator [] (vect<int> pos) ;  //M�me fonction, mais overload�e pour un objet de type vect (plusieurs positions)
					//La d�finition de cet op�rateur vient apr�s la d�finition des comportements de vect
	};
	
//2) Cr�er la classe
	template <class T> //Cr�er un "template" de type, qui pourra �tre des int, des char... ce que je veux! 
		class vect
		{
		//Valeurs membres	
		public:
			T* pt;  //D�clarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'ext�rieur 
		private:
			int nb;  //D�clarer le nombre d'objets de l'array comme priv�, pour qu'on ne puisse que le changer par += et -=.
		public:
		//Constructeurs	
			vect<T>() {nb=0 ; pt = new T;}  //Cr�er un constructeur par d�faut, pour initialiser tous les param�tres
			vect<T>(int nxt) {nb=1 ; pt = new T [1]; pt[0] = nxt;}  //Cr�er un constructeur pour cr�er l'objet avec une seule valeur
		template <int N>
			vect(arr<T,N> nxt) {nb=nxt.nb ; pt = new T [nxt.nb] ;	for(int a=0; a < nxt.nb; a++) pt[a] = nxt.pt[a];}  //Cr�er un constructeur pour arr
		//Fonction de modification : ajouter des �l�ments � la suite (Op�rateur +=)	
			void operator += (T nxt) { //Changer un op�rateur permettant d'ajouter un integer � la suite du vecteur
				T* nwpt = new T [nb+1];  //D�clarer le nouvel array (transitoire)
				for(int a=0; a < nb; a++) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
				nwpt[nb++] = nxt; //Ajouter la nouvelle valeur (en m�me temps de noter que c'est un objet de plus)
				delete[] pt;  //�liminer le vieux array trop petit (il semble que si on ne sp�cifie pas combien d'�l�ments �liminer entre braquettes, �a �limine tout)
				pt = nwpt;  //Assigner le pointeur � l'array actuel
			}		
			void operator += (const vect& nxt) { //M�me fonction, mais overload�e pour ajouter un objet de type vect
				T* nwpt = new T [nb+nxt.nb];  //D�clarer le nouvel array (transitoire)
				for(int a=0; a < nb; a++) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
				for(int a=0; a < nxt.nb; a++) nwpt[a+nb] = nxt.pt[a];  //Ajouter les nouvelles valeurs
				nb+=nxt.nb;  //Noter le nombre de valeurs qu'on ajoute
				delete[] pt;  //�liminer le vieux array trop petit (il semble que si on ne sp�cifie pas combien d'�l�ments �liminer entre braquettes, �a �limine tout)
				pt = nwpt;  //Assigner le pointeur � l'array actuel
			}	
		template <int N>
			void operator += (const arr<T,N>& nxt) { //M�me fonction, mais overload�e pour ajouter un objet de type arr
				T* nwpt = new T [nb+nxt.nb];  //D�clarer le nouvel array (transitoire)
				for(int a=0; a < nb; a++) nwpt[a] = pt[a];  //Remplir avec les vieilles valeurs
				for(int a=0; a < nxt.nb; a++) nwpt[a+nb] = nxt.pt[a];  //Ajouter les nouvelles valeurs
				nb+=nxt.nb;  //Noter le nombre de valeurs qu'on ajoute
				delete[] pt;  //�liminer le vieux array trop petit (il semble que si on ne sp�cifie pas combien d'�l�ments �liminer entre braquettes, �a �limine tout)
				pt = nwpt;  //Assigner le pointeur � l'array actuel
			}			
		//Fonction de modification: supprimer des positions	(op�rateur -)
			void operator - (int pos) { //Fonction permettant de supprimer les valeurs � une position sp�cifique
				T* nwpt = new T [nb-1];  //D�clarer le nouvel array (transitoire)
				int nwpos = 0;  //D�clarer un compteur pour les positions actuelles
				for(int a=0; a < nb; a++) {  //Remplir avec les vieilles valeurs
					if(a==pos) continue;
					nwpt[nwpos++] = pt[a];  //Assigner la valeur, en m�me temps de passer � la position suivante
				}
				nb--;  //Noter le nombre de valeur qu'on enl�ve
				delete[] pt;  //�liminer le viel array
				pt = nwpt;  //Assigner le pointeur � l'array actuel
			}		
			void operator - (const vect<int>& nxt) { //M�me fonction, mais overload�e pour un objet de type vect
				T* nwpt = new T [nb+nxt.nb];  //D�clarer le nouvel array (transitoire)
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
			void operator - (const arr<T,N>& nxt)  { //M�me fonction, mais overload�e pour ajouter un objet de type arr
				T* nwpt = new T [nb+nxt.nb];  //D�clarer le nouvel array (transitoire)
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
		//Fonctions d'acc�s	: retourner certains positions (Op�rateur [])
			int operator [] (int pos) { //Cr�er une fonction permettant d'aller chercher une valeur de l'array (une seule position)
				return(pt[pos]);
			}
			vect<T> operator [] (vect<int> pos) { //M�me fonction, mais overload�e pour un objet de type vect (plusieurs positions)
				arr<T,pos.nb> indx;  //D�clarer un arr transitoire
				for(int a=0; a<pos.nb; a++)  indx.pt[a] =  pt[pos[a]]; //Remplir avec les valeurs dans les bonnes positions
				vect<T> gtvc = indx; //Cr�er un objet vect � l'aide de l'arr
				return(gtvc); 
			}
		template <int N>
			vect<T> operator [] (arr<int,N> pos) { //M�me fonction, mais overload�e pour un objet de type arr (plusieurs positions)
				arr<T,pos.nb> indx;  //D�clarer un arr transitoire
				for(int a=0; a<pos.nb; a++)  indx.pt[a] =  pt[pos[a]]; //Remplir avec les valeurs dans les bonnes positions
				vect<T> gtvc = indx; //Cr�er un objet vect � l'aide de l'arr
				return(gtvc);
			}
		//Fonctions d'acc�s	: afficher le vecteur en entier (Op�rateur ~)
								//Attention! L'op�rateur ~ doit �tre plac� au-devant de l'objet vect!			
			void operator ~ (void) { //Cr�er une fonction pour simplement afficher l'array
				cout << "[";
				for(int a=0; a< nb-1; a++) cout << pt[a] << ",";
				cout << pt[nb-1] << "]";
			}
					
	};
	
	/*
	//D�finir l'indexation de arr par vect apr�s la d�finition de vect
		template <class T, int N>
		vect<T> arr<T,N>::operator [] (vect<int> pos) { //Indexation par [], pour obtenir les valeurs dans des positions sp�cifiques
			arr<T,pos.nb> gtar;  //D�clarer un arr transitoire
			for(int a=0; a<pos.count(); a++)  gtar.pt[a] =  pt[pos[a]]; //Remplir avec les valeurs dans les bonnes positions
			vect<T> gtvc = gtar; //Cr�er un objet vect � l'aide de l'arr
			return(gtvc); 
		}	
	*/                      //Ne fonctionne pas, car l'argument pos.nb, pass� comme "N", est priv� (et pas une constante, par-dessus le march�)
	
	
//3) Tester
int main()
{
	cout << "\nFait que l�... \n\n\n";
	vect<int> test;
	test+=3;
	cout << "\nSuppos� contenir la valeur 3 (avec r�f�rence normale): " << test.pt[0];
	cout << "\nSuppos� contenir la valeur 3 (avec fonction membre): " << test[0];

	test+=44;
	cout << "\nEt l�, suppos� avoir 44 en deuxi�me position (avec r�f�rence normale) : " << test.pt[1];
	cout << "\nEt l�, suppos� avoir 44 en deuxi�me position (avec fonction membre) : " << test[1];	
	
	test+=(22);
	cout << "\nEt si j'ose une troisi�me augmentation, avec 22 : " << test[2];	
	
	cout << "\n\nAu total, l'objet ressemble �: "; ~test;
	
	cout << "\n\nOk, l� j'vais essayer de cr�er un nouveau vecteur et d'additionner tout:";
	vect<int> test2;
	test2+=(55);
	cout << "\nTest 2 ressemble maintenant �: "; ~test2;
	cout << "\nEt l� j'ajoute le premier objet au deuxi�me:";
	test2+=test;
	cout << "\n\nEt le deuxi�me ressemble maintenant �: ";
	~test2;
	
	cout << "\n\nOk, et si j'essaie d'ajouter un objet arr";
	arr<int,3> testarr = {{4,4,4}};
	test2+=testarr;
	cout << "\nEt maintenant, Test 2 ressemble �:";
	~test2;
	
	cout << "\n\n Et si j'essaie de voir ce qu'il y a en position [0,2,4] (faire +1 pour comprendre les positions de C++): \n";
	arr<int,3> testget = {{0,2,4}};
	~test2[testget];
	
	cout << "\n\nEt l�, je vais enlever la deuxi�me position:\n";
	test2-1;
	~test2;
	
	cout << "\n\nEt l�, les positions [0,2,3] (faire +1 pour comprendre les positions de C++): \n";
	arr<int,3> testdel = {{0,2,3}};
	test2-testdel;
	~test2;
	
	cout << "\n\nMais, disons, si je veux tester l'op�rateur [] des arr... Voir ce que [0,2,4] cache en position [0,2]: \n";
	arr<int,2> testget2 = {{0,2}};
	vect<int> testget3 = testget[testget2];
	~testget3;
	
	cout << "\n\nEt... maintenant, encore avec arr[], qu'est-ce que �a donne... avec des doubles? Voir [0.23,0.34,0.45], m�me positions: \n";
	arr<double,3> testget4 = {{0.23,0.34,0.45}};
	vect<double> testget5 = testget4[testget2];
	~testget5;	
}	

