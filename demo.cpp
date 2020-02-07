/*
			///||================================---2020/01/18---================================||\\\
\\\||================================---Tutoriel / Démo du potentiel interactif / narratif---================================||///
*/


# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/cadre_fonctionnel_global.cpp"


//-----------------------------------------------------------------|                         |--------------------------------------------------------------------------------\\

int main(void) {

	//Changement de taille et de place de la console                     //Doit être défini à l'intérieur du main() pour fonctionner!
	//x, y, width, height,
	fen base(600,30,500,500);                                           //Crée également l'objet dans lequel ces paramètres sont définis       
	memoire mem(base.limtxtx);

	//Créer l'objet où tout est initié
	univers monde;

//-----------------------------------------------------------------|      Bibliothèque       |--------------------------------------------------------------------------------\\
	
	nvrayon(monde,"intro");
		nvlivre(monde,"desuet");	
		nvlivre(monde,"jeprem");
		nvlivre(monde,"jedeux");
		nvlivre(monde,"saraprem");
		nvlivre(monde,"saradeux");
		nvlivre(monde,"jetrois");
		nvlivre(monde,"saratrois");
		nvlivre(monde,"jequatre");
		nvlivre(monde,"saraquatre");
		
			
			
//-----------------------------------------------------------------|          Début          |--------------------------------------------------------------------------------\\

	//Créer un canal
	nvcanal(monde,"je"); canaldelai(monde,80); 
	nvcanal(monde,"sara"); canaldelai(monde,130); canalalinea(monde,6);
		
	//Débuter un chapitre
	nvchapt(monde);
		ccond(monde,"!intro¶desuet");        //Rendre le premier chapitre accessible seulement quand c'est l'intro 

			//Juste le début
			nvauto(monde); acanal(monde,"je");	                                    	
			acond(monde,"!intro¶jeprem");	
			adeb(monde,"§bintro¶jeprem=1§");
			afin(monde,"§bintro¶saraprem=1§");
			aover(monde,0);						//N'override pas le canal à son début
			atexte(monde,"T'as froid aux joues.§p1400§"
			"\n§d0§                     §d80§Pis aux cuisses.");				

			//La réponse de Sara
			nvauto(monde); acanal(monde,"sara");		
			acond(monde,"intro¶saraprem");	
			adeb(monde,"§bintro¶saraprem=0§");
			afin(monde,"§bintro¶jedeux=1§");
			atexte(monde,"§p1800§\"Come on,§p1100§"
			"\n§d0§          §d130§on est presqu'arrivées!\"");

			//La suite
			nvauto(monde); acanal(monde,"je");		
			acond(monde,"intro¶jedeux");	
			adeb(monde,"§bintro¶jedeux=0§§s§");
			afin(monde,"§bintro¶saradeux=1§");
			atexte(monde,"§p400§\n\n         T'accélères le pas,§p600§ moins pour la rejoindre§p100§ que pour réchauffer tes jambes.§p1200§§d110§ Le vent,§p500§ criss.§p1000§ Le vent.§p2000§"
			"\n  Fait frette.§p2200§"
			"\n§d90§Tu lèves les yeux§p100§ juste à la limite de ton capuchon§p300§ pis Sara est quand même loin en avant.§p1400§§d80§ Tu te presses un peu plus.§p2800§"
			"\n\nTraverses une rue,§p400§ t'es au coin de la cathédrale§p300§ pis le vent charge de plus belle depuis ta droite.§p2400§ Caliss.§p3000§§d90§ Sara est déjà rendue plus bas,§p500§ a'longe la grosse chapelle.§p2300§"
			"\n§d0§                       §d80§Tu descends au jogging§p120§, §p400§"
			"\n§d0§                                                §d80§rejoindre au plus vite l'énorme pare-vent de pierre.§p1800§"
			"\nTa jupe virevolte sur tes genoux,§p200§ expose tes cuisses aux rafales;§p2300§ Pas l'meilleur choix de vêtements.§p4300§"
			"\n\n     La cathédrale coupe le vent§p150§ pour vrai.§3100§ "
			"\n\n\nSara t'as un peu attendue et te sourit avec son trop d'excitation.§p2200§");

			//La réponse de Sara
			nvauto(monde); acanal(monde,"sara");		
			acond(monde,"intro¶saradeux");	
			adeb(monde,"§bintro¶saradeux=0§§s§");
			afin(monde,"§bintro¶jetrois=1§");
			atexte(monde,"§p130§§d110§\n\"J'te jure,§p260§ ça vaut vraiment la peine!\"");			

			//La suite
			nvauto(monde); acanal(monde,"je");		
			acond(monde,"intro¶jetrois");	
			adeb(monde,"§bintro¶jetrois=0§§s§");
			afin(monde,"§bintro¶saratrois=1§");
			atexte(monde,"§p3100§Tu peux pas empêcher tes commissures engourdies de remonter un peu,§p210§ t'actives tes doigts dans tes gants dans les poches de ta veste,§p440§ question de r'partir la circulation.§p4200§"
			"\n\n§d90§Encore quelques pas ensemble et vous êtes à l'arrière d'la maison de Dieu§p140§ pis l'vent reprend.§p560§§100§ Vraiment une belle soirée pour être sur l'top d'une colline.§2600§"
			"\n\n§d90§Sara te traîne encore plus derrière l'église,§p220§ dans une allée séparée de la rue par un p'tit muret.§p1800§ À ta gauche,§p160§ tu peux voir le frimas sur les toits plats des buildings adjacents,§p240§ pis les lumières de la ville,§p130§ de l'autre côté d'la rivière.§p2000§ Vous êtes pas mal haut,§p180§ finalement.§p3000§"
			"\nTu continues et un long bâtiment de brique s'érige entre le bord de la falaise et vous,§p110§ coupe le paysage.§p900§ Ça donne moins le vertige.§p2500§ Tu égares ta tête à droite§p100§ et y'a une fenêtre d'allumée§p400§§d110§ - Fuck. §p1200§ §d130§Fuuuuck. §d100§§p4300§"
			"\n§d0§                      §d100§Tu te décrispes et te forces à avancer.§1500§§d90§ Probablement juste un curé presbyte;§p700§ y fait noir anyways.§p800§§d130§"
			"\nCalme.§p2000§"
			"§d200§\n\n\n\n\n§d80§Tu snap out of it et Sara est juste en train d'disparaître au coin du building de briques.§p2100§ Tu resserts ta capuche pis avance.§p1800§"
			"§d100§\n\nAu bout d'la bâtisse,§p300§ votre allée remonte vers un léger promontoir asphalté.§p1100§ Ultime place de parking avant le précipice.§p2300§"
			"\nBordé de la fin du bâtiment de briques à sa gauche,§p200§ le stationnement a mérité une ligne jaune comme limite à droite,§p500§ même si la chute abrupte du relief de beaucoup d'mètres offre aussi une délimitation pas mal claire.§p2000§ Des butoirs de béton ont été installés le long de la ligne de peinture§p130§ et au devant de l'emplacement,§p300§ pour plus de sécurité.§p2600§ À l'avant, c'est bouclé par une clôture haute de 3 ou 4 mètres,§p230§ qui empêche fermement l'accès aux toits adjacents,§p400§ barbelés et tout.§p2400§"
			"§d85§\nClôture sur laquelle les épaules de Sara sont accotées,§p140§ ses deux pieds repoussés contre le bump en béton.§p1500§ Les bras croisés,§210§ le dos trop droit;§p400§"
			"\n   Un sourire qui sussure"
			"\n§d0§                          §d100§\"C'est par là qu'on passe\".§p3000§");

			//L'explication de Sara
			nvauto(monde); acanal(monde,"sara");		
			acond(monde,"intro¶saratrois");	
			adeb(monde,"§bintro¶saratrois=0§§s§");
			afin(monde,"");
			atexte(monde,"§p1600§§d100§\n\"Fait qu'on a juste à monter la clôture,§p300§ là,§bintro¶jequatre=1§§p2400§"
			"\npis après on va vraiment jusqu'au coin,§p300§ jusqu'à l'autre clôture bizarre,§p200§ qui'est comme une grille.§p4000§ Pis elle,§p90§ on la monte§p170§ - tu vas voir c'est pas tough - §p2100§ pis 'y reste juste à r'descendre pis on est sur les toîts.\"");
			
			//Encore l'explication de Sara, mais en gestes (narration)	/ puis la suite
			nvauto(monde); acanal(monde,"je");		
			acond(monde,"intro¶jequatre");	
			adeb(monde,"§bintro¶jequatre=0§§s§");
			afin(monde,"§bintro¶saraquatre=1§");
			atexte(monde,"§d80§\n\nElle se redresse et pose la main à plat sur le grillage en losanges,§p100§ avant de la rediriger en pointant l'extrémité en haut à droite,§p120§ puis avance d'un pas en faisant des gestes de haut en bas avec ses deux bras,§p2000§ te regarde dans les yeux,§p220§ fait un tour sur elle-même en crispant les dents avec ses doigts solidement accrochés à son imagination,§p100§§d85§ puis fait semblant d'atterir sur ses deux pieds,§d95§ finalement.§p4500§"
			"§d100§\n\n\nElle te sourit,§300§ l'air fière de son explication.§p3000§"
			"§d110§\n\nTu clignes des yeux§p290§ une fois.§p1900§"
			"");

											
//-----------------------------------------------------------------|                         |--------------------------------------------------------------------------------\\
	
	//WORK IN PROGRESS
		//Modifier la bibliothèque pour suit my needs
		//monde.biblio.modif("intro","jeprem",1); 
		//monde.biblio.modif("intro","saratrois",1);
	
	
	
	
	//Vérifier une toute première fois la disponibilité des motifs automatiques
	AutoInterpret(monde.canaux, monde.biblio, monde.histoire, base, monde.inp, mem);
	//Faire une boucle pour que les canaux s'expriment!
	jouer(monde,base,mem);				
	curspos(0,13);			//Mettre le curseur dans un bel endroit à la fin


}		
