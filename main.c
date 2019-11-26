#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define NOMBREDESSAIE 12
#define NOIR 0
#define GRIS 7
#define VERT 2
#define JAUNE 14


typedef struct tQuatuorMasterMind
//Soit w,x,y,z pour les 4 valeurs dans l'ordre wxyz.
{
    int nW;
    int nX;
    int nY;
    int nZ;
    //Pour les couleurs les valeurs peuvent �tre 0, 1 ou 2.
    //0 pour pas de modification � l'affichage.
    //1 pour une valeur correct mais pas au bon endroit.
    //2 pour une valeur correct au bon endroit.
    int nCouleurW;
    int nCouleurX;
    int nCouleurY;
    int nCouleurZ;
}tQuatuorMasterMind;

//Mutateurs.
void setW(tQuatuorMasterMind *tQ,int nInt);
void setX(tQuatuorMasterMind *tQ,int nInt);
void setY(tQuatuorMasterMind *tQ,int nInt);
void setZ(tQuatuorMasterMind *tQ,int nInt);
void setCouleurW(tQuatuorMasterMind *tQ,int nInt);
void setCouleurX(tQuatuorMasterMind *tQ,int nInt);
void setCouleurY(tQuatuorMasterMind *tQ,int nInt);
void setCouleurZ(tQuatuorMasterMind *tQ,int nInt);
//Accesseurs.
int getW(tQuatuorMasterMind tQ);
int getX(tQuatuorMasterMind tQ);
int getY(tQuatuorMasterMind tQ);
int getZ(tQuatuorMasterMind tQ);
int getCouleurW(tQuatuorMasterMind tQ);
int getCouleurX(tQuatuorMasterMind tQ);
int getCouleurY(tQuatuorMasterMind tQ);
int getCouleurZ(tQuatuorMasterMind tQ);

//Les Prototypes.
//Mise en place de la donn�e.
void random(int *nAlea,int nImpossibleA,int nImpossibleB,int nImpossibleC);
void creationQuatuorMasterMind(tQuatuorMasterMind *tQuatuor);
tQuatuorMasterMind creattQ(int nA, int nB,int nC,int nD);
void decomposition9999(int nDecomp,int *nMillier,int *nCentaine,int *nDizaine,int *nUnite);
//Gestion de la donn�e.
void gestionDuTourDuJoueur(int nIndex,tQuatuorMasterMind tQTabEntreeJoueur[NOMBREDESSAIE]);
int gestionEntreeDuJoueur();
void comparaisonAvecLaSolution(int nIndex,tQuatuorMasterMind tQTabEntreeJoueur[NOMBREDESSAIE],tQuatuorMasterMind tQSolution);
int verifjoueur(int nEntreeJoueur);
int verifcasparcas(int nVerif,int nA,int nB,int nC);
//Affichage.
void afficheTQ(tQuatuorMasterMind leTQ);
void afficheTQJoueur(int nIndex,tQuatuorMasterMind tQTabEntreeJoueur[NOMBREDESSAIE]);
void color(int t,int f);
void afficheDigitJoueur(int nLeCouleur,int nLeDigit);


int main()
{
    //Cr�ation de la solution.
    tQuatuorMasterMind tQSolution;
    creationQuatuorMasterMind(&tQSolution);
    
    //On n'affiche pas la solution pour le joueur, mais on peut enlever le commentaire pour les tests.
    /*printf("La solution est : ");
    afficheTQ(tQSolution);
    printf(".\n");*/

    //Cr�ation du tableau contenant les saisis du joueur.
    tQuatuorMasterMind tQTabJoueur[NOMBREDESSAIE];
    int nI=0;
    while (nI<NOMBREDESSAIE)
    {
        gestionDuTourDuJoueur(nI,tQTabJoueur);
        //G�rer les entr�es.
        comparaisonAvecLaSolution(nI,tQTabJoueur,tQSolution);
        printf("Vos propositions jusqu'ici sont :\n");
        afficheTQJoueur(nI,tQTabJoueur);
        printf("\n");

        if ((tQTabJoueur[nI].nCouleurW==2)&&(tQTabJoueur[nI].nCouleurX==2)&&(tQTabJoueur[nI].nCouleurY==2)&&(tQTabJoueur[nI].nCouleurZ==2))
        {
        	printf("Vous avez trouve le code felicitations !!!\n");
        	nI=NOMBREDESSAIE;
        }
        else if (nI==11)
	   	{
	    	printf("Vous avez use vos 12 essaies, la solution �tait : ");
	    	color(VERT,NOIR);
	    	afficheTQ(tQSolution);
	    	printf(".\n");
	    }

        nI++;
    }


    return 0;
}

//Affichage.

