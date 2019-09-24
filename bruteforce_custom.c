#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fisierExista(char nume_fisier[20]){
	FILE *fisier;
	fisier = fopen(nume_fisier, "rt");
	if(fisier != NULL){
		fclose(fisier);
		return 1;
	}
	else return 0;
}

void creazaUnFisier(char nume_fisier[20]){
	FILE *fisier;
	fisier = fopen(nume_fisier, "wt");
	fclose(fisier);
}

int fisierGol(char nume_fisier[20]){
	FILE *fisier;
	fisier = fopen(nume_fisier, "rt");
	fseek(fisier, 0, SEEK_END);
	if(ftell(fisier) == 0)
	{
		fclose(fisier);
		return 0;
	}
	else {
		fclose(fisier);
		return 1;
		 }
}

void printeazaActiunile(){
	printf("* Alege o comanda *\n");
	printf("1 - Afiseaza un fisier (Dureaza mult!)\n");
	printf("2 - Construieste un fisier nou cu setari DEFAULT\n");
	printf("3 - Construieste un fisier nou cu setari CUSTOM\n");
	printf("4 - Deschide / Creaza un fisier nou\n");
	printf("0 - Iesi din program\n\n");
}

void afiseazaFisier(char nume_fisier[20]){
	FILE *fisier;
	fisier = fopen(nume_fisier, "rt");
	char parola[30];
	fseek(fisier, 0, SEEK_END);
	if(ftell(fisier) == 0)
		printf("* Fisier-ul este GOL *\n\n\n");
	else {
	fseek(fisier, 0, SEEK_SET);
	while(feof(fisier) == 0)
	{
		fscanf(fisier," %s", parola);
		printf("%s\n", parola);
	}
	}
	fclose(fisier);
}

void fisierDefault(char nume_fisier[20]){
	printf("! Acest tip de fisier dureaza foarte mult !\n");
	long long int x;
	printf("    ! Dati o limita de parole generate !\n");
	scanf("%llu",&x);
	int i, j, k, n = 6;
	char *parola;
	parola = (char *)malloc(7 * sizeof(char));
	FILE *fisier;
	fisier = fopen(nume_fisier, "wt");
	for(i = 0; i < n; i++){
		parola[i] = 33;
	}
	parola[n] = '\0';
	for(i = 0; i < x; i++){
		if(parola[n - 1] != 126)
		parola[n - 1]++;
		else {
			parola[n - 1] = 33;
			parola[n - 2]++;

			   for(j = n - 2; j >= 0; j--)
			   	if(parola[j] == 127){
			   		parola[j] = 33;
			   		if(j == 0){
			   			parola = (char *)realloc(parola, n+2);
			   			n++;
			   			for(k = 0; k < n; k++)
			   				parola[k] = 33;
			   			parola[n] = '\0';
			   		}else parola[j - 1]++;
			   	}else break;
			 }
		fprintf(fisier, "%s\n", parola);
	}
	free(parola);
	fprintf(fisier, " * Sunt %llu parole *",x);
	printf("! GATA SEFU !\n\n\n");
	fclose(fisier);

}


void fisierCustom(char nume_fisier[20]){
	int i, j, k, n, min, max, nr;
	printf("* Dati numarul minim de caractere *\n");
	scanf("%d", &min);
	printf("* Dati numarul maxim de caractere *\n");
	scanf("%d", &max);
	printf("* Dati caracterele dorite *\n");
	char caractere[100];
	scanf("%s", caractere);
	n = min;
	nr = strlen(caractere)-1;
	caractere[nr + 1] = '*';
	int *pozlit;
	pozlit = (int *)calloc(max, sizeof(int));
	char *parola;
	parola = (char *)malloc((n + 1) * sizeof(char));
	for(i = 0; i < n; i++)
		parola[i] = caractere[0];
	parola[n] = '\0';
	FILE *fisier;
	fisier = fopen(nume_fisier,"wt");
	fprintf(fisier,"%s\n",parola);

	while(n<=max){
		if(parola[n - 1] != caractere[nr]){
				pozlit[n - 1]++;
				parola[n - 1] = caractere[pozlit[n-1]];
			} else{
				pozlit[n - 1] = 0;
				parola[n - 1] = caractere[0];
				pozlit[n - 2]++;
				parola[n - 2] = caractere[pozlit[n-2]];
				for(j = n - 2; j >= 0; j--){
					if(parola[j] == caractere[nr + 1]){
						parola[j] = caractere[0];
						pozlit[j] = 0;
					if(j == 0){
						parola = (char *)realloc(parola, n + 2);
			   			n++;
			   			for(k = 0; k < n; k++){
			   				parola[k] = caractere[0];
			   				pozlit[k] = 0;
			   			}
			   			parola[n] = '\0';
					}	else {
							pozlit[j - 1]++;
							parola[j - 1] = caractere[pozlit[j - 1]];
						}
				  }else break;

			}
		}

			if(n <= max)
			fprintf(fisier, "%s\n", parola);


}
	printf("\n\n* Gata sefu! *\n\n\n");
	free(pozlit);
	free(parola);
	fclose(fisier);
}

int main(){
	int i, j, k, min, max;
	int *litera;
	char nume_fisier[20];
	fisnou:
	printf("* Introdu numele fisierului, maxim 19 caractere *\n");
	scanf("%s", nume_fisier);
	if(fisierExista(nume_fisier) == 0){
		printf("* Fisierul nu exista, dar a fost creat *\n");
		creazaUnFisier(nume_fisier);
	}else if(fisierGol(nume_fisier) == 1)
		printf("* Fisier exista deja si contine ceva *\n");
	 else printf("  * Fisier exista dar este gol *\n");

	int comanda = -1;


	while(comanda != 0){
		printeazaActiunile();
		scanf("%d", &comanda);
		if(comanda == 1){
			afiseazaFisier(nume_fisier);
		}
		else if(comanda == 2){
			fisierDefault(nume_fisier);
		}
		else if(comanda == 3){
			fisierCustom(nume_fisier);
		}
		else if(comanda == 4){
			goto fisnou;
		}
	}
	system("cls");
    printf("    ********************\n");
    printf("    *  Made by Mircea  *\n");
    printf("    ********************\n");


	 return 0;
}
