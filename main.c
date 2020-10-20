#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLNOM 100
#define TAILLLOGIN 100
#define TAILLMOTDEPASS 200
#define TAILLBUFFER 402


typedef struct trinom{
	char nom[TAILLNOM];
	char login[TAILLLOGIN];
	char mdp[TAILLMOTDEPASS];
}Trinom;
//======================================================================
Trinom *alloue(char *nom, char *login, char *mdp){
	Trinom *tmp=(Trinom*)malloc(sizeof(Trinom));
	if (tmp==NULL) return NULL;
	strcpy(tmp->nom,nom);
	strcpy(tmp->login,login);
	strcpy(tmp->mdp,mdp);
	return tmp;
}
//======================================================================
Trinom *ajout(){
	char nom[TAILLNOM], login[TAILLLOGIN], mdp[TAILLMOTDEPASS];//,valide;
	
	printf("nom:");
	scanf("%s",nom);
	printf("login:");
	scanf("%s",login);
	printf("mot de passe:");
	scanf("%s",mdp);
	//printf("Valider la saisie (o/n):");
	//check saisie str cmp	

	return alloue(nom,login,mdp);
}
//======================================================================
void afficher_mdp(Trinom afficher){
	if (afficher.nom[0]=='\0')
		return;
	printf("nom :%s\n",afficher.nom);
	printf("	login:%s\n",afficher.login);
	printf("	mdp:%s\n",afficher.mdp);
}
//======================================================================
void afficher_nom(Trinom afficher,int valeur){
	if (afficher.nom[0]=='\0')
		return;
	printf("%d) nom :%s\n",valeur,afficher.nom);
}
//======================================================================
void afficher_list(Trinom afficher[]){
	printf("===========================\n");
	for(int i=0;i<100;++i)
		afficher_nom(afficher[i],i);
	printf("===========================\n\n");
}
//======================================================================
void afficher_select(Trinom afficher[]){
	int select;
	printf("=======================================\n");
	printf("Sélectionner le numéro de l'identifiant/mdp que vous voulez voir :");
	scanf("%d",&select);
	printf("=======================================\n");
	afficher_mdp(afficher[select]);
	printf("=======================================\n\n");
}
//======================================================================
void ajout_select(Trinom tri[]){
	int i=0;
	for(;i<100;++i)
		if (tri[i].nom[0]=='\0')
			break;
	tri[i]=*ajout();	
}
//======================================================================
Trinom *extraire_ligne(char ligne[]){
	char tmpnom[TAILLNOM];
	char tmplogin[TAILLLOGIN];
	char tmpmdp[TAILLMOTDEPASS];
	int k=0,j=0-1;	
	
	for(int i =-1;k<=2;){
		++i;
		++j;
		if(ligne[i]=='\0'||ligne[i]=='\n'){
			break;
		}
		if(ligne[i]==','){
			++k;
			++i;
			j=0;
		}			
		if(k==0){
			tmpnom[j]=ligne[i];
			tmpnom[j+1]='\0';
		}
		if(k==1){
			tmplogin[j]=ligne[i];
			tmplogin[j+1]='\0';			
		}
		if(k==2){
			tmpmdp[j]=ligne[i];
			tmpmdp[j+1]='\0';		
		}
	}
	Trinom *tri =alloue(tmpnom,tmplogin,tmpmdp);
	return tri;
}
//======================================================================
Trinom *extraire(char *filename){
	FILE *fd;
	fd=fopen(filename,"r");
	
	if(fd==NULL){//le fichier de vault n'est pas le bon
		printf("Fichier introuvable \n");
		return NULL;
	}
	//ouvrir la vault
	printf("Fichier ouvert \n");
	
	Trinom *tri=(Trinom*)malloc(100*sizeof(Trinom));
	for(int i=0;i<100;++i)
		tri[i].nom[0]='\0';
		
	int i=0;
	char ligne[TAILLBUFFER];
	while(fgets(ligne,TAILLBUFFER, fd)){
		tri[i]=*extraire_ligne(ligne);
		i++;
	}
	
	fclose(fd);	

	return tri;
}
//======================================================================
int make_vector(char mot[]){
	int total=0;
	int i=0;
	while(mot[i]!='\0'){
		total+=(i+1)*mot[i];
		++i;
	}
	return total;
}