void afficheTQ(tQuatuorMasterMind leTQ)
//BUT : Afficher les 4 valeurs d'un tQuatuorMasterMind.
//ENTREE : Une variable du type structur� tQuatuorMasterMind.
//SORTIE : Ses 4 valeurs affich�es � la suite � l'�cran sans retour � la ligne.
{
    printf("%d%d%d%d",leTQ.nW,leTQ.nX,leTQ.nY,leTQ.nZ);
}

void color(int t,int f)
//Les couleurs qu'on utilise, 0 pour noir, 7 pour gris clair, 2 pour du vert, 14 pour du jaune.
{
	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H,f*16+t);
}

void afficheTQJoueur(int nIndex,tQuatuorMasterMind tQTabEntreeJoueur[NOMBREDESSAIE])
{
	//int nI; //Le compilateur dit qu'on a pas � pr�d�clarer nI apparemment.
	for (int nI = 0; nI <= nIndex; nI++)
	{
		afficheDigitJoueur(tQTabEntreeJoueur[nI].nCouleurW,tQTabEntreeJoueur[nI].nW);
		afficheDigitJoueur(tQTabEntreeJoueur[nI].nCouleurX,tQTabEntreeJoueur[nI].nX);
		afficheDigitJoueur(tQTabEntreeJoueur[nI].nCouleurY,tQTabEntreeJoueur[nI].nY);
		afficheDigitJoueur(tQTabEntreeJoueur[nI].nCouleurZ,tQTabEntreeJoueur[nI].nZ);
		printf("\n");
	}
}

void afficheDigitJoueur(int nLeCouleur,int nLeDigit)
{
	int nLaCouleur=GRIS; //On a du gris par d�faut dans la console.
	if (nLeCouleur==1)
	{
		nLaCouleur=JAUNE; //On met du jaune si on est mal plac� mais qu'on est dans le code final.
	}
	else if (nLeCouleur==2)
	{
		nLaCouleur=VERT; //On met du vert si on est bien plac� par rapport au code final
	}
	color (nLaCouleur,NOIR); //On garde la couleur de fond en noir.
	printf("%d",nLeDigit);
	color (GRIS,NOIR); //On r�initialise apr�s l'�criture.
}

//Gestion de la donn�e.

void gestionDuTourDuJoueur(int nIndex,tQuatuorMasterMind tQTabEntreeJoueur[NOMBREDESSAIE])
//BUT : G�rer le tour du joueur.
//ENTREE : Le tableau des entr�es actuelles et l'index nI pour savoir � combien d'essaie nous en sommes.
//SORTIE : Le r�sultat de l'action du joueur.
{
    int nTentative,nTentativeW,nTentativeX,nTentativeY,nTentativeZ;
    nTentative=gestionEntreeDuJoueur();
    decomposition9999(nTentative,&nTentativeW,&nTentativeX,&nTentativeY,&nTentativeZ);
    tQTabEntreeJoueur[nIndex]=creattQ(nTentativeW,nTentativeX,nTentativeY,nTentativeZ);

    /*
    printf("Le Joueur a rentre la valeur : ");
    afficheTQ(tQTabEntreeJoueur[nIndex]);
    printf(".\n");
    */
}

int gestionEntreeDuJoueur()
//BUT : Recevoir l'information du joueur et v�rifier si elle est dans la norme souhait�e, compris entre 0 et 9999.
//ENTREE : Un entier saisi par l'utilisateur.
//SORTIE : L'entier saisi v�rifi�.
{
    int nEntreeJoueur=-1;
    int nVerification=0;
    while (nEntreeJoueur<0 || nEntreeJoueur>9999)
    {
        printf("Veuillez entrer votre proposition sous la forme d'un entier a 4 chiffres, il n'y a pas de doublons dans le code secret, et vous ne pouvez pas en rentrer.\n");
        scanf("%d",&nEntreeJoueur);
        nVerification=verifjoueur(nEntreeJoueur); //On v�rifie si l'utilisateur a entr� un doublon.
        if (nVerification==1) //Si on a un doublon on redemande l'entr�e � l'utilisateur.
        {
        	nEntreeJoueur=-1;
        }
    }
    return nEntreeJoueur;
}

int verifjoueur(int nEntreeJoueur)
//BUT : V�rifier l'entr�e du joueur et emp�cher les doublons.
//ENTREE : L'entr�e du joueur.
//SORTIE : 0 si il n'y a pas de doublon 1 si il y en a.
{
	int nVerif=0;
	int nW=-1,nX=-1,nY=-1,nZ=-1;
	int nCas1=0,nCas2=0,nCas3=0,nCas4=0;
	decomposition9999(nEntreeJoueur,&nW,&nX,&nY,&nZ);
	nCas1=verifcasparcas(nW,nZ,nY,nX);
	nCas2=verifcasparcas(nX,nW,nZ,nY);
	nCas3=verifcasparcas(nY,nX,nW,nZ);
	nCas4=verifcasparcas(nZ,nY,nX,nW);
	if (nCas1==1 || nCas2==1|| nCas3==1 || nCas4==1)
	{
		nVerif=1;
	}
	return nVerif;
}

