/*
///||================================---2018/0i/27---================================||\\\
\\\||================================---Cadre de travail pour histoires interactives---================================||///
*/

//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>
#include <vector>
using namespace std;

//A) Fonction pour repérer des mots
//------------------------------------------------------------------------------------------------------------------------------------------------------
				// x est le mot à repérer,
				// p est la phrase dans laquelle repérer le mot
	
		//ATTENTION: J'aurais aussi très bien pu utiliser la fonction .find, déjà incluse comme membre de la classe string (dans std).
	
		//ATTENTION!!! Pour trouver la longueur des strings, j'utilise .length(), qui calcule la mémoire utilisée.
		//Ça va bien quand j'utilise de simples char, car leur taille est 1 bt. Mais les accents vont probablement pas entrer là-dedans...
				
		//ATTENTION!!! Je pourrais utiliser, au lieu de string comme type, de mettre const string&.
		//Présentement (avec string), le string est copié pour caller la fonction.
		//Avec l'alternative (const string&), seulement une référence (pointeur) est copiée, et "const"	assure que l'objet original n'est pas changé.	

	//Optimisée
	bool lfind(string x, string p)  //Pour "logical find" 
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Créer des compteurs
		int xpos = 0 ; int ppos = 0;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //Évaluer pour la présente lettre, mais en profiter pour passer à la prochaine
			{
				if(xpos==xnchar) return(true); //Si le mot à repérer a été repéré au complet, on arrête la fonction
			} 
			else xpos = 0; //Si ce n'était pas le mot, on retourne à la première lettre
			if(ppos>pnchar) return(false); //Si la phrase est terminée sans avoir trouvé le mot  
		}
	}														
														
	//ii) Position première occurence
	int pfind(string x, string p)  //Pour "position find"
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Créer des compteurs
		int xpos = 0 ; int ppos = 0;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //Évaluer pour la présente lettre, mais en profiter pour passer à la prochaine
			{
				if(xpos==xnchar) return(ppos-xpos); //Si le mot à repérer a été repéré au complet, retourner la position de la première lettre
			} 
			else xpos = 0; //Si ce n'était pas le mot, on retourne à la première lettre
			if(ppos>pnchar) return(-1); //Si la phrase est terminée sans avoir trouvé le mot, retourner -1 (valeur d'erreur choisie ici)  
		}
	}												
	//iii) Position toutes occurences  //Pour "multiple find"
		//Attention: Ici, j'utilise la classe "vector", que je ne maîtrise pas tout à fait
		//ISSSSHHHHHHKKKKK!!! Je n'arrive pas à retourner un array complet! Comment retourner plusieurs valeurs??
				//Il semble que je doive retourner UN SEUL objet, mais d'un type qui me permet de stocker plusieurs informations.
				//How 'bout je crée un objet de type "array" personalisé, qui possède le pointeur + le nombre d'objets contenus?
				//Je pourrais tant qu'à faire simplement créer mon type personalisé genre "vecteur", seulement pour les int.
				//Pour avoir un raccourci à utiliser dans ce code-ci.
	int mfind(string x, string p)
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Créer des compteurs
		int xpos = 0 ; int ppos = 0; int xnb = 0;
		//Créer un vecteur (personalisé) pour contenir chaque occurence
		vect mult;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //Évaluer pour la présente lettre, mais en profiter pour passer à la prochaine
			{
				if(xpos==xnchar) 
				{
				vec.push_back(ppos-xpos); xnb++;  //Si le mot à repérer a été repéré au complet, sauvegarder sa position dans le vecteur
				cout << "\n>À l'assignation: " << ppos-xpos;	
				xpos = 0; //Puisque c'est terminé avec cette itération, on remet le mot à son début
				}	
			} 
			else xpos = 0; //Si ce n'était pas le mot, on retourne à la première lettre
			if(ppos>pnchar) //Si on est rendues à la fin de la phrase, transformer le vecteur en format exportable (array)
			{
				if(xnb!=0)
				{
					//Je devrais: Soit passer l'array + SON NOMBRE D'ÉLÉMENTS en return(),
					//ou bien simplement passer le vecteur (ou tout autre type de classe que je décide de créer à sa place)
					
					int * arr;
					arr = new int [xnb]; //Déclarer l'array (en tant que dynamique, pointé par l'objet arr)
					cout << "\nIl y a " << xnb << " occurences de " << x;
					for(int a=0 ; a<xnb ; a++) 
					{
						arr[a] = vec.at(a) ; 
						cout << "\nDans le vecteur: "<< vec.at(a); cout << "\nDans l'array: "<< arr[a];
					}
					cout << "\nDans la fonction, l'array montre: " << *arr;
					return(*arr);
				}
				else return(-1); //Si la phrase est terminée sans avoir trouvé le mot, retourner -1 (valeur d'erreur choisie ici)  
			}
		}
	}	

//Z) Test, en utilisant la fonction main() ; va être réécrit beaucoup, c'est juste pour voir si tout marche
int main()
{
	string x = "salade" ; string p = "J'aime la Salade.";
	cout << "\n" << x << " est présent dans " << p << " : " << lfind(x,p); 
	cout << "\nDe plus, " << x << " commence à la lettre " << pfind(x,p); 
	string z = "ét" ; string d = "j'étais étonnée et étourdie."; 
	cout << "\nDans " << d << ", " << z << " se trouve aux emplacements " << mfind(z,d);
}

