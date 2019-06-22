/*
			///||================================---2018/0i/27---================================||\\\
\\\||================================---Fonction find() personnalisée (strings)---================================||///
*/

//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entrées/sorties0
using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)

# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/classe_vect_maison.cpp"  //Pour les vecteurs maisons


//1) Fonction pour repérer des mots
//------------------------------------------------------------------------------------------------------------------------------------------------------
				// x est le mot à repérer,
				// p est la phrase dans laquelle repérer le mot
	
		//Notes:
		/*      Je n'aurais pas pu utiliser la fonction string::find(), car elle ne trouve que la première occurence,
				et non TOUTES les occurences.
		*/
		
		/*
				Je devrais faire deux versions de la fonction: 
				Une pour la classe vect, et une pour la classe string.
					Au pire, faire un template, et dériver "nb" de chq argument avec un choix if( "is.comme.dans.R()" == "string")...
					Mais je viens de regarder, et on dirait qu'il n'y a pas vraiment de fonctions comme cela déjà existantes.
					Ce qui pourrait être fait, au pire, c'est d'inclure un membre static const string "nom", qui est le nom de la classe.
					Comme ça, ça pourrait permettre de garder les fonctions en template même s'il y a de mineures différences entre les arguments.
					Ouin, j'suis mieux d'opter pour ça, une fois que la fonction sera terminée.  
		*/
		
		/*
				Je devrai éventuellement mettre les variables en const  & (ex: const string&), pour les appeler par référence (plus efficace)
		*/
		
	//i) Logical (oui ou non, x est dans p au moins une fois)
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
	vect<int> mfind(string x, string p)
	{
		//Trouver la longueur de chaque variable
		int xnchar = x.length() ; int pnchar =  p.length();
		//Créer des compteurs
		int xpos = 0 ; int ppos = 0;
		//Créer un vecteur (personalisé) pour contenir chaque occurence
		vect<int> mult;
		while(true)
		{
			if(x[xpos++]==p[ppos++]) //Évaluer pour la présente lettre, mais en profiter pour passer à la prochaine
			{
				if(xpos==xnchar) 
				{
				mult+=(ppos-xpos);  //Si le mot à repérer a été repéré au complet, sauvegarder sa position dans le vecteur
				xpos = 0; //Puisque c'est terminé avec cette itération, on remet le mot à son début
				}	
			} 
			else xpos = 0; //Si ce n'était pas le mot, on retourne à la première lettre
			if(ppos>pnchar) //Si on est rendues à la fin de la phrase, retourner le résultat
			{
				if(mult.nb!=0) {return(mult);}
				else return(vect<int> {-1}); //Si la phrase est terminée sans avoir trouvé le mot, retourner -1 (valeur d'erreur choisie ici)  
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