int verifcasparcas(int nVerif,int nA,int nB,int nC)
//BUT : V�rifier si la premi�re entr�e est �gale � une des trois autres.
//ENTREE : Une entr�e � v�rifier et 3 � comparer.
//SORTIE : 1 Si on a un doublon, 0 si on oest bon
{
	int nBon=0;
	if ((nVerif==nA)||(nVerif==nB)||(nVerif==nC))
	{
		nBon=1;
	}
	return nBon;
}

void comparaisonAvecLaSolution(int nIndex,tQuatuorMasterMind tQTabEntreeJoueur[NOMBREDESSAIE],tQuatuorMasterMind tQSolution)
//BUT : Modifier la couleur de l'affichage du joueur pour la rendre coh�rente compar�e � la solution.
//ENTREE : La table entr�e par le joueur, son index et la solution.
//SORTIE : La table entr�e par le joueur aux couleurs modifi�es.
{
	//D�but d'une immense for�t d'ifs.
	if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW) //Le cas du nW en principal
	//Si le nW de la solution est pris, on ne le v�rifie plus apr�s.
	{
		//On est en �galit� totale, donc on passe en couleur 2.
		tQTabEntreeJoueur[nIndex].nCouleurW=2;
		if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
		//Si le nX de la solution est pris, on ne le v�rifie plus apr�s.
		{
			//On est en �galit� totale, donc on passe en couleur 2.
			tQTabEntreeJoueur[nIndex].nCouleurW=2;
			if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
			//Si le nY de la solution est pris, on ne le v�rifie plus apr�s.
			{
				//On est en �galit� totale, donc on passe en couleur 2.
				tQTabEntreeJoueur[nIndex].nCouleurY=2;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurZ=2;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
			//Si le nY n'est pas bon, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
				//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
		//Si le nX n'est pas bon, on v�rifie le nY, et comme le nY serait bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurX=1;
			//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
			if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
				//nW,nX et nY sont pos�s.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurZ=2;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
			//Si le nX et le nY ne sont pas bons, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
				//Puisque le nX n'�tait pas bon avant, on le v�rifie ici.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
					if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
					//Puisque le nY n'�tait pas bon avant, on le v�rifie ici.
					//On est dans la derni�re v�rification.
					{
						tQTabEntreeJoueur[nIndex].nCouleurZ=1;
					}
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
		//Si le nX et le nY ne sont pas bons, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurX=1;
			if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
			//Puisque le nX n'�tait pas bon avant, on le v�rifie ici.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
				//Puisque le nY n'�tait pas bon avant, on le v�rifie ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
		}
	}
	else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
	//Si le nW n'est pas bon, on v�rifie le nX, et comme le nX serait bon, on ne le v�rifie plus apr�s.
	{
		tQTabEntreeJoueur[nIndex].nCouleurW=1;
		if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
		//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurX=1;
			//nX et nW sont pris, on reprend donc le cas d'avant � ce m�me stade.
			if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
			//Si le nY de la solution est pris, on ne le v�rifie plus apr�s.
			{
				//On est en �galit� totale, donc on passe en couleur 2.
				tQTabEntreeJoueur[nIndex].nCouleurY=2;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
				//On est dans la derni�re v�rification.
				//Comme le nZ n'�tait pas bon avant, il peut l'�tre ici.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurZ=2;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
			//Si le nY n'est pas bon, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
				//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
		}
		if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
		//Puisque nW et nX ne sont pas bons, on v�rifie nY, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurX=1;
			if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
				//Si le nZ n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurZ=2;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
			//Si le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
		//Puisque le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurX=1;
			if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
				//Si le nY n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
			//Puisque le nW ne convient pas, on test le nZ qu'on ne v�rifie plus apr�s
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
		}
	}
	else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
	//Si le nW et le nX ne sont pas bons, on v�rifie le nY, et comme le nY serait bon, on ne le v�rifie plus apr�s.
	{
		tQTabEntreeJoueur[nIndex].nCouleurW=1;
		if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
		//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurX=1;
			//nY et nW sont pris, on test donc nX.
			if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
			//Si le nX de la solution est pris, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
				//On est dans la derni�re v�rification.
				//Comme le nZ n'�tait pas bon avant, il peut l'�tre ici.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurZ=2;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
			//Si le nX n'est pas bon, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
				//Comme le nX n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
		//Puisque nW et nY ne sont pas bons, on v�rifie nX, et si il est bon, on ne le v�rifie plus apr�s.
		{
			//On est en �galit� totale, la couleur passe � deux.
			tQTabEntreeJoueur[nIndex].nCouleurX=2;
			if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
				//Si le nZ n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurZ=2;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
			//Si le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
		//Puisque le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurX=1;
			if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
				//Si le nX n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
			//Puisque le nW ne convient pas, on test le nX qu'on ne v�rifie plus apr�s
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
		}
	}else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
	//Si le nW, le nX et le nY ne sont pas bons, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
	{
		tQTabEntreeJoueur[nIndex].nCouleurW=1;
		if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
		//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurX=1;
			//nY et nW sont pris, on test donc nX.
			if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
			//Si le nX de la solution est pris, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
				//On est dans la derni�re v�rification.
				//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
				{
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
			//Si le nX n'est pas bon, on v�rifie le nY, et comme le nY serait bon, on ne le v�rifie plus apr�s.
			{
				//Egalit� totale, couleur=2.
				tQTabEntreeJoueur[nIndex].nCouleurY=2;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
				//Comme le nX n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
		//Puisque nW et nY ne sont pas bons, on v�rifie nX, et si il est bon, on ne le v�rifie plus apr�s.
		{
			//On est en �galit� totale, la couleur passe � deux.
			tQTabEntreeJoueur[nIndex].nCouleurX=2;
			if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
				//Si le nY n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
			//Si le nY n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				//Egalit� totale, couleur=2.
				tQTabEntreeJoueur[nIndex].nCouleurY=2;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
		//Puisque le nY n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurX=1;
			if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
				//Si le nX n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
			//Puisque le nW ne convient pas, on test le nX qu'on ne v�rifie plus apr�s
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				}
			}
		}
	}
	else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW) //Le cas du nX en principal
	//Si le nW de la solution est pris, on ne le v�rifie plus apr�s.
	{
		//On est en �galit� totale, donc on passe en couleur 2.
		tQTabEntreeJoueur[nIndex].nCouleurX=1;
		if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
		//Si le nX de la solution est pris, on ne le v�rifie plus apr�s.
		{
			//On est en �galit� totale, donc on passe en couleur 2.
			tQTabEntreeJoueur[nIndex].nCouleurY=1;
			if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
			//Si le nY de la solution est pris, on ne le v�rifie plus apr�s.
			{
				//On est en �galit� totale, donc on passe en couleur 2.
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
			//Si le nY n'est pas bon, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=2;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
				//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
		//Si le nX n'est pas bon, on v�rifie le nY, et comme le nY serait bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurY=2;
			//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
			if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
				//nW,nX et nY sont pos�s.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
			//Si le nX et le nY ne sont pas bons, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurY=1;
				if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
				//Puisque le nX n'�tait pas bon avant, on le v�rifie ici.
				{
					tQTabEntreeJoueur[nIndex].nCouleurZ=1;
					if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
					//Puisque le nY n'�tait pas bon avant, on le v�rifie ici.
					//On est dans la derni�re v�rification.
					{
						tQTabEntreeJoueur[nIndex].nCouleurW=1;
					}
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
		//Si le nX et le nY ne sont pas bons, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurY=1;
			if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
			//Puisque le nX n'�tait pas bon avant, on le v�rifie ici.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
				//Puisque le nY n'�tait pas bon avant, on le v�rifie ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
		}
	}
	else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
	//Si le nW n'est pas bon, on v�rifie le nX, et comme le nX serait bon, on ne le v�rifie plus apr�s.
	{
		tQTabEntreeJoueur[nIndex].nCouleurX=2;
		if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
		//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurY=1;
			//nX et nW sont pris, on reprend donc le cas d'avant � ce m�me stade.
			if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
			//Si le nY de la solution est pris, on ne le v�rifie plus apr�s.
			{
				//On est en �galit� totale, donc on passe en couleur 2.
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
				//On est dans la derni�re v�rification.
				//Comme le nZ n'�tait pas bon avant, il peut l'�tre ici.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
			//Si le nY n'est pas bon, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=2;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
				//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
		}
		if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
		//Puisque nW et nX ne sont pas bons, on v�rifie nY, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurY=2;
			if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
				//Si le nZ n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
			//Si le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=2;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurW=2;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
		//Puisque le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurY=1;
			if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
				//Si le nY n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
			//Puisque le nW ne convient pas, on test le nZ qu'on ne v�rifie plus apr�s
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=2;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurW=2;
				}
			}
		}
	}
	else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
	//Si le nW et le nX ne sont pas bons, on v�rifie le nY, et comme le nY serait bon, on ne le v�rifie plus apr�s.
	{
		tQTabEntreeJoueur[nIndex].nCouleurX=1;
		if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
		//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurY=1;
			//nY et nW sont pris, on test donc nX.
			if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
			//Si le nX de la solution est pris, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
				//On est dans la derni�re v�rification.
				//Comme le nZ n'�tait pas bon avant, il peut l'�tre ici.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
			//Si le nX n'est pas bon, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=2;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
				//Comme le nX n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
		//Puisque nW et nY ne sont pas bons, on v�rifie nX, et si il est bon, on ne le v�rifie plus apr�s.
		{
			//On est en �galit� totale, la couleur passe � deux.
			tQTabEntreeJoueur[nIndex].nCouleurY=1;
			if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
				//Si le nZ n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
			//Si le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=2;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=2;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
		//Puisque le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurY=1;
			if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
				//Si le nX n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
			//Puisque le nW ne convient pas, on test le nX qu'on ne v�rifie plus apr�s
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=2;
				}
			}
		}
	}else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
	//Si le nW, le nX et le nY ne sont pas bons, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
	{
		tQTabEntreeJoueur[nIndex].nCouleurX=1;
		if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
		//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurY=1;
			//nY et nW sont pris, on test donc nX.
			if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
			//Si le nX de la solution est pris, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
				//On est dans la derni�re v�rification.
				//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
			//Si le nX n'est pas bon, on v�rifie le nY, et comme le nY serait bon, on ne le v�rifie plus apr�s.
			{
				//Egalit� totale, couleur=1.
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
				//Comme le nX n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
		//Puisque nW et nY ne sont pas bons, on v�rifie nX, et si il est bon, on ne le v�rifie plus apr�s.
		{
			//On est en �galit� totale, la couleur passe � deux.
			tQTabEntreeJoueur[nIndex].nCouleurY=1;
			if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
				//Si le nY n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
			//Si le nY n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				//Egalit� totale, couleur=1.
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurW=2;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
		//Puisque le nY n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurY=2;
			if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
				//Si le nX n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
			//Puisque le nW ne convient pas, on test le nX qu'on ne v�rifie plus apr�s
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=1;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=2;
				}
			}
		}
	}
	else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW) //Le cas du nY en principal
	//Si le nW de la solution est pris, on ne le v�rifie plus apr�s.
	{
		//On est en �galit� totale, donc on passe en couleur 2.
		tQTabEntreeJoueur[nIndex].nCouleurY=1;
		if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
		//Si le nX de la solution est pris, on ne le v�rifie plus apr�s.
		{
			//On est en �galit� totale, donc on passe en couleur 2.
			tQTabEntreeJoueur[nIndex].nCouleurZ=1;
			if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
			//Si le nY de la solution est pris, on ne le v�rifie plus apr�s.
			{
				//On est en �galit� totale, donc on passe en couleur 2.
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
			//Si le nY n'est pas bon, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
				//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
		//Si le nX n'est pas bon, on v�rifie le nY, et comme le nY serait bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurZ=1;
			//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
			if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
				//nW,nX et nY sont pos�s.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
			//Si le nX et le nY ne sont pas bons, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurZ=2;
				if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
				//Puisque le nX n'�tait pas bon avant, on le v�rifie ici.
				{
					tQTabEntreeJoueur[nIndex].nCouleurW=1;
					if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
					//Puisque le nY n'�tait pas bon avant, on le v�rifie ici.
					//On est dans la derni�re v�rification.
					{
						tQTabEntreeJoueur[nIndex].nCouleurX=1;
					}
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
		//Si le nX et le nY ne sont pas bons, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurZ=2;
			if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
			//Puisque le nX n'�tait pas bon avant, on le v�rifie ici.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
				//Puisque le nY n'�tait pas bon avant, on le v�rifie ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
		}
	}
	else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
	//Si le nW n'est pas bon, on v�rifie le nX, et comme le nX serait bon, on ne le v�rifie plus apr�s.
	{
		tQTabEntreeJoueur[nIndex].nCouleurY=1;
		if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
		//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurZ=1;
			//nX et nW sont pris, on reprend donc le cas d'avant � ce m�me stade.
			if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
			//Si le nY de la solution est pris, on ne le v�rifie plus apr�s.
			{
				//On est en �galit� totale, donc on passe en couleur 2.
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
				//On est dans la derni�re v�rification.
				//Comme le nZ n'�tait pas bon avant, il peut l'�tre ici.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
			//Si le nY n'est pas bon, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
				//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
		}
		if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
		//Puisque nW et nX ne sont pas bons, on v�rifie nY, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurZ=1;
			if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=2;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
				//Si le nZ n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
			//Si le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
		//Puisque le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurZ=2;
			if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=2;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
				//Si le nY n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
			//Puisque le nW ne convient pas, on test le nZ qu'on ne v�rifie plus apr�s
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
		}
	}
	else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
	//Si le nW et le nX ne sont pas bons, on v�rifie le nY, et comme le nY serait bon, on ne le v�rifie plus apr�s.
	{
		tQTabEntreeJoueur[nIndex].nCouleurY=2;
		if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
		//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurZ=1;
			//nY et nW sont pris, on test donc nX.
			if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
			//Si le nX de la solution est pris, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
				//On est dans la derni�re v�rification.
				//Comme le nZ n'�tait pas bon avant, il peut l'�tre ici.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
			//Si le nX n'est pas bon, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
				//Comme le nX n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=2;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
		//Puisque nW et nY ne sont pas bons, on v�rifie nX, et si il est bon, on ne le v�rifie plus apr�s.
		{
			//On est en �galit� totale, la couleur passe � deux.
			tQTabEntreeJoueur[nIndex].nCouleurZ=1;
			if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=2;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
				//Si le nZ n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
			//Si le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
		//Puisque le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurZ=2;
			if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=2;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
				//Si le nX n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=2;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
			//Puisque le nW ne convient pas, on test le nX qu'on ne v�rifie plus apr�s
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
		}
	}else if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
	//Si le nW, le nX et le nY ne sont pas bons, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
	{
		tQTabEntreeJoueur[nIndex].nCouleurY=1;
		if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW)
		//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurZ=1;
			//nY et nW sont pris, on test donc nX.
			if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
			//Si le nX de la solution est pris, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
				//On est dans la derni�re v�rification.
				//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
			//Si le nX n'est pas bon, on v�rifie le nY, et comme le nY serait bon, on ne le v�rifie plus apr�s.
			{
				//Egalit� totale, couleur=1.
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
				//Comme le nX n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=2;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
		//Puisque nW et nY ne sont pas bons, on v�rifie nX, et si il est bon, on ne le v�rifie plus apr�s.
		{
			//On est en �galit� totale, la couleur passe � deux.
			tQTabEntreeJoueur[nIndex].nCouleurZ=1;
			if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=2;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
				//Si le nY n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
			//Si le nY n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				//Egalit� totale, couleur=1.
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
		//Puisque le nY n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurZ=1;
			if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=2;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
				//Si le nX n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=2;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
			//Puisque le nW ne convient pas, on test le nX qu'on ne v�rifie plus apr�s
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=1;
				}
			}
		}
	}
	else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nW) //Le cas du nZ en principal
	//Si le nW de la solution est pris, on ne le v�rifie plus apr�s.
	{
		//On est en �galit� totale, donc on passe en couleur 2.
		tQTabEntreeJoueur[nIndex].nCouleurZ=1;
		if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
		//Si le nX de la solution est pris, on ne le v�rifie plus apr�s.
		{
			//On est en �galit� totale, donc on passe en couleur 2.
			tQTabEntreeJoueur[nIndex].nCouleurW=1;
			if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
			//Si le nY de la solution est pris, on ne le v�rifie plus apr�s.
			{
				//On est en �galit� totale, donc on passe en couleur 2.
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
			//Si le nY n'est pas bon, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
				//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=2;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
		//Si le nX n'est pas bon, on v�rifie le nY, et comme le nY serait bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurW=1;
			//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
			if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=2;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
				//nW,nX et nY sont pos�s.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
			//Si le nX et le nY ne sont pas bons, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurW=1;
				if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
				//Puisque le nX n'�tait pas bon avant, on le v�rifie ici.
				{
					tQTabEntreeJoueur[nIndex].nCouleurX=2;
					if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
					//Puisque le nY n'�tait pas bon avant, on le v�rifie ici.
					//On est dans la derni�re v�rification.
					{
						tQTabEntreeJoueur[nIndex].nCouleurY=2;
					}
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
		//Si le nX et le nY ne sont pas bons, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurW=1;
			if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
			//Puisque le nX n'�tait pas bon avant, on le v�rifie ici.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=2;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
				//Puisque le nY n'�tait pas bon avant, on le v�rifie ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=2;
				}
			}
		}
	}
	else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nX)
	//Si le nW n'est pas bon, on v�rifie le nX, et comme le nX serait bon, on ne le v�rifie plus apr�s.
	{
		tQTabEntreeJoueur[nIndex].nCouleurZ=1;
		if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
		//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurW=2;
			//nX et nW sont pris, on reprend donc le cas d'avant � ce m�me stade.
			if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
			//Si le nY de la solution est pris, on ne le v�rifie plus apr�s.
			{
				//On est en �galit� totale, donc on passe en couleur 2.
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
				//On est dans la derni�re v�rification.
				//Comme le nZ n'�tait pas bon avant, il peut l'�tre ici.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
			//Si le nY n'est pas bon, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
				//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=2;
				}
			}
		}
		if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
		//Puisque nW et nX ne sont pas bons, on v�rifie nY, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurW=1;
			if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
				//Si le nZ n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
			//Si le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
		//Puisque le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurW=1;
			if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
				//Si le nY n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurY=2;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
			//Puisque le nW ne convient pas, on test le nZ qu'on ne v�rifie plus apr�s
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
		}
	}
	else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nY)
	//Si le nW et le nX ne sont pas bons, on v�rifie le nY, et comme le nY serait bon, on ne le v�rifie plus apr�s.
	{
		tQTabEntreeJoueur[nIndex].nCouleurZ=1;
		if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
		//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurW=2;
			//nY et nW sont pris, on test donc nX.
			if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
			//Si le nX de la solution est pris, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=2;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
				//On est dans la derni�re v�rification.
				//Comme le nZ n'�tait pas bon avant, il peut l'�tre ici.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
			//Si le nX n'est pas bon, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
				//Comme le nX n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
		//Puisque nW et nY ne sont pas bons, on v�rifie nX, et si il est bon, on ne le v�rifie plus apr�s.
		{
			//On est en �galit� totale, la couleur passe � deux.
			tQTabEntreeJoueur[nIndex].nCouleurW=1;
			if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nZ)
				//Si le nZ n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nZ)
			//Si le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nZ)
		//Puisque le nZ n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurW=1;
			if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
				//Si le nX n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
			//Puisque le nW ne convient pas, on test le nX qu'on ne v�rifie plus apr�s
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=2;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
		}
	}else if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
	//Si le nW, le nX et le nY ne sont pas bons, on v�rifie le nZ, et comme le nZ serait bon, on ne le v�rifie plus apr�s.
	{
		tQTabEntreeJoueur[nIndex].nCouleurZ=2;
		if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
		//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurW=2;
			//nY et nW sont pris, on test donc nX.
			if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
			//Si le nX de la solution est pris, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=2;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
				//On est dans la derni�re v�rification.
				//Comme le nY n'�tait pas bon avant, il peut l'�tre ici.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=2;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
			//Si le nX n'est pas bon, on v�rifie le nY, et comme le nY serait bon, on ne le v�rifie plus apr�s.
			{
				//Egalit� totale, couleur=1.
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
				//Comme le nX n'�tait pas bon avant, il peut l'�tre ici.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nX)
		//Puisque nW et nY ne sont pas bons, on v�rifie nX, et si il est bon, on ne le v�rifie plus apr�s.
		{
			//On est en �galit� totale, la couleur passe � deux.
			tQTabEntreeJoueur[nIndex].nCouleurW=1;
			if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
				//Si le nY n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=2;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nY)
			//Si le nY n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				//Egalit� totale, couleur=1.
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					//On est en �galit� totale, donc on passe en couleur 2.
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
		}
		else if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nY)
		//Puisque le nY n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
		{
			tQTabEntreeJoueur[nIndex].nCouleurW=1;
			if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nW)
			//Si le nW n'�tait pas bon avant, on le test � pr�sent, et si il est bon, on ne le v�rifie plus apr�s.
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=1;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nX)
				//Si le nX n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
			else if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
			//Puisque le nW ne convient pas, on test le nX qu'on ne v�rifie plus apr�s
			{
				tQTabEntreeJoueur[nIndex].nCouleurX=2;
				if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nW)
				//Si le nW n'�tait pas bon avant, on le test � pr�sent.
				//On est dans la derni�re v�rification.
				{
					tQTabEntreeJoueur[nIndex].nCouleurY=1;
				}
			}
		}
	}


	//On rajoute �a pour �tre s�r de ce qu'on a fait. 
	if (tQTabEntreeJoueur[nIndex].nW==tQSolution.nW)
	{
		tQTabEntreeJoueur[nIndex].nCouleurW=2;
	}
	if (tQTabEntreeJoueur[nIndex].nX==tQSolution.nX)
	{
		tQTabEntreeJoueur[nIndex].nCouleurX=2;
	}
	if (tQTabEntreeJoueur[nIndex].nY==tQSolution.nY)
	{
		tQTabEntreeJoueur[nIndex].nCouleurY=2;
	}
	if (tQTabEntreeJoueur[nIndex].nZ==tQSolution.nZ)
	{
		tQTabEntreeJoueur[nIndex].nCouleurZ=2;
	}
}

