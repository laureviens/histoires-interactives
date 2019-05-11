/*
///||================================---2018/0i/27---================================||\\\
\\\||================================---Cadre de travail pour histoires interactives---================================||///
*/

//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>
#include <vector>
using namespace std;

//A) Fonction pour rep�rer des mots
//------------------------------------------------------------------------------------------------------------------------------------------------------
				// x est le mot � rep�rer,
				// p est la phrase dans laquelle rep�rer le mot
	
		//ATTENTION: J'aurais aussi tr�s bien pu utiliser la fonction .find, d�j� incluse comme membre de la classe string (dans std).
	
		//ATTENTION!!! Pour trouver la longueur des strings, j'utilise .length(), qui calcule la m�moire utilis�e.
		//�a va bien quand j'utilise de simples char, car leur taille est 1 bt. Mais les accents vont probablement pas entrer l�-dedans...
				
		//ATTENTION!!! Je pourrais utiliser, au lieu de string comme type, de mettre const string&.
		//Pr�sentement (avec string), le string est copi� pour caller la fonction.
		//Avec l'alternative (const string&), seulement une r�f�rence (pointeur) est copi�e, et "const"	assure que l'objet original n'est pas chang�.	

	//Optimis�e
	bool lfind(string x, string p)  //Pour "logical find" 
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Cr�er des compteurs
		int xpos = 0 ; int ppos = 0;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //�valuer pour la pr�sente lettre, mais en profiter pour passer � la prochaine
			{
				if(xpos==xnchar) return(true); //Si le mot � rep�rer a �t� rep�r� au complet, on arr�te la fonction
			} 
			else xpos = 0; //Si ce n'�tait pas le mot, on retourne � la premi�re lettre
			if(ppos>pnchar) return(false); //Si la phrase est termin�e sans avoir trouv� le mot  
		}
	}														
														
	//ii) Position premi�re occurence
	int pfind(string x, string p)  //Pour "position find"
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Cr�er des compteurs
		int xpos = 0 ; int ppos = 0;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //�valuer pour la pr�sente lettre, mais en profiter pour passer � la prochaine
			{
				if(xpos==xnchar) return(ppos-xpos); //Si le mot � rep�rer a �t� rep�r� au complet, retourner la position de la premi�re lettre
			} 
			else xpos = 0; //Si ce n'�tait pas le mot, on retourne � la premi�re lettre
			if(ppos>pnchar) return(-1); //Si la phrase est termin�e sans avoir trouv� le mot, retourner -1 (valeur d'erreur choisie ici)  
		}
	}												
	//iii) Position toutes occurences  //Pour "multiple find"
		//Attention: Ici, j'utilise la classe "vector", que je ne ma�trise pas tout � fait
		//ISSSSHHHHHHKKKKK!!! Je n'arrive pas � retourner un array complet! Comment retourner plusieurs valeurs??
				//Il semble que je doive retourner UN SEUL objet, mais d'un type qui me permet de stocker plusieurs informations.
				//How 'bout je cr�e un objet de type "array" personalis�, qui poss�de le pointeur + le nombre d'objets contenus?
				//Je pourrais tant qu'� faire simplement cr�er mon type personalis� genre "vecteur", seulement pour les int.
				//Pour avoir un raccourci � utiliser dans ce code-ci.
	int mfind(string x, string p)
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Cr�er des compteurs
		int xpos = 0 ; int ppos = 0; int xnb = 0;
		//Cr�er un vecteur (personalis�) pour contenir chaque occurence
		vect mult;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //�valuer pour la pr�sente lettre, mais en profiter pour passer � la prochaine
			{
				if(xpos==xnchar) 
				{
				vec.push_back(ppos-xpos); xnb++;  //Si le mot � rep�rer a �t� rep�r� au complet, sauvegarder sa position dans le vecteur
				cout << "\n>� l'assignation: " << ppos-xpos;	
				xpos = 0; //Puisque c'est termin� avec cette it�ration, on remet le mot � son d�but
				}	
			} 
			else xpos = 0; //Si ce n'�tait pas le mot, on retourne � la premi�re lettre
			if(ppos>pnchar) //Si on est rendues � la fin de la phrase, transformer le vecteur en format exportable (array)
			{
				if(xnb!=0)
				{
					//Je devrais: Soit passer l'array + SON NOMBRE D'�L�MENTS en return(),
					//ou bien simplement passer le vecteur (ou tout autre type de classe que je d�cide de cr�er � sa place)
					
					int * arr;
					arr = new int [xnb]; //D�clarer l'array (en tant que dynamique, point� par l'objet arr)
					cout << "\nIl y a " << xnb << " occurences de " << x;
					for(int a=0 ; a<xnb ; a++) 
					{
						arr[a] = vec.at(a) ; 
						cout << "\nDans le vecteur: "<< vec.at(a); cout << "\nDans l'array: "<< arr[a];
					}
					cout << "\nDans la fonction, l'array montre: " << *arr;
					return(*arr);
				}
				else return(-1); //Si la phrase est termin�e sans avoir trouv� le mot, retourner -1 (valeur d'erreur choisie ici)  
			}
		}
	}	

//Z) Test, en utilisant la fonction main() ; va �tre r��crit beaucoup, c'est juste pour voir si tout marche
int main()
{
	string x = "salade" ; string p = "J'aime la Salade.";
	cout << "\n" << x << " est pr�sent dans " << p << " : " << lfind(x,p); 
	cout << "\nDe plus, " << x << " commence � la lettre " << pfind(x,p); 
	string z = "�t" ; string d = "j'�tais �tonn�e et �tourdie."; 
	cout << "\nDans " << d << ", " << z << " se trouve aux emplacements " << mfind(z,d);
}

