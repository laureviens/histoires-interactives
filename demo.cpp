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
		nvlivre(monde,"jecinq");
		
			
			
//-----------------------------------------------------------------|          D�but          |--------------------------------------------------------------------------------\\

	//Cr�er un canal
	nvcanal(monde,"je"); canaldelai(monde,80); 
	nvcanal(monde,"sara"); canaldelai(monde,130); canalalinea(monde,6);
		
	//D�buter un chapitre
	nvchapt(monde);
		ccond(monde,"!intro�desuet");        //Rendre le premier chapitre accessible seulement quand c'est l'intro 

			//Juste le d�but
			nvauto(monde); acanal(monde,"je");	                                    	
			acond(monde,"intro�jeprem");	
			adeb(monde,"�bintro�jeprem=0�");
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
			atexte(monde,"�p400�\n\n         T'acc�l�res le pas,�p600� moins pour la rejoindre�p100� que pour r�chauffer tes jambes.�p1200��d110� Le vent,�p500� criss.�p700� Le vent.�p1600�"
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
			atexte(monde,"�p130��d110�\n\"J'te jure,�p260� c'est l'meilleur spot au monde,�p240� sur les toits du centro!\"");			

			//La suite
			nvauto(monde); acanal(monde,"je");		
			acond(monde,"intro�jetrois");	
			adeb(monde,"�bintro�jetrois=0��s�");
			afin(monde,"�bintro�saratrois=1�");
			atexte(monde,"�p3100�Tu peux pas emp�cher tes commissures engourdies de remonter un peu.�p2600�"
			"\n\n�d90�Encore quelques pas ensemble et vous �tes � l'arri�re d'la maison de Dieu�p140� pis l'vent reprend.�p560��100� Vraiment une belle soir�e pour �tre sur l'top d'une colline.�2600�"
			"\n\n�d90�Sara te tra�ne encore plus derri�re l'�glise,�p220� dans une all�e s�par�e de la rue par un p'tit muret.�p1800� � ta gauche,�p160� tu peux voir le frimas sur les toits plats des buildings adjacents,�p240� pis les lumi�res de la ville,�p130� de l'autre c�t� d'la rivi�re.�p2000� Vous �tes pas mal haut,�p180� finalement.�p3000�"
			"\nTu continues et un long b�timent de briques s'�rige entre le bord de la falaise et vous,�p110� coupe le paysage.�p900� �a donne moins le vertige.�p2500�"

			"\n�d0�               �d90�Tu te demandes si c'est ill�gal de grimper sur les toits des b�timents la nuit.�p1200�"   //Phrase nouvelle; essai; est-ce que c'est bon?
			
			"�d100�\n\nAu bout d'la b�tisse,�p300� votre all�e remonte vers un l�ger promontoir asphalt�.�p1100�"
			"\nUltime place de parking avant le pr�cipice.�p2300�"
			"\nBord� de la fin du b�timent de briques � sa gauche,�p200� le stationnement a m�rit� une ligne jaune comme limite � droite,�p500� m�me si la chute abrupte du relief de beaucoup d'm�tres offre aussi une d�limitation pas mal claire.�p2000� Des butoirs de b�ton ont �t� install�s le long de la peinture jaune,�p130� � droite et au devant de l'emplacement,�p300� pour plus de s�curit�.�p2600� � l'avant, c'est boucl� par une cl�ture haute de 3 ou 4 m�tres,�p230� qui emp�che fermement l'acc�s aux toits adjacents,�p400� barbel�s et tout.�p2400�"
			"�d85�\nCl�ture sur laquelle les �paules de Sara sont accot�es,�p140� ses deux pieds repouss�s contre le bump en b�ton.�p1500� Les bras crois�s,�210� le dos trop droit;�p400�"
			"\n   Un sourire qui sussure"
			"\n�d0�                          �d100�\"C'est par l� qu'on passe\".�p3000�");

			//L'explication de Sara
			nvauto(monde); acanal(monde,"sara");		
			acond(monde,"intro�saratrois");	
			adeb(monde,"�bintro�saratrois=0��s�");
			afin(monde,"");
			atexte(monde,"�p1600��d100�\n\"Fait qu'on a juste � monter la cl�ture,�bintro�jequatre=1��p300� l�,�p2900�"
			"\npis apr�s on va vraiment jusqu'au coin,�p400� jusqu'� l'autre cl�ture bizarre,�p200� la genre de grille qui pend.�p1200� Pis elle,�p90� on la monte�p270� - tu vas voir c'est pas tough - �p5200� pis 'y reste juste � r'descendre pis on est sur les to�ts.\"");
			
			//Encore l'explication de Sara, mais en gestes (narration)	/ puis la suite
			nvauto(monde); acanal(monde,"je");		
			acond(monde,"intro�jequatre");	
			adeb(monde,"�bintro�jequatre=0��s�");
			afin(monde,"");
			atexte(monde,"�d80�\n\nElle se redresse et pose la main � plat sur le grillage en losanges�p540� avant de pointer l'extr�mit� en haut � droite,�p420� avance d'un pas en bougeant de haut en bas avec ses deux bras,�p2800� te regarde dans les yeux,�p1200� fait un tour sur elle-m�me en crispant les dents avec ses doigts solidement accroch�s � son imagination,�p100��d90� et fait semblant d'atterir sur ses deux pieds,�d110� finalement.�p4500�"
			"�d100�\n\n\nElle te sourit,�300� l'air fi�re de son explication.�p2000�"
			"�d110�\nTu clignes des paupi�res�p800� une fois.�p2900�"
			"�d100�\n\n\nLa t�te te soupire�p110� et t'avances pour constater le chemin toi-m�me.�p2100�"
			"\n\nAu devant, la grande barri�re de grillage en losanges�p90� a son top en barbel�s,�p390� dress�s en angle contre votre direction.�p900� �d120�Fait que d�finitivement pas par l�.�p2300�"
			"�d150�\n\n� droite,�p500��d130� par contre,�p430��d110� le grillage finit juste avant la falaise,�p290� et une esp�ce de grille � gros barreaux verticaux prolonge la cl�ture au-dessus du pr�cipice,�p600��d100� probablement pour nous emp�cher de juste tourner le coin.�p1800�"
			"�d120�\n\nMais la grille,�p180� qui fait juste chiller au-ds'us du vide,�p440� elle,�p580� elle a pas de barbel�s.�p400�.�p320�.�p3200�"
			"�d160� Fait que par l�.�p3800�"
			"�d90�\n\n\n\nTes yeux se ferment bri�vement,�p430� une seconde fois.�p1900�"
			"�d300�\n\n\n�d0�                  �d400�DANGEREUX.�p2200�"
			"�d100�\n\n\nT'ouvres l'oeil sur tes pieds,�p300� au sol,�p430��d120� l'autre oeil,�p520�"
			"\n�d0�                �d100�t'es debout sur l'asphalte,�p460� les orteils � peine sur la ligne jaune du devant du parking,�320� juste avant le bump de b�ton.�p1300�"
			"�d90�\nSara est rendue l'autre bord du grillage�p130�,�p220� d�j� pass�e par-dessus la grille,�p180� agripp�e�p110� l�g�re encore dans le haut de la barri�re,�p330� accroch�e.�p2600��bintro�saraquatre=1��p2600�"
			"�d400��c�Non.�p1800�"
			"�d500��s�\n\n\n\n\n\n�d180�Non.�p600��d120� Non j'fais pas �a.�p700� �d600�Non.�p1700�");

			//L'explication de Sara
			nvauto(monde); acanal(monde,"sara");		
			acond(monde,"intro�saraquatre");	
			adeb(monde,"�bintro�saraquatre=0��s�");
			afin(monde,"�bintro�jecinq=1�");
			atexte(monde,"�d80�\n\"Tu vois c'est vraiment simple,�p90� c'est juste la partie o� tu changes de bord qui est un peu tricky,�p100� mais sinon y'a vraiment pas � s'inqui�ter,�p70� tu vas voir �a va full bien s'passer,�p110� pis j'suis l� si y'a d'quoi�p100� -\"�p1600�"
			"�s�\n\n\"�a va�p230�  ?\"");
			

					//Commentaire de Cyb�le:
							//�a serait le fun d'avoir de l'info ("plus t�t") sur c'qu'on fait l�,
							//pour pouvoir anticiper plus la suite.
								//Genre savoir un peu le but de tout �a.
									//Donc genre mettre dans les premi�res lignes de dialogue de Sara un p'tit "Tu vas voir, c'est super le fun sur les toits d'la main"
											
									//Pis commentaire personnel: Le rythme, quand �a d�file par lui-m�me, est quand m�me lent.
										//Genre c'est un bon 5 minutes se rendre jusqu'au premier choix (traverser la ligne jaune ou pas).
										//Fait que oui, �a devient super pertinent de mettre un peu de "why" l�-dedans.
										
							//C'que j'ai chang� en r�ponse:
									//J'ai mis en commentaire deux sections pas utiles, limite redondantes, pour acc�l�rer le rythme.
									//J'ai chang� "J'te jure,�p260� �a vaut vraiment la peine!"
										//par "J'te jure,�p260� c'est l'meilleur spot au monde,�p240� sur les toits du centro!"
											
								//J'devrais peut-�tre aussi ajouter une ptite phrase narrative quand tu marches encore dans les rues (au d�but-d�but)			
											
													//� la limite, j'peux �galement scrapper mon p'tit bout de confusion o� tout le monde �crit en m�me temps, parce qu'il ne sert pas tant � grand-chose...
					
									//Update: J'ai mis une phrase quand elles sont d�j� � l'arri�re de la cath�drale, et �a fait un beau rappel, en plus de donner le caract�re de la personnage principale		
													
					//Commentaire de moi:
							//Le rythme est pas si pire, et j'pense que le but est assez �nonc� (selon mon humble avis).
							//J'aime �galement le bout o� tout le monde parle en m�me temps, j'trouve que �a aide la visualisation sans �tre lourd.
							//Par contre, le bout que j'trouve maintenant superflus / dans les jambes, c'est la description de l"ultime place de parking". 
								//Id�alement, faudrait la r��crire pour qu'il y ait les m�mes informations, mais dans une forme moins lourde. Moins une pause.
									//Plus comme l'observation du chemin?
											//Principe exp�rimental: �tre en relation avec l'environnement (y marcher, l'observer activement), plut�t que le d�crire (dans le but de se l'imaginer bien).
						
											
		//La suite, pour introduire les actions � �crire:
			//Ish, j'ai l'impression qu'il me faudrait vraiment des notes �crites en mode "chatt" (qui s'�crivent, et qui dispara�ssent comme si effac�es par backspace),
			//qui pausent tous les autres canaux, et qui sont genre en blanc, pour dire "Maintenant, c'est � toi de jouer / �crire les actions que tu d�sires."
			//Pis d�s que �a s'efface, (id�alment, y'a un peu de chevauchement) les autres canaux reprennent vie.
			
			//�a serait vraiment important de d�finir si oui ou non j'ai acc�s � cet outil, parce que le niveau d'encouragement/aide que je vais donner via les canaux normaux
			//en d�pend vraiment.
									//Fait que mettons que j'prends une d�cision: oui, j'vais utiliser + d�velopper cet outil.
												//(doit s'afficher apr�s la m�moire, pour effacer certaines lignes, et �tre positionn�).	
												
																	
//-----------------------------------------------------------------|                         |--------------------------------------------------------------------------------\\
	
	//WORK IN PROGRESS
		//Modifier la biblioth�que pour suit my needs
		monde.biblio.modif("intro","saratrois",1);
	
	
	
	//Enclencher le premier motif (oui, j'fais �a manuellement pour garder l'uniformit� dans mes enclenchements)
	//monde.biblio.modif("intro","jeprem",1);
	//V�rifier une toute premi�re fois la disponibilit� des motifs automatiques
	AutoInterpret(monde.canaux, monde.biblio, monde.histoire, base, monde.inp, mem);
	//Faire une boucle pour que les canaux s'expriment!
	jouer(monde,base,mem);				
	curspos(0,13);			//Mettre le curseur dans un bel endroit � la fin


}		