//Mise en place de la donn�e.

void random(int *nAlea,int nImpossibleA,int nImpossibleB,int nImpossibleC)
//BUT : G�n�rer un nombre al�atoire compris entre 0 et 9999.
//ENTREE : Un entier � qui donner la valeur al�atoire.
//SORTIE : L'entier modifi�.
{
	while ((*nAlea==nImpossibleA)||(*nAlea==nImpossibleB)||(*nAlea==nImpossibleC)||(*nAlea==-1))
	{
		srand(time(NULL));
   		*nAlea=rand()%10;
	}
}


void creationQuatuorMasterMind(tQuatuorMasterMind *tQuatuor)
//BUT : Cr�er la Solution al�atoire du Master Mind.
//ENTREE : Un type structur� tQuatuorMasterMind � initialiser.
//SORTIE : Le type structur� tQuatuorMasterMind initialis�.
{
    //int nSolution=0,
    //On n'en a plus besoin

    int nSolutionW=-1,nSolutionX=-1,nSolutionY=-1,nSolutionZ=-1;
    //On cr�e la solution
    random(&nSolutionW,nSolutionX,nSolutionY,nSolutionZ);
    random(&nSolutionX,nSolutionY,nSolutionZ,nSolutionW);
    random(&nSolutionY,nSolutionZ,nSolutionW,nSolutionX);
    random(&nSolutionZ,nSolutionW,nSolutionX,nSolutionY);

    //printf("La solution est : %d avant de passer dans le type structure.\n",nSolution);

    //On d�coupe la solution.
    //decomposition9999(nSolution,&nSolutionW,&nSolutionX,&nSolutionY,&nSolutionZ);
    //On n'en a plus besoin.

    //On pose la solution dans le type structur�.
    *tQuatuor=creattQ(nSolutionW,nSolutionX,nSolutionY,nSolutionZ);
}

