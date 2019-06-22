/*
			///||================================---2018/0i/27---================================||\\\
\\\||================================---Fonction find() personnalis�e (strings)---================================||///
*/

//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entr�es/sorties0
using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans sp�cifier ces fonctions proviennent de quel enviro)

# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/classe_vect_maison.cpp"  //Pour les vecteurs maisons


//1) Fonction pour rep�rer des mots
//------------------------------------------------------------------------------------------------------------------------------------------------------
				// x est le mot � rep�rer,
				// p est la phrase dans laquelle rep�rer le mot
	
		//Notes:
		/*      Je n'aurais pas pu utiliser la fonction string::find(), car elle ne trouve que la premi�re occurence,
				et non TOUTES les occurences.
		*/
		
		/*
				Je devrais faire deux versions de la fonction: 
				Une pour la classe vect, et une pour la classe string.
					Au pire, faire un template, et d�river "nb" de chq argument avec un choix if( "is.comme.dans.R()" == "string")...
					Mais je viens de regarder, et on dirait qu'il n'y a pas vraiment de fonctions comme cela d�j� existantes.
					Ce qui pourrait �tre fait, au pire, c'est d'inclure un membre static const string "nom", qui est le nom de la classe.
					Comme �a, �a pourrait permettre de garder les fonctions en template m�me s'il y a de mineures diff�rences entre les arguments.
					Ouin, j'suis mieux d'opter pour �a, une fois que la fonction sera termin�e.  
		*/
		
		/*
				Je devrai �ventuellement mettre les variables en const  & (ex: const string&), pour les appeler par r�f�rence (plus efficace)
		*/
		
	//i) Logical (oui ou non, x est dans p au moins une fois)
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
	vect<int> mfind(string x, string p)
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Cr�er des compteurs
		int xpos = 0 ; int ppos = 0;
		//Cr�er un vecteur (personalis�) pour contenir chaque occurence
		vect<int> mult;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //�valuer pour la pr�sente lettre, mais en profiter pour passer � la prochaine
			{
				if(xpos==xnchar) 
				{
				mult+=(ppos-xpos);  //Si le mot � rep�rer a �t� rep�r� au complet, sauvegarder sa position dans le vecteur
				xpos = 0; //Puisque c'est termin� avec cette it�ration, on remet le mot � son d�but
				}	
			} 
			else xpos = 0; //Si ce n'�tait pas le mot, on retourne � la premi�re lettre
			if(ppos>pnchar) //Si on est rendues � la fin de la phrase, retourner le r�sultat
			{
				if(mult.nb!=0) {return(mult);}
				else return(vect<int> {-1}); //Si la phrase est termin�e sans avoir trouv� le mot, retourner -1 (valeur d'erreur choisie ici)  
			}
		}
	}	

//2) Test
int main()
{
	string x = "salade" ; string p = "J'aime la Salade."; ; string o = "J'aime la salade.";
	cout << "\n" << x << " est present dans " << p << " : " << lfind(x,p); 
	cout << "\n" << x << " est present dans " << o << " : " << lfind(x,o); 	
	cout << "\nDe plus, dans cette derniere phrase, " << x << " commence en position " << pfind(x,o) << " (on veut 10)"; 
	cout << "\nDe plus, dans la premiere phrase, " << x << " commence en position " << pfind(x,p) << " (on veut -1)."; 
	string z = "et" ; string d = "j'etais etonnee et etourdie."; 
	cout << "\nDans " << d << ", " << z << " se trouve aux emplacements "; ~mfind(z,d);
}