void test_make_vector(){
	printf("bob=%d\n",make_vector("bob"));
	printf("aob=%d\n",make_vector("aob"));
	printf("boa=%d\n",make_vector("boa"));
	printf("alice=%d\n",make_vector("alice"));
	printf("aliceetbob=%d\n",make_vector("aliceetbob"));
	printf("tmp=%d\n",make_vector("tmp"));
}
//======================================================================
void encrypt(char nom[]){
	char* buffer= (char*)malloc(TAILLBUFFER*sizeof(char));
	printf("===============\n");
	snprintf(buffer,TAILLBUFFER , "openssl enc -e -a -aes-128-cbc -iv \"%d\" -iter 100 -in %s.txt -out %s.enc",make_vector(nom),nom,nom);
	(system(buffer));
	printf("===============\n");	
}
//======================================================================
int decrypt(char nom[]){
	char* buffer= (char*)malloc(TAILLBUFFER*sizeof(char));
	int returnvalue=-1;
	printf("===============\n");
	snprintf(buffer,TAILLBUFFER , "openssl enc -d -a -aes-128-cbc -iv \"%d\" -iter 100 -in %s.enc -out %s.txt",make_vector(nom),nom,nom);
	returnvalue=system(buffer);
	printf("===============\n");
	return returnvalue;
}
//======================================================================
void clear(char nom[]){
	char* buffer= (char*)malloc(TAILLBUFFER*sizeof(char));
	//todo mettre shred
	snprintf(buffer,TAILLBUFFER , "rm %s",nom);
	system(buffer);
}
//======================================================================
void to_txt(char nom[],Trinom tri[]){
	char *name=(char*)malloc(TAILLBUFFER*sizeof(char));
	snprintf(name, TAILLBUFFER, "./%s.txt",nom);//+.txt
	
	char* buffer= (char*)malloc(TAILLBUFFER*sizeof(char));
	snprintf(buffer,TAILLBUFFER , "touch %s",name);
	system(buffer);
	
	FILE *fd;
	fd=fopen(name,"w");
	
	for(int i=0;i<100;++i){
		if (tri[i].nom[0]=='\0'){
			break;
		}
		fprintf(fd,"%s,%s,%s\n",tri[i].nom,tri[i].login,tri[i].mdp);
	}
	fclose(fd);
}
//======================================================================
void save_and_quit(char nom[],Trinom vault[]){
	to_txt(nom,vault);
	encrypt(nom);
	char *name=(char*)malloc(TAILLBUFFER*sizeof(char));
	snprintf(name, TAILLBUFFER, "%s.txt",nom);//+.txt
	clear(name);	
	exit(0);
}
//======================================================================
Trinom *start(char nom []){
	char select[10];
	select[0]='\0';
	printf("Déchiffer la vault (o/n)?");
	scanf("%s",select);
	if(select[0]=='0'||select[0]=='O'||select[0]=='o'){
		int bool=decrypt(nom);
		if (bool!=0){
			printf("#####\n#####\n#####\n#####\n#####\n");
			printf("Bad decrypt retry\n");
			printf("#####\n");
			return (start(nom));
		}
		char* buffer= (char*)malloc(TAILLBUFFER*sizeof(char));
		snprintf(buffer,TAILLBUFFER , "%s.txt",nom);
		Trinom* tri= extraire(buffer);
		clear(buffer);
		
		return tri;
	}
	printf("Au revoir");
	exit(0);
}
//======================================================================
void menu(char nom [],Trinom vault[]){
	int select;
	select=0;
	while(1){
		printf("=======================================\n");
		printf("1: Afficher la liste\n");
		printf("2: Afficher l'identifiant/mot de passe\n");
		printf("3: Ajouter un identifiant/mot de passe\n");
		printf("4: Supprimer une entrée\n");
		printf("5: Sauvegarder et quitter\n");
		printf("6: Quitter (les modifications seront perdues)\n");
		printf("Sélectionner le mode avec le numéro :");
		scanf("%d",&select);
	
		if(select==1){
			afficher_list(vault);
		}
		else if(select==2){
			afficher_select(vault);
		}
		else if(select==3){
			ajout_select(vault);
		}
		else if(select==4){
			printf("44\n");//todo
		}
		else if(select==5){
			save_and_quit(nom,vault);
		}
		else if(select==6){
			exit(0);
		}
	}
	return;
}
//======================================================================
int main(){
	char nom[TAILLBUFFER];
	printf("Passworld - Gestionnaire de mot de passe - v0.9\n");//TODO metre un message d'acueille un peux mieux =)
	printf("Entrez un nom :");
	scanf("%s",nom);
	//-------
	Trinom *vault=start(nom);
	menu(nom,vault);
	
	return(0);
}
