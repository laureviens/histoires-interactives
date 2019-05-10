/*
                ///||================================---2018/0i/27---================================||\\\
\\\||================================---Classe personalis�e pour imiter les vecteurs---================================||///
*/

/*
		#### Serait pertinent d'avoir une synthaxe plus claire quant aux op�rateurs.
		Id�alement, avoir += pour ajouter des affaires � la suite.
		
		Mais apr�s, comment on le diff�rentie des op�rations qui enl�ve les entr�es dans des positions pr�cises?
		
		�galement, il serait charmant d'avoir des op�rations de simple addition num�rique; 
			+ et - et * et /, avec les vecteurs num�riques (de int ou double).
					Mais c'est quand m�me tr�s optionnel. Juste logique + souhaitable. Mais pas n�cessaire.
		
		
		#### Aussi, serait bien d'overloader la fonction get() pour des vecteurs ou des arr?
				Mais, hum, je viens de me rappeler. Return ne peut que retourner un seul objet.
				Faudrait alors retourner un nouvel objet de type vect. Ce qui serait tr�s possible.
				
		#### Finalement, il faudrait �galement �largir cette classe � des entr�es autres que des integers.
		     Genre les doubles, qui ne devraient pas causer de probl�mes.
		     Surtout les characters, probablement du type wchar_t. Pour que ce soit en unicode.
			 		#### Dans le fond, si je me fie � mon prototype pour afficher des phrases avec accents,
					     tout pourrait se passer seulement dans la fonction qui affiche, pas dans l'entreposage.
						 Donc je n'aurais qu'� trouver des mani�res rapides de convertir des strings (normales)
						 en classe de type "arr" ou "vect" (qui contiennent "naturellement" le nombre de caract�res).
						 
						 En m�me temps, l'utilisation de caract�res sp�ciaux du type \n rend le tout probl�matique,
						 car ils ne compteraient pas pour un seul caract�re.   ##2019-05-10: En fait, oui. Voir le test.
						 Je pourrais toujours utiliser un caract�re genre � ou �, ou � ou � pour sauter une ligne.
						 Et en prendre un autre pour faire des caract�res "transparents".
						 
						 Pour utiliser le raccourci "string", je suis oblig�e, je crois, d'employer la fonction membre "length". Ou l'objet "size_t".
						 Mais �a ne donne pas le nombre de caract�res contenus dans l'objet, mais la taille totale de l'objet.
						 Donc ne fonctionne pas.
						 Donc... Faudrait essayer de copier cette synthaxe facile dans un objet custom (genre "arr")?
						 
						 Officiellement, ici, https://en.cppreference.com/w/cpp/language/user_literal, �a dit qu'on peut le faire!
						 On peut overloader un "" string litteral operator?
						 
						 ##2019-05-10: J'ai test� la fonction "length" des strings, et elle semble fonctionner comme je l'entends.
						 	Au pire, je peux toujours d�buter en mettant des strings en entr�e, � la fois aux arr et aux vect, 
						 	et modifier par la suite en cr�ant des syntaxes maison avec l'overload de string litteral operator,
						 	si je rencontre des probl�mes avec les strings.
						 	
						 
		#### Voir http://www.cplusplus.com/reference/string/string/, qui donne toutes les fonctions membres de "string",
		     ce qui donne des belles id�es sur les op�rateurs utiles � inclure.				 	
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
		friend class vect<T>;	//D�clarer vect comme ami de arr, pour que vect puisse avoir acc�s aux valeurs priv�es de arr
	    static const int nb = N;  //Associer N avec le nombre d'�l�ments dans l'array; private, pour �tre s�re
	public:
	    T pt[N];  //Cr�er un array fixe (pas dynamique) de la bonne taille; publique, pour pouvoir le changer et le cr�er facilement
	    
	};
	
	//2) Cr�er la classe
	template <class T> //Cr�er un "template" de type, qui pourra �tre des int, des char... ce que je veux! 
		class vect
		{
		//Valeurs membres	
		public:
			T* pt;  //Cr�er l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'ext�rieur 
		private:
			int nb;  //Cr�er le nombre d'objets de l'array comme priv�, pour qu'on ne puisse que le changer par += et -=.
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
		//Fonction de modification: supprimer des positions	
			void del (int pos) { //Fonction permettant de supprimer les valeurs � une position sp�cifique
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
			void del (const vect<int>& nxt) { //M�me fonction, mais overload�e pour un objet de type vect
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
			void del (const arr<T,N>& nxt)  { //M�me fonction, mais overload�e pour ajouter un objet de type arr
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
		//Fonctions d'acc�s	: retourner la longueur du vecteur
			int count(void) {  //Cr�er une fonction permettant d'aller chercher la longueur de l'array
				return(nb);
			}
			
		//Fonctions d'acc�s	: retourner le vecteur
			int get(int pos) { //Cr�er une fonction permettant d'aller chercher une valeur de l'array (une seule position)
				return(pt[pos]);
			}
			
			vect get(vect<int> pos) { //M�me fonction, mais overload�e pour un objet de type vect (plusieurs positions)
				T* gtpt = new T [pos.nb];  //D�clarer un array transitoire
				for(int a=0; a<pos.nb; a++)  gtpt[a] =  pt[pos.get(a)]; //Remplir avec les valeurs dans les bonnes positions
				return(gtpt); 
			}
		template <int N>
			arr<T,N> get(arr<int,N> pos) { //M�me fonction, mais overload�e pour un objet de type arr (plusieurs positions)
				T* gtpt = new T [pos.nb];  //D�clarer un array transitoire
				for(int a=0; a<pos.nb; a++)  gtpt[a] =  pt[pos[a]]; //Remplir avec les valeurs dans les bonnes positions
				return(gtpt); 
			}			
			
		//Fonctions d'acc�s	: afficher le vecteur			
			void see(void) { //Cr�er une fonction pour simplement afficher l'array
				cout << "[";
				for(int a=0; a< nb-1; a++) cout << pt[a] << ",";
				cout << pt[nb-1] << "]";
			}
					
	};

	
//3) Tester
int main()
{
	cout << "\nFait que l�... \n\n\n";
	vect<int> test;
	test+=3;
	cout << "\nSuppos� contenir la valeur 3 (avec r�f�rence normale): " << test.pt[0];
	cout << "\nSuppos� contenir la valeur 3 (avec fonction membre): " << test.get(0);

	test+=44;
	cout << "\nEt l�, suppos� avoir 44 en deuxi�me position (avec r�f�rence normale) : " << test.pt[1];
	cout << "\nEt l�, suppos� avoir 44 en deuxi�me position (avec fonction membre) : " << test.get(1);	
	
	test+=(22);
	cout << "\nEt si j'ose une troisi�me augmentation, avec 22 : " << test.get(2);	
	
	cout << "\n\nAu total, l'objet ressemble �: "; test.see();
	
	cout << "\n\nOk, l� j'vais essayer de cr�er un nouveau vecteur et d'additionner tout:";
	vect<int> test2;
	test2+=(55);
	cout << "\nTest 2 ressemble maintenant �: "; test2.see();
	cout << "\nEt l� j'ajoute le premier objet au deuxi�me:";
	test2+=test;
	cout << "\n\nEt le deuxi�me ressemble maintenant �: ";
	test2.see();
	
	cout << "\n\nOk, et si j'essaie d'ajouter un objet arr";
	arr<int,3> testarr = {{4,4,4}};
	test2+=testarr;
	cout << "\nEt maintenant, Test 2 ressemble �:";
	test2.see();
	
	cout << "\n\nEt l�, je vais enlever la deuxi�me position:\n";
	test2.del(1);
	test2.see();
	
	cout << "\n\nEt l�, les positions [0,2,3] (faire +1 pour comprendre les positions en C++): \n";
	arr<int,3> testenl = {{0,2,3}};
	test2.del(testenl);
	test2.see();
	
}	