tQuatuorMasterMind creattQ(int nA,int nB,int nC,int nD)
//BUT : Cr�er un type structur� tQuatuorMasterMind.
//ENTREE : 4 entier pour les 4 valeurs du tQuatuorMasterMind.
//SORTIE : Le TQuaturoMasterMind.
{
    tQuatuorMasterMind tQCreation;
    setW(&tQCreation,nA);
    setX(&tQCreation,nB);
    setY(&tQCreation,nC);
    setZ(&tQCreation,nD);
    setCouleurW(&tQCreation,0);
    setCouleurX(&tQCreation,0);
    setCouleurY(&tQCreation,0);
    setCouleurZ(&tQCreation,0);
    return tQCreation;
}

void decomposition9999(int nDecomp,int *nMillier,int *nCentaine,int *nDizaine,int *nUnite)
//BUT : D�composer un nombre en ses 4 chiffres.
//ENTREE : Un entier inf�rieur � 10 000 et sup�rieur � -1, ainsi que 4 adresse pour y mettre les 4 chiffres composant notre entier de base.
//SORTIE : Les 4 entiers correspondants aux adresses modifier pour porter les milliers, centaines, dizaines et unit�s.
{
    if (nDecomp<10000 && nDecomp>=0)
    {
        *nMillier=(nDecomp/1000);
        *nCentaine=((nDecomp%1000)/100);
        *nDizaine=((nDecomp%100)/10);
        *nUnite=(nDecomp%10);
    }
    else
    {
        printf("L'entier %d renseigne n'est pas compris entre 0 et 9999.\n",nDecomp);
    }
}

