/*
			///||================================---2020/01/18---================================||\\\
\\\||================================---Tutoriel / D�mo du potentiel interactif / narratif---================================||///
*/


# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/cadre_fonctionnel_global.cpp"


//-----------------------------------------------------------------|                         |--------------------------------------------------------------------------------\\

int main(void) {

	//Changement de taille et de place de la console                     //Doit �tre d�fini � l'int�rieur du main() pour fonctionner!
	//x, y, width, height,
	fen base(600,30,500,500);                                           //Cr�e �galement l'objet dans lequel ces param�tres sont d�finis       
	memoire mem(base.limtxtx);

	//Cr�er l'objet o� tout est initi�
	univers monde;

//-----------------------------------------------------------------|      Biblioth�que       |--------------------------------------------------------------------------------\\
	
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
		
			
			
//-----------------------------------------------------------------|          D�but          |--------------------------------------------------------------------------------\\

	//Cr�er un canal
	nvcanal(monde,"je"); canaldelai(monde,80); 
	nvcanal(monde,"sara"); canaldelai(monde,130); canalalinea(monde,6);
		
	//D�buter un chapitre
	nvchapt(monde);
		ccond(monde,"!intro�desuet");        //Rendre le premier chapitre accessible seulement quand c'est l'intro 

			//Juste le d�but
			nvauto(monde); acanal(monde,"je");	                                    	
			acond(monde,"!intro�jeprem");	
			adeb(monde,"�bintro�jeprem=1�");
			afin(monde,"�bintro�saraprem=1�");
			aover(monde,0);						//N'override pas le canal � son d�but
			atexte(monde,"T'as froid aux joues.�p1400�"
			"\n�d0�                     �d80�Pis aux cuisses.");				

			//La r�ponse de Sara
			nvauto(monde); acanal(monde,"sara");		
			acond(monde,"intro�saraprem");	
			adeb(monde,"�bintro�saraprem=0�");
			afin(monde,"�bintro�jedeux=1�");
			atexte(monde,"�p1800�\"Come on,�p1100�"
			"\n�d0�          �d130�on est presqu'arriv�es!\"");

			//La suite
			nvauto(monde); acanal(monde,"je");		
			acond(monde,"intro�jedeux");	
			adeb(monde,"�bintro�jedeux=0��s�");
			afin(monde,"�bintro�saradeux=1�");
			atexte(monde,"�p400�\n\n         T'acc�l�res le pas,�p600� moins pour la rejoindre�p100� que pour r�chauffer tes jambes.�p1200��d110� Le vent,�p500� criss.�p1000� Le vent.�p2000�"
			"\n  Fait frette.�p2200�"
			"\n�d90�Tu l�ves les yeux�p100� juste � la limite de ton capuchon�p300� pis Sara est quand m�me loin en avant.�p1400��d80� Tu te presses un peu plus.�p2800�"
			"\n\nTraverses une rue,�p400� t'es au coin de la cath�drale�p300� pis le vent charge de plus belle depuis ta droite.�p2400� Caliss.�p3000��d90� Sara est d�j� rendue plus bas,�p500� a'longe la grosse chapelle.�p2300�"
			"\n�d0�                       �d80�Tu descends au jogging�p120�, �p400�"
			"\n�d0�                                                �d80�rejoindre au plus vite l'�norme pare-vent de pierre.�p1800�"
			"\nTa jupe virevolte sur tes genoux,�p200� expose tes cuisses aux rafales;�p2300� Pas l'meilleur choix de v�tements.�p4300�"
			"\n\n     La cath�drale coupe le vent�p150� pour vrai.�3100� "
			"\n\n\nSara t'as un peu attendue et te sourit avec son trop d'excitation.�p2200�");

			//La r�ponse de Sara
			nvauto(monde); acanal(monde,"sara");		
			acond(monde,"intro�saradeux");	
			adeb(monde,"�bintro�saradeux=0��s�");
			afin(monde,"�bintro�jetrois=1�");
			atexte(monde,"�p130��d110�\n\"J'te jure,�p260� �a vaut vraiment la peine!\"");			

			//La suite
			nvauto(monde); acanal(monde,"je");		
			acond(monde,"intro�jetrois");	
			adeb(monde,"�bintro�jetrois=0��s�");
			afin(monde,"�bintro�saratrois=1�");
			atexte(monde,"�p3100�Tu peux pas emp�cher tes commissures engourdies de remonter un peu,�p210� t'actives tes doigts dans tes gants dans les poches de ta veste,�p440� question de r'partir la circulation.�p4200�"
			"\n\n�d90�Encore quelques pas ensemble et vous �tes � l'arri�re d'la maison de Dieu�p140� pis l'vent reprend.�p560��100� Vraiment une belle soir�e pour �tre sur l'top d'une colline.�2600�"
			"\n\n�d90�Sara te tra�ne encore plus derri�re l'�glise,�p220� dans une all�e s�par�e de la rue par un p'tit muret.�p1800� � ta gauche,�p160� tu peux voir le frimas sur les toits plats des buildings adjacents,�p240� pis les lumi�res de la ville,�p130� de l'autre c�t� d'la rivi�re.�p2000� Vous �tes pas mal haut,�p180� finalement.�p3000�"
			"\nTu continues et un long b�timent de brique s'�rige entre le bord de la falaise et vous,�p110� coupe le paysage.�p900� �a donne moins le vertige.�p2500� Tu �gares ta t�te � droite�p100� et y'a une fen�tre d'allum�e�p400��d110� - Fuck. �p1200� �d130�Fuuuuck. �d100��p4300�"
			"\n�d0�                      �d100�Tu te d�crispes et te forces � avancer.�1500��d90� Probablement juste un cur� presbyte;�p700� y fait noir anyways.�p800��d130�"
			"\nCalme.�p2000�"
			"�d200�\n\n\n\n\n�d80�Tu snap out of it et Sara est juste en train d'dispara�tre au coin du building de briques.�p2100� Tu resserts ta capuche pis avance.�p1800�"
			"�d100�\n\nAu bout d'la b�tisse,�p300� votre all�e remonte vers un l�ger promontoir asphalt�.�p1100� Ultime place de parking avant le pr�cipice.�p2300�"
			"\nBord� de la fin du b�timent de briques � sa gauche,�p200� le stationnement a m�rit� une ligne jaune comme limite � droite,�p500� m�me si la chute abrupte du relief de beaucoup d'm�tres offre aussi une d�limitation pas mal claire.�p2000� Des butoirs de b�ton ont �t� install�s le long de la ligne de peinture�p130� et au devant de l'emplacement,�p300� pour plus de s�curit�.�p2600� � l'avant, c'est boucl� par une cl�ture haute de 3 ou 4 m�tres,�p230� qui emp�che fermement l'acc�s aux toits adjacents,�p400� barbel�s et tout.�p2400�"
			"�d85�\nCl�ture sur laquelle les �paules de Sara sont accot�es,�p140� ses deux pieds repouss�s contre le bump en b�ton.�p1500� Les bras crois�s,�210� le dos trop droit;�p400�"
			"\n   Un sourire qui sussure"
			"\n�d0�                          �d100�\"C'est par l� qu'on passe\".�p3000�");

			//L'explication de Sara
			nvauto(monde); acanal(monde,"sara");		
			acond(monde,"intro�saratrois");	
			adeb(monde,"�bintro�saratrois=0��s�");
			afin(monde,"");
			atexte(monde,"�p1600��d100�\n\"Fait qu'on a juste � monter la cl�ture,�p300� l�,�bintro�jequatre=1��p2400�"
			"\npis apr�s on va vraiment jusqu'au coin,�p300� jusqu'� l'autre cl�ture bizarre,�p200� qui'est comme une grille.�p4000� Pis elle,�p90� on la monte�p170� - tu vas voir c'est pas tough - �p2100� pis 'y reste juste � r'descendre pis on est sur les to�ts.\"");
			
			//Encore l'explication de Sara, mais en gestes (narration)	/ puis la suite
			nvauto(monde); acanal(monde,"je");		
			acond(monde,"intro�jequatre");	
			adeb(monde,"�bintro�jequatre=0��s�");
			afin(monde,"�bintro�saraquatre=1�");
			atexte(monde,"�d80�\n\nElle se redresse et pose la main � plat sur le grillage en losanges,�p100� avant de la rediriger en pointant l'extr�mit� en haut � droite,�p120� puis avance d'un pas en faisant des gestes de haut en bas avec ses deux bras,�p2000� te regarde dans les yeux,�p220� fait un tour sur elle-m�me en crispant les dents avec ses doigts solidement accroch�s � son imagination,�p100��d85� puis fait semblant d'atterir sur ses deux pieds,�d95� finalement.�p4500�"
			"�d100�\n\n\nElle te sourit,�300� l'air fi�re de son explication.�p3000�"
			"�d110�\n\nTu clignes des yeux�p290� une fois.�p1900�"
			"");

											
//-----------------------------------------------------------------|                         |--------------------------------------------------------------------------------\\
	
	//WORK IN PROGRESS
		//Modifier la biblioth�que pour suit my needs
		//monde.biblio.modif("intro","jeprem",1); 
		//monde.biblio.modif("intro","saratrois",1);
	
	
	
	
	//V�rifier une toute premi�re fois la disponibilit� des motifs automatiques
	AutoInterpret(monde.canaux, monde.biblio, monde.histoire, base, monde.inp, mem);
	//Faire une boucle pour que les canaux s'expriment!
	jouer(monde,base,mem);				
	curspos(0,13);			//Mettre le curseur dans un bel endroit � la fin


}		
