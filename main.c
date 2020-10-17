#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
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
//======================================================================
Trinom *ajout(){
	char nom[TAILLNOM], login[TAILLLOGIN], mdp[TAILLMOTDEPASS];//,valide;
	
	printf("nom:");
	scanf("%s",nom);
	printf("login:");
	scanf("%s",login);
	printf("mot de passe:");
	scanf("%s",mdp);
	//printf("valider la saisi (y/n):");
	//check saisie str cmp	

	return alloue(nom,login,mdp);
}
//======================================================================
//======================================================================
void afficher(Trinom afficher){
	printf("nom :%s\n",afficher.nom);
	printf("	login:%s\n",afficher.login);
	printf("	mdp:%s\n",afficher.mdp);
}
//======================================================================
//======================================================================
void affichernom(Trinom afficher){
	printf("nom :%s\n",afficher.nom);
}
//======================================================================
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
//======================================================================
Trinom *extraire(char *filename){
	FILE *fd;
	fd=fopen(filename,"r");
	
	if(fd==NULL){//le fichier de vault n'est pas le bon
		printf("fichier introuvable \n");
		return NULL;
	}
	//ouvrir la vault
	printf("fichier ouvert \n");
	
	Trinom *tri=(Trinom*)malloc(100*sizeof(Trinom));
	
	int i=0;
	char ligne[TAILLBUFFER];
	while(fgets(ligne,TAILLBUFFER, fd)){
		tri[i]=*extraire_ligne(ligne);
		afficher(tri[i]);
		i++;
	}
	
	fclose(fd);	

	return tri;
}
//======================================================================
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
}
//======================================================================
//======================================================================
void encrypt_decrypt(){
	//le nom est utiliser comme vecteur d'initialisation 
	char nom[20];
	printf("hello\n");
	printf("c'est quoi ton nom:");
	scanf("%s",nom);
	
	
	char* buffer= (char*)malloc(TAILLBUFFER*sizeof(char));
	//-----------------
	printf("===============\n");
	snprintf(buffer,TAILLBUFFER , "openssl enc -e -a -aes-128-cbc -iv \"%d\" -iter 100 -in tmp -out plain.enc",make_vector(nom));
	printf("here=%s",buffer);
	printf("hello %d",(system(buffer)));
	printf("===============\n");
	//-----------------
	snprintf(buffer,TAILLBUFFER , "cat texteenchiffrer");
	system(buffer);
	printf("===============\n");
	//-----------------
	snprintf(buffer,TAILLBUFFER , "openssl enc -d -a -aes-128-cbc -iv \"%d\" -iter 100 -in plain.enc -out claire.txt",make_vector(nom));
	system(buffer);
	printf("===============\n");
}
//======================================================================
//======================================================================
int main(int argc, char *argv[]){
	//extraire(argv[1]);
	encrypt_decrypt();

	
	return(0);
}