//Les Mutateurs.

void setW(tQuatuorMasterMind *tQ,int nInt)
{
    tQ->nW=nInt;
}
void setX(tQuatuorMasterMind *tQ,int nInt)
{
    tQ->nX=nInt;
}
void setY(tQuatuorMasterMind *tQ,int nInt)
{
    tQ->nY=nInt;
}
void setZ(tQuatuorMasterMind *tQ,int nInt)
{
    tQ->nZ=nInt;
}
void setCouleurW(tQuatuorMasterMind *tQ,int nInt)
{
    tQ->nCouleurW=nInt;
}
void setCouleurX(tQuatuorMasterMind *tQ,int nInt)
{
    tQ->nCouleurX=nInt;
}
void setCouleurY(tQuatuorMasterMind *tQ,int nInt)
{
    tQ->nCouleurY=nInt;
}
void setCouleurZ(tQuatuorMasterMind *tQ,int nInt)
{
    tQ->nCouleurZ=nInt;
}

//Les Accesseurs.

int getW(tQuatuorMasterMind tQ)
{
    return tQ.nW;
}
int getX(tQuatuorMasterMind tQ)
{
    return tQ.nX;
}
int getY(tQuatuorMasterMind tQ)
{
    return tQ.nY;
}
int getZ(tQuatuorMasterMind tQ)
{
    return tQ.nZ;
}
int getCouleurW(tQuatuorMasterMind tQ)
{
    return tQ.nCouleurW;
}
int getCouleurX(tQuatuorMasterMind tQ)
{
    return tQ.nCouleurX;
}
int getCouleurY(tQuatuorMasterMind tQ)
{
    return tQ.nCouleurY;
}
int getCouleurZ(tQuatuorMasterMind tQ)
{
    return tQ.nCouleurZ;
}
