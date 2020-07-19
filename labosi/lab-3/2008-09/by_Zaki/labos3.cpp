/* UTR labos3 2008/09 by Zaki

3. Zadatak Programski ostvariti aplikaciju za odre�ivanje prostorne i vremenske slo�enosti deterministi�kog Turingovog stroja s jednom trakom koja je beskona�na na obje strane. Aplikacija za zadani Turingov stroj i zadani niz zapisan na traci odre�uje prostornu i vremensku slo�enost prihva�anja niza.
Prostornu slo�enost Turingovog stroja izraziti brojem kori�tenih �elija trake, a vremensku brojem pomaka glave za �itanje i pisanje.
Aplikacija na po�etku izvo�enja u�itava sljede�e podatke:
1) funkciju prijelaza Turingovog stoja iz ulazne datoteke

    Funkcija prijelaza Turingovog stroja zadaje se ulaznom datotekom prema sljede�em formatu:
    stanje#znak_na_traci#novo_stanje#novi_znak_na_trac i#smjer_pomaka_glave
    Oznake stanja mogu biti proizvoljni nizovi znakova. Za znakove trake koriste se pojedina�ni znakovi. Prazna �elija ozna�ava se oznakom B. Smjerovi pomaka glave su D za pomak u desno, odnosno L za pomak u lijevo. Primjer datoteke s funkcijom prijelaza (primjer 4.1 u ud�beniku):
    0
    0#0#1#X#D
    1#0#1#0#D
    2#0#2#0#L
    1#1#2#Y#L
    2#X#0#X#D
    0#Y#3#Y#D
    1#Y#1#Y#D
    2#Y#2#Y#L
    3#Y#3#Y#D
    3#B#4#B#D

2) niz zapisan na traci od korisnika
3) po�etni polo�aj glave za �itanje i pisanje od korisnika

    Polo�aj glave zadaje se broj�anom oznakom koja odre�uje poziciju �elije na kojoj se nalazi glava u odnosu na �eliju u kojoj je zapisan krajnje lijevi znak ulaznog niza. Primjeri zadavanja polo�aja glave:

        * 0 - �elija u kojoj je zapisan krajnje lijevi znak ulaznog niza

        * 1 - �elija u kojoj je zapisan drugi znak ulaznog niza
        * N - �elija koja se nalazi N mjesta desno od �elije u kojoj je zapisan krajnje lijevi znak ulaznog niza

        * -1 - �elija neposredno lijevo od �elije u kojoj je zapisan krajnje lijevi znak ulaznog niza
        * -N - �elija koja se nalazi N mjesta lijevo od �elije u kojoj je zapisan krajnje lijevi znak ulaznog niza

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

FILE *tablica;

char ulazniNiz[255];
char pomTraka[2];
int obradjenihCelija=0;
int maxVelicina;

int pocetnaGlava;
int trenutnaGlava;
char trenutniZnak;
int pocetnoStanje;
int trenutnoStanje;
int korak=0;
int ucinjenaPromjenaNaTraci=0;


char nadjiPrijelaz(){
     int stanje;
     char znak_na_traci;
     int novo_stanje;
     char novi_znak_na_traci;
     char smjer_pomaka_glave;
     char ucitavajPrijelaze=1;                            //koristimo za petlju; ucitavat cemo znak za novi red, ili jos bitnije znak EOF
     char postavke[6]; 
     
     tablica=fopen("tablica.txt","r");
     fscanf(tablica,"%s\n",postavke);                     //ovime samo preskacemo prvi red u kojem je zapisano pocetno stanje

     while(ucitavajPrijelaze!=EOF){                       //vrtimo petlju dok ne ocitamo sve moguce prijelaze iz datoteke (ili dok se ne nadje prijelaz)
          fscanf(tablica,"%d#%c#%d#%c#%c",&stanje,&znak_na_traci,&novo_stanje,&novi_znak_na_traci,&smjer_pomaka_glave);
          ucitavajPrijelaze = getc(tablica);              //nakon pro�itanog reda, u�itavamo ili znak za novi red, ili EOF. fscanf ne mo�e pro�itati EOF pa koristimo getc()
          
          if( (stanje==trenutnoStanje) && (znak_na_traci==trenutniZnak) ){ //ako se poklopi da su trenutno stanje i trenutni znak na traci jednaki onima za koje je definiran prijelaz u tablici, radimo prijelaz 
             if(trenutniZnak!=novi_znak_na_traci) ucinjenaPromjenaNaTraci++;
             ucitavajPrijelaze=0;
             fclose(tablica);
             printf("\tprijelaz: (q%d,%c)=(q%d,%c,%c)\n",stanje,znak_na_traci,novo_stanje,novi_znak_na_traci,smjer_pomaka_glave);
             trenutnoStanje=novo_stanje;
             trenutniZnak=novi_znak_na_traci;
             
             return smjer_pomaka_glave;                  //vracamo smjer u kojem cemo pozicionirati glavu
          }
     }
     fclose(tablica);
     return 0;                                           //ako nije nadjen prijelaz, vrati nulu
}

int main(){
    int i=0,j=0;
    char smjer=1;
    char postavke[100];
    char * traka;
    char * obradjeneCelije;
        
    tablica=fopen("tablica.txt","r");                    //otvaramo datoteku s podacima
    fscanf(tablica,"%s\n",postavke);                     //�itamo po�etno stanje
    pocetnoStanje=atoi(postavke);                        //smje�tamo po�etno stanje u varijablu pocetnoStanje
    trenutnoStanje=pocetnoStanje;                        //za trenutno stanje stavljamo ono po�etno
    fclose(tablica);
    
    /*  ULAZNI NIZ IZ DATOTEKE
    FILE *ulazna;
    ulazna=fopen("ulaz.txt","r");
    fscanf(ulazna,"%s",ulazniNiz); 
    fclose(ulazna);
    */
    
    printf("Upisite ulazni niz: ");
    scanf("%s",ulazniNiz);
    printf("Upisite pocetni smjestaj glave: ");
    scanf("%d",&pocetnaGlava);
    
    if(pocetnaGlava<0){                                                                 //u slu�aju da je glava na po�etku lijevo od niza na traci
                      maxVelicina=2+ abs(pocetnaGlava) +strlen(ulazniNiz) +2+1;         //velicina trake s kojom cemo raditi
                      traka = (char*) malloc ( sizeof(char)*maxVelicina );              //alociramo memoriju za traku
                      obradjeneCelije = (char*) malloc ( sizeof(char)*maxVelicina );    //alociramo memoriju za marker koristenih celija
                      for(i=0; i<(2+abs(pocetnaGlava)); i++){                           //sve �elije do po�etka niza punimo znakovima 'B'
                               traka[i]='B';
                               }
                      for(; i<(2+abs(pocetnaGlava)+strlen(ulazniNiz)); i++){            //upisujemo niz na traku
                                                   traka[i]=ulazniNiz[j];
                                                   j++;
                                                   }
                      for(; i<(2+abs(pocetnaGlava)+strlen(ulazniNiz)+2); i++)           //iza trake ostavljamo dvije �elije sa znakovima 'B'
                            { traka[i]='B'; }
                      traka[i]='\0';
                      
                      trenutnaGlava=2;                    //pozicioniramo glavu na mjesto koje smo zadali (reminder: 0 i 1 zauzimaju znakovi 'B')                                         
                      }
    else if( pocetnaGlava>strlen(ulazniNiz) ){                            //u slu�aju da je na po�etku glava pozicionirana desno od niza na traci
         maxVelicina=2+ pocetnaGlava +2+1;                                //velicina trake s kojom cemo raditi
         traka = (char*) malloc ( sizeof(char)*maxVelicina );             //alociramo memoriju za traku
         obradjeneCelije = (char*) malloc ( sizeof(char)*maxVelicina );   //alociramo memoriju za marker koristenih celija
         for(i=0; i<2; i++){ traka[i]='B'; }                              //sve �elije do po�etka niza punimo znakovima 'B'
         for(; i<(2+strlen(ulazniNiz)); i++){                             //upisujemo niz na traku
                  traka[i]=ulazniNiz[j];
                  j++;
                  }
         for(; i<=(2+pocetnaGlava+2); i++){                               //ostatak trake punimo znakovima 'B'
                                         traka[i]='B';
                                         }
         traka[i]='\0';
         
         trenutnaGlava=2+pocetnaGlava; //pozicioniramo glavu na mjesto koje smo zadali (reminder: 0 i 1 zauzimaju znakovi 'B', mjesto 2 je po�etak samog niza) 
         }
    else {                                                             //u slu�aju da je na po�etku glava negdje na nizu
         maxVelicina=2+ strlen(ulazniNiz) +2+1;                        //velicina trake s kojom cemo raditi
         traka = (char*) malloc ( sizeof(char)*maxVelicina );          //alociramo memoriju za traku
         obradjeneCelije = (char*) malloc ( sizeof(char)*maxVelicina );//alociramo memoriju za marker koristenih celija
         for(i=0; i<2; i++) { traka[i]='B'; }                          //sve �elije do po�etka niza punimo znakovima 'B'
         for(; i<(2+strlen(ulazniNiz)); i++){                          //upisujemo niz na traku
                  traka[i]=ulazniNiz[j];
                  j++;
                  }
         for(; i<(2+strlen(ulazniNiz)+2); i++){ traka[i]='B'; }        //ostatak trake punimo znakovima 'B'
         traka[i]='\0';
         
         trenutnaGlava=2+pocetnaGlava;
         }
    
    for(i=0; i<=maxVelicina; i++) obradjeneCelije[i]=0;                //postavljamo da nijedna �elija jo� nije obra�ivana

    while(smjer){
                 obradjeneCelije[trenutnaGlava]=1;                     //zapisujemo da je trenutna �elija bila obra�ivana
                 trenutniZnak=traka[trenutnaGlava];                    //pamtimo znak s trenutne �elije za kasniju usporedbu
                 korak++;
                 
                 /* ISPIS: */
                 //printf("\nKORAK: %d\n",korak);
                 printf("\nGLAVA:\t "); for(i=0; i<trenutnaGlava; i++){printf(" ");}printf("X\n");
                 printf("TRAKA:\t~%s~\t\t",traka);
                 
                 smjer=nadjiPrijelaz();                               //tra�imo prijelaz za trenutne podatke
                 
                 traka[trenutnaGlava]=trenutniZnak;                   //upisujemo novi znak na trenutno mjesto
                 
                 if(smjer=='L') trenutnaGlava--;                      //premje�tamo glavu ulijevo ukoliko je u prijelazu tako zadano
                 else if((smjer=='D')||(smjer=='R')) trenutnaGlava++; //premje�tamo glavu udesno ukoliko je u prijelazu tako zadano
                 else if(smjer==0) break;                             //prijelaz ne postoji stoga izlazimo iz petlje i zavr�avamo program
                 
                 if(trenutnaGlava==(maxVelicina-2)){                  //u slu�aju da smo do�li skroz desno na traci, tj. do zadnjeg polja u memoriji, �irimo memoriju
                                                maxVelicina++;        //pove�avamo max broj �elija na radnoj traci
                                                traka = (char*) realloc (traka, sizeof(char)*(maxVelicina+1)); //radimo realokaciju memorije za traku za novu veli�inu
                                                traka[maxVelicina]='\0'; 
                                                traka[maxVelicina-1]='B'; 
                                                traka[maxVelicina-2]='B'; //punimo nove �elije znakovima 'B';
                                                obradjeneCelije = (char*) realloc (obradjeneCelije, sizeof(char)*(maxVelicina+1) ); //realociramo memoriju za marker
                                                obradjeneCelije[maxVelicina-1]=0;
                                                obradjeneCelije[maxVelicina]=0;
                                                }
                 if(trenutnaGlava==0){ //u slu�aju da smo do�li skroz lijevo na traci, tj. do zadnjeg polja u memoriji, �irimo memoriju
                                      maxVelicina++;                                              //pove�avamo max broj �elija na radnoj traci
                                      traka = (char*) realloc (traka, sizeof(char)*maxVelicina);  //radimo realokaciju memorije za traku za novu veli�inu
                                      traka[maxVelicina]='\0';
                                      for(i=(maxVelicina-1); i>0; i--) { traka[i-1]=traka[i-2]; } //pomi�emo sve znakove �elija za jedno mjesto udesno
                                      traka[0]='B';
                                      obradjeneCelije = (char*) realloc (obradjeneCelije, sizeof(char)*(maxVelicina+1) ); //realociramo memoriju za marker              
                                      for(i=(maxVelicina-1); i>0; i--) { obradjeneCelije[i-1]=obradjeneCelije[i-2]; }   
                                      obradjeneCelije[0]=0;
                                      trenutnaGlava=1; //trenutna pozicija glave vi�e nije na nuli jer smo pomaknuli cijelu traku udesno, stoga i trenutna glava ide s 0 na 1
                                      }
                 
                 }
    // ako je vra�en smjer bio 0, zna�i da nema novih prijelaza te se tra�enje zaustavlja i ispisuju kona�ni podaci
    printf("\n \nNEMA NOVIH DEFINIRANIH PRIJELAZA!\n \n");
    printf("UKUPNI BROJ KORAKA (vremenska slozenost): %d\n",korak-1);
    
    // ako je na traci bilo koji znak MIJENJAN, onda se u prostornu slo�enost obavezno moraju ubrojiti sve �elije niza!
    if(ucinjenaPromjenaNaTraci){
         for(i=0; i<(maxVelicina-2); i++){
                  if(traka[i]!='B'){ obradjeneCelije[i]=1; }
                  }
         }               
    for(i=0; i<=maxVelicina; i++){if(obradjeneCelije[i]==1) obradjenihCelija++;}                  //zbrajamo koliko je kori�tenih �elija
    printf("UKUPNO KORISTENIH CELIJA (prostorna slozenost): %d\n",obradjenihCelija);
    
    free(traka);    //osloba�anje kori�tene memorije
    free(obradjeneCelije);
    getchar();getchar();
    return 0;
}
