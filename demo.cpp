/*
			///||================================---2020/01/18---================================||\\\
\\\||================================---Tutoriel / D�mo du potentiel interactif / narratif---================================||///
*/


# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/cadre_fonctionnel_global.cpp"


//-----------------------------------------------------------------|                         |--------------------------------------------------------------------------------\\

int main(void) {

	//Cr�er l'objet o� tout est initi�
	univers u;
	//Ouvrir une fen�tre de bonnes dimensions et initialiser les objets de sauvegarde
	u.MettreDansLeMain();
	
//-----------------------------------------------------------------|      Biblioth�que       |--------------------------------------------------------------------------------\\
	
	u.nvrayon("intro");
		u.nvlivre("desuet");	
		u.nvlivre("jeprem");
		u.nvlivre("jedeux");
		u.nvlivre("saraprem");
		u.nvlivre("saradeux");
		u.nvlivre("jetrois");
		u.nvlivre("saratrois");
		u.nvlivre("jequatre");
		u.nvlivre("saraquatre");
		u.nvlivre("jecinq");
		u.nvlivre("tutoprem");
		u.nvlivre("tutodeux");
		u.nvlivre("saracinq");
		
			
			
//-----------------------------------------------------------------|          D�but          |--------------------------------------------------------------------------------\\

	//Cr�er un canal
	u.nvcanal("je"); u.canaldelai(80); 
	u.nvcanal("sara"); u.canaldelai(130); u.canalalinea(6);
		
	//D�buter un chapitre
	u.nvchapt();
		u.ccond("!intro�desuet");        //Rendre le premier chapitre accessible seulement quand c'est l'intro 

			//Juste le d�but
			u.nvauto(); u.acanal("je");	                                    	
			u.acond("intro�jeprem");	
			u.adeb("�bintro�jeprem=0�");
			u.afin("�bintro�saraprem=1�");
			u.aover(0);						//N'override pas le canal � son d�but
			u.atexte("T'as froid aux joues.�p1400�"
			"\n�d0�                     �d80�Pis aux cuisses.");				

			//Messagerie de directives du d�but (temporaire?)
			u.nvauto(); u.acanal("msn");
			u.acond("intro�jeprem");
			u.afin("�p2600��f0�");
			u.atexte("�p4000�Pour qui�f1�tter le programme,�p400� appuie sur �p210�[ESC�p110�].�p1200�"
			"\nPour modifier la vitesse de d�filement,�p600� appuie sur les touches �p90�[HAUT�p100�] et �p140�[BAS�p90�].");
				
			//La r�ponse de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro�saraprem");	
			u.adeb("�bintro�saraprem=0�");
			u.afin("�bintro�jedeux=1�");
			u.atexte("�p1800�\n\"Come on,�p1100�"
			"\n�d0�          �d130�on est presqu'arriv�es!\"");

			//La suite
			u.nvauto(); u.acanal("je");		
			u.acond("intro�jedeux");	
			u.adeb("�bintro�jedeux=0��s�");
			u.afin("�bintro�saradeux=1�");
			u.atexte("�p400�\n\n         T'acc�l�res le pas,�p600� moins pour la rejoindre�p100� que pour r�chauffer tes jambes.�p1200��d110� Le vent,�p500� criss.�p700� Le vent.�p1600�"
			"\n�d90�Tu l�ves les yeux�p100� juste � la limite de ton capuchon�p300� pis Sara est quand m�me loin en avant.�p1400��d80� Tu te presses un peu plus.�p2800�"
			"\n\nTraverses une rue,�p400� t'es au coin de la cath�drale�p300� pis le vent charge de plus belle depuis ta droite.�p2400� Caliss.�p3000��d90� Sara est d�j� rendue plus bas,�p500� a'longe la grosse chapelle.�p2300�"
			"\n�d0�                       �d80�Tu descends au jogging�p120�, �p400�"
			"\n�d0�                                                �d80�rejoindre au plus vite l'�norme pare-vent de pierre.�p1800�"
			"\nTa jupe virevolte sur tes genoux,�p200� expose tes cuisses aux rafales;�p2300� Pas l'meilleur choix de v�tements.�p4300�"
			"\n\n     La cath�drale coupe le vent�p150� pour vrai.�3100� "
			"\n\n\nSara t'as un peu attendue et te sourit avec son trop d'excitation.�p2200�");

			//La r�ponse de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro�saradeux");	
			u.adeb("�bintro�saradeux=0��s�");
			u.afin("�bintro�jetrois=1�");
			u.atexte("�p130��d110�\n\"J'te jure,�p260� c'est l'meilleur spot au monde,�p240� sur les toits du centro!\"");			

			//La suite
			u.nvauto(); u.acanal("je");		
			u.acond("intro�jetrois");	
			u.adeb("�bintro�jetrois=0��s�");
			u.afin("�bintro�saratrois=1�");
			u.atexte("�p3100�Tu peux pas emp�cher tes commissures engourdies de remonter un peu.�p2600�"
			"\n\n�d90�Encore quelques pas ensemble et vous �tes � l'arri�re d'la maison de Dieu�p140� pis l'vent reprend.�p560��100� Vraiment une belle soir�e pour �tre sur l'top d'une colline.�2600�"
			"\n\n�d90�Sara te tra�ne encore plus derri�re l'�glise,�p220� dans une all�e s�par�e de la rue par un p'tit muret.�p1800� � ta gauche,�p160� tu peux voir le frimas sur les toits plats des buildings adjacents,�p240� pis les lumi�res de la ville,�p130� de l'autre c�t� d'la rivi�re.�p2000� Vous �tes pas mal haut,�p180� finalement.�p3000�"
			"\nTu continues et un long b�timent de briques s'�rige entre le bord de la falaise et vous,�p110� coupe le paysage.�p900� �a donne moins le vertige.�p2500�"

			"\n�d0�               �d90�Tu te demandes si c'est ill�gal de grimper sur les toits des b�timents la nuit.�p1200�"   //Phrase nouvelle; essai; est-ce que c'est bon?
			
			"�d100�\n\nApr�s la b�tisse,�p300� votre all�e remonte � gauche vers un l�ger promontoir asphalt�.�p1100�"
			"\nUltime place de parking avant le pr�cipice.�p2300�"
			"\nLe stationnement garde le b�timent de briques � sa gauche;�p330� et une ligne jaune comme limite � droite,�p540� m�me si le bord du pr�cipice donne aussi une d�limitation pas mal claire.�p2000� Y'a des \"�p120�butoirs\"�p70� en b�ton � droite et au devant de l'emplacement,�p140� tout le long de la peinture jaune.�p2600� � l'avant, c'est boucl� par une cl�ture haute de 3 ou 4 m�tres,�p230� qui emp�che fermement l'acc�s aux toits adjacents,�p400� barbel�s et tout.�p2400�"
			"�d85�\nCl�ture sur laquelle les �paules de Sara sont accot�es,�p140� ses deux pieds repouss�s contre le bump en b�ton.�p1500� Les bras crois�s,�p400� un sourire qui sussure"
			"\n�d0�                          �d100�\"C'est par l� qu'on passe\".�p3000�");

			//L'explication de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro�saratrois");	
			u.adeb("�bintro�saratrois=0��s�");
			u.afin("");
			u.atexte("�p1600��d100�\n\"Fait qu'on a juste � monter la cl�ture,�bintro�jequatre=1��p300� l�,�p2900�"
			"\npis apr�s on va vraiment jusqu'au coin,�p400� jusqu'� l'autre cl�ture bizarre,�p200� la genre de grille qui pend.�p1200� Pis elle,�p90� on la monte�p270� - tu vas voir c'est pas tough - �p5200� pis 'y reste juste � r'descendre pis on est sur les to�ts.\"");
			
			//Encore l'explication de Sara, mais en gestes (narration)	/ puis la tienne
			u.nvauto(); u.acanal("je");		
			u.acond("intro�jequatre");	
			u.adeb("�bintro�jequatre=0��s�");
			u.afin("�bintro�jecinq=1�");
			u.atexte("�d80�\n\nElle se redresse et pose la main � plat sur le grillage en losanges�p540� avant de pointer l'extr�mit� en haut � droite,�p420� avance d'un pas en bougeant de haut en bas avec ses deux bras,�p2800� te regarde dans les yeux,�p1200� fait un tour sur elle-m�me en crispant les dents avec ses doigts solidement accroch�s � son imagination,�p100��d90� et fait semblant d'atterir sur ses deux pieds,�d110� finalement.�p4500�"
			"�d100�\n\n\nElle te sourit,�300� l'air fi�re de son explication.�p2000�"
			"�d110�\nTu clignes des paupi�res�p800� une fois.�p2900�"
			"�d100�\n\n\nLa t�te te soupire�p110� et t'avances pour constater le chemin toi-m�me.�p2100�"
			"\n\nAu devant, la grande barri�re de grillage en losanges�p90� a son top en barbel�s,�p390� dress�s en angle contre votre direction.�p900� �d120�Fait que d�finitivement pas par l�.�p2300�"
			"�d150�\n\n� droite,�p500��d130� par contre,�p430��d110� le grillage finit juste avant la falaise,�p290� et une esp�ce de grille � gros barreaux verticaux prolonge la cl�ture au-dessus du pr�cipice,�p600��d100� probablement pour nous emp�cher de juste tourner le coin.�p1800�"
			"�d120�\n\nMais la grille,�p180� qui fait juste chiller au-ds'us du vide,�p440� elle,�p580� elle a pas de barbel�s.�p400�.�p320�.�p3200�"
			"�d160� Fait que par l�.�p3800�");
	
			//Tu doutes de tes capacit�s, et j'mets plein de vocabulaire � saisir
			u.nvauto(); u.acanal("je");		
			u.acond("intro�jecinq");	
			u.adeb("�bintro�jecinq=0�");
			u.afin("�bintro�saraquatre=1�");			
			u.atexte("�d90�\n\n\n\nTes yeux se ferment bri�vement,�p430� une seconde fois.�p1900�"
			"�d300�\n\n\n�d0�                  �d400�DANGEREUX.�p2200�"
			"�d100�\n\n\nT'ouvres l'oeil sur tes pieds,�p300� au sol,�p430��d120� l'autre oeil,�p520�"
			"\n�d0�                �d100�t'es debout sur l'asphalte,�p460� les orteils � peine sur la ligne jaune du devant du parking,�320� juste avant le bump de b�ton.�p1300�"
			"�d90�\nSara est rendue l'autre bord de la cl�ture�p130�,�p220� d�j� pass�e par-dessus la grille,�p180� agripp�e�p110� l�g�re encore dans le haut de la barri�re,�p330� accroch�e.�p2600�"
			"\n\n\n�d180�Tu ...�p820�,�p1240��d120�        ...tu penses pas�p210��d130� �tre capable�d140� de faire�p140��d160� �a�p300�?�p2600�");

			//La voix du tutoriel qui te parle
			//u.nvauto(); u.acanal("msn");		
			//u.acond("intro�tutoprem");	
			//u.adeb("�bintro�tutoprem=0��f1�");
			//u.afin("�f0�");			
			//u.atexte("�p600�C'est maintenant � toi de guider [t]es actes.�p1000� �cris la commande que tu souhaites effectuer,�p610� puis appuie sur �p120�[ENTER�p90�].�p2200�");

			//Sara te rassures
			u.nvauto(); u.acanal("sara");		
			u.acond("intro�saraquatre");	
			u.adeb("�bintro�saraquatre=0��s�");
			u.afin("");
			u.atexte("�d80�\n\"Tu vois�p110� c'est vraiment simple,�bintro�tutoprem=1��p120� c'est juste la partie o� tu changes de bord qui est un peu tricky,�p130� mais sinon y'a vraiment pas � s'inqui�ter,�p70� tu vas voir �a va full bien s'passer,�p110� pis j'suis l� si y'a d'quoi.\"�bintro�tutodeux=1��p5600�");

			//Les mille et une suggestions d'actions � faire
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin("�bintro�tutodeux=0�"); u.atexte("�p1800�Grimper la cl�ture");
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin(""); u.atexte("�p2130�Avancer");
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin(""); u.atexte("�p2240�Franchir la ligne");
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin(""); u.atexte("�p2270�Continuer");
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin(""); u.atexte("�p2300�Monter dans le grillage");
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin(""); u.atexte("�p2310��tre capable de grimper");
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin(""); u.atexte("�p2330�Poursuivre");
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin(""); u.atexte("�p2420�Aller de l'avant");			
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin(""); u.atexte("�p2450�Rassembler son courage");
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin(""); u.atexte("�p2510�Monter sur les toits");
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin(""); u.atexte("�p2550�Surmonter sa peur");
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin(""); u.atexte("�p2670�Franchir la ligne jaune");
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin(""); u.atexte("�p2830�Rejoindre Sara");
			//u.nvauto(); u.acanal("msn"); u.acond("intro�tutoprem"); u.afin(""); u.atexte("�p3130�Avancer jusqu'� la cl�ture");

			//Sara monologue pour t'encourager
			u.nvauto(); u.acanal("sara");		
			u.acond("intro�saracinq");	
			u.adeb("�bintro�saracinq=0�");
			u.afin("");			
			u.atexte("�p4000�\n\n\"�d130�Ok,�p430� fais juste avancer lentement,�p620� une fois que t'es dedans�p400� �a se fait tu seul.�p1850� S�rieux.�p2670�"
			"\n�d0�          �d110�ok fais juste bouger,�p330� au moins,�p650� avance jusqu'�' clot�re�p1560�,�2p630� envoyes,�470� y fait frette!�p4100�"
			);
			
			
			
//-----------------------------------------------------------------|                         |--------------------------------------------------------------------------------\\
	
	//WORK IN PROGRESS
		//Modifier la biblioth�que pour suit my needs
		//u.biblio.modif("intro","jecinq",1);
	
	
	//Enclencher le premier motif (oui, j'fais �a manuellement pour garder l'uniformit� dans mes enclenchements)
	u.biblio.modif("intro","jeprem",1);
	//V�rifier une toute premi�re fois la disponibilit� des motifs automatiques
	u.AutoInterpret();
	//Faire une boucle pour que les canaux s'expriment!
	u.jouer();				
	curspos(u.cons,0,13);			//Mettre le curseur dans un bel endroit � la fin


}		
