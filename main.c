#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>

typedef struct dugum{
    int plaka,komsu_sayisi;
    char isim[20], bolge[10];
    struct dugum* next;
    struct dugum* prev;
    struct komsu * komsu_sehir;
};
struct komsu{
    int plaka_kodu;
    struct komsu* next;
};
struct dugum* head = NULL;
FILE *output;

void sil(struct dugum** head, struct dugum* silincek)
{

    if (*head == NULL || silincek == NULL)
        return;

    if (*head == silincek)
        *head = silincek->next;

    if (silincek->next != NULL)
        silincek->next->prev = silincek->prev;

    if (silincek->prev != NULL)
        silincek->prev->next = silincek->next;


    free(silincek);
    return;
}
struct dugum* sehir_ara(struct dugum**birinci, int plaka, char isim[]){
    struct dugum* aranan = NULL;
    struct dugum* kopyala= *birinci;

    while(kopyala!=NULL){
        if(kopyala->plaka== plaka || strcmp(kopyala->isim, isim)==0){
            //printf("ISIM: %s\n",kopyala->isim);
            //printf("PLAKA: %d\n", kopyala->plaka);
            aranan = kopyala;
            return aranan;
        }
        kopyala=kopyala->next;
    }
    return aranan;
}
void komsu_sayisi_ara(struct dugum**birinci, int komsu_s){

    struct dugum* aranan_bolge = NULL;
    struct dugum* kopyalanan_bolge= *birinci;

    while(kopyalanan_bolge!=NULL ){
        if(kopyalanan_bolge->komsu_sayisi>=komsu_s){
            aranan_bolge = kopyalanan_bolge;
            printf("Isim: %s\n", aranan_bolge->isim);
            printf("Plaka: %d\n",aranan_bolge->plaka);
            printf("Komsu sayisi: %d\n",aranan_bolge->komsu_sayisi);

        }
        kopyalanan_bolge=kopyalanan_bolge->next;

    }

}
struct komsu* komsu_ara(struct komsu**birinci, int plaka){
    struct komsu* aranan = NULL;
    struct komsu* kopyala= *birinci;

    while(kopyala!=NULL){
        if(kopyala->plaka_kodu== plaka ){
            aranan = kopyala;
            printf("%d",aranan->plaka_kodu);
            return aranan;
        }
        kopyala=kopyala->next;
    }
    return aranan;
}
void komsu_sayisi_ortak(struct dugum**birinci, int komsu_s1, int komsu_s2){

    struct dugum* aranan_bolge = NULL;
    struct dugum* kopyalanan_bolge= *birinci;
    struct komsu* ortak = NULL;
    int a5;
    komsu_s2<=a5<=komsu_s1;

    while(kopyalanan_bolge!=NULL ){
        if(kopyalanan_bolge->komsu_sayisi >= komsu_s1 && kopyalanan_bolge->komsu_sayisi <= komsu_s2){
            ortak = kopyalanan_bolge->komsu_sehir;
            while(ortak!=NULL){
               if(kopyalanan_bolge->komsu_sehir->next->plaka_kodu==ortak->plaka_kodu){
                printf("Ortak komsular: %d\n", ortak->plaka_kodu);

             }
             ortak = ortak->next;
            }


        }
        kopyalanan_bolge=kopyalanan_bolge->next;

    }

}

void bolge_ara(struct dugum**birinci,char bolge[]){

    struct dugum* aranan_bolge = NULL;
    struct dugum* kopyalanan_bolge= *birinci;

    while(kopyalanan_bolge!=NULL ){
        if(strcmp(kopyalanan_bolge->bolge,bolge)==0){
            aranan_bolge = kopyalanan_bolge;
            printf("Isim: %s\n", aranan_bolge->isim);
            printf("Plaka: %d\n",aranan_bolge->plaka);
            printf("Komsu sayisi: %d\n",aranan_bolge->komsu_sayisi);

        }
        kopyalanan_bolge=kopyalanan_bolge->next;

    }

}
void komsu_sayisi(struct dugum**birinci,char bolge[]){

    struct dugum* aranan_bolge = NULL;
    struct dugum* kopyalanan_bolge= *birinci;

    while(kopyalanan_bolge!=NULL ){
        if(strcmp(kopyalanan_bolge->bolge,bolge)==0){
            aranan_bolge = kopyalanan_bolge;
            printf("Isim: %s\n", aranan_bolge->isim);
            printf("Plaka: %d\n",aranan_bolge->plaka);
            printf("Komsu sayisi: %d\n",aranan_bolge->komsu_sayisi);

        }
        kopyalanan_bolge=kopyalanan_bolge->next;

    }

}
struct komsu *dugum_yap(int yeni_plaka)
{

    struct komsu* komsu_yeni = (struct komsu*) malloc(sizeof(struct komsu));

    komsu_yeni->plaka_kodu = yeni_plaka;
    komsu_yeni->next =  NULL;

    return komsu_yeni;
}
struct dugum* dugum_al(int plaka,char isim[20],char bolge[10],int komsu_sayisi)
{

    struct dugum* sehir = (struct dugum*)malloc(sizeof(struct dugum));

    sehir->plaka = plaka;
    strcpy(sehir->isim,isim);
    strcpy(sehir->bolge,bolge);
    sehir->komsu_sayisi=komsu_sayisi;
    sehir->prev =NULL;
    sehir->next = NULL;
    sehir->komsu_sehir = NULL;
    return sehir;
}
void doubly(struct dugum** ilk, struct dugum*sehir)
{
    struct dugum*simdiki;

    if (*ilk == NULL)
        *ilk = sehir;


    else if ((*ilk)->plaka >= sehir->plaka) {
        sehir->next = *ilk;
        sehir->next->prev = sehir;
        *ilk = sehir;

    }

    else {
        simdiki = *ilk;


        while (simdiki->next != NULL &&
               simdiki->next->plaka < sehir->plaka)
               simdiki = simdiki->next;

        sehir->next = simdiki->next;


        if (simdiki->next != NULL)
            sehir->next->prev = sehir;

        simdiki->next = sehir;
        sehir->prev = simdiki;
    }
}
void singly(struct komsu**ilk, int p)
{
    struct komsu* yeni_dugum = (struct komsu*)malloc(sizeof(struct komsu));
    yeni_dugum->plaka_kodu = p;
    yeni_dugum->next = NULL;
    struct komsu* simdiki = *ilk;

    ///Liste boþ
     if (*ilk == NULL)
     {
         *ilk = yeni_dugum;

     }///Baþa
     else if(simdiki->plaka_kodu > yeni_dugum->plaka_kodu){

        yeni_dugum->next = simdiki;
        *ilk = yeni_dugum;
     }///araya
     else{

        while(simdiki->next != NULL){

            if(simdiki->next->plaka_kodu < yeni_dugum->plaka_kodu){
                struct komsu* temp = simdiki->next->next;
                simdiki->next->next = yeni_dugum;
                yeni_dugum->next=temp;
                return;
            }
            else{
                yeni_dugum->next = simdiki->next;
                simdiki->next = yeni_dugum;
            return;
            }

            simdiki = simdiki->next;
        }

        simdiki->next = yeni_dugum;

     }
}

void yazdir(struct dugum* sehir)
{
    output = fopen("cikti.txt","w");
    int a;
    struct dugum* son;
    while (sehir != NULL) {
        fprintf(output,"PLAKA: %d\n", sehir->plaka);
        fprintf(output,"ISIM: %s\t----> ", sehir->isim);
        yazdir_tek(sehir->komsu_sehir);
        fprintf(output,"\nBOLGE: %s\n",sehir->bolge);
        fprintf(output,"KOMSU SAYÝSÝ: %d\n", sehir->komsu_sayisi);
        fprintf(output,"\n");
        if(sehir->next != NULL){
            fprintf(output, "\n  ||   \t"); fprintf(output," /\\ \n");
            fprintf(output," \\  /\t"); fprintf(output,"/  \\ \n");
            fprintf(output,"  \\/ \t"); fprintf(output," ||\n");

        }
        fprintf(output, "\n");

        son = sehir;
        sehir = son->next;
    }
    }
void yazdir_tek(struct komsu *head)
{
    struct komsu *temp = head;
    while(temp != NULL)
    {
        fprintf(output, "%d", temp->plaka_kodu);
        if(temp->next != NULL)
            fprintf(output, " ----> ");
        temp = temp->next;
    }
}
void yazdir_tekk(struct komsu *head)
{
    struct komsu *temp = head;
    while(temp != NULL)
    {
        printf("%d", temp->plaka_kodu);
        if(temp->next != NULL)
            printf(" ----> ");
        temp = temp->next;
    }
}
void komsu_sil(struct komsu **head, int plaka)
{

    struct komsu* temp = *head, *prev;

    if (temp != NULL && temp->plaka_kodu == plaka)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->plaka_kodu != plaka)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;


    prev->next = temp->next;

    free(temp);
}

void menu(){
    int secim = 0;
    do{
        printf("\n");
        printf("\t\tMenü\n");
        printf("\t\t1-Yeni bir sehir ekleme.\n");
        printf("\t\t2-Yeni bir komsu ekleme.\n");
        printf("\t\t3-Sehir arama.\n");
        printf("\t\t4-Sehir sil.\n");
        printf("\t\t5-Bir bolgedeki sehirleri sirala.\n");
        printf("\t\t6-Belirli komsu sayisindaki illeri sirala.\n");
        printf("\t\t7-Belirli sayi araliginda komsusu olan illerin belirli ortak komsularini sirala.\n");
        printf("\t\t8-Tüm þehirleri listele.\n");
        printf("\t\t9-Komsu sil.\n");
        printf("\t\tProgramdan cikmak icin 0'i tuslayin.......\n");
        printf("\t\tSeciminiz: ");
        scanf("%d",&secim);

        switch(secim){

        case 1:
            printf("");
            int p, k,o;
            char b[8],i[10];
            printf("Plaka: \n " );
            scanf("%d",&p);
            printf("Isim: \n");
            scanf("%s" ,&i);
            printf("Bolge: \n");
            scanf("%s", &b);
            printf("Komsu sayisi: \n");
            scanf("%d", &k);

            struct dugum* bul= sehir_ara(&head, p, i);
            if(bul!=NULL){
            printf("Bu sehir zaten listede yer aliyor.\n");
            }
            else {
                printf("Sehir eklendi...\n");
                struct dugum * kullanici = dugum_al(p,i,b,k);
                doubly(&head,kullanici);
            }
            break;

        case 2:
            printf("");
            int r,w,kont=0;
            char e[2];
            printf("Komsu eklemek istediginiz ilin plakasini girin: \n");
            scanf("%d",&r);
            printf("Eklemek istediginiz komsu plakasini girin: \n");
            scanf("%d", &w);
            struct dugum *komsu_ekle = sehir_ara(&head, r, "");
            if(komsu_ekle!=NULL){
                struct komsu * kullanici_komsu = dugum_yap(r);
                while(sehir_ara(&head, r, "")->komsu_sehir->next!=NULL){
                   if(sehir_ara(&head, r, "")->komsu_sehir->plaka_kodu==w){
                    printf("Bu komsu zaten mevcut..\n");
                    kont = 1;
                    break;
                }
                sehir_ara(&head, r, "")->komsu_sehir=sehir_ara(&head, r, "")->komsu_sehir->next;
                }
                if(kont!=1){
                    singly(&sehir_ara(&head, r, "")->komsu_sehir,w);
                    printf("Komsu eklendi..\n");
                    sehir_ara(&head,r,"")->komsu_sayisi++;
                }

            }
            else{
                printf("Listede olmayan bir il plakasi girdiniz...\n");
            }
            break;

        case 3:
            printf("");
            int s;
            char il[15];
            printf("Aramak istediginiz ilin plakasini girin: \n");
            scanf("%d",&s);
            printf("Aramak istediginiz ilin adini girin: \n");
            scanf("%s",&il);
            struct dugum * sehir_bul = sehir_ara(&head, s, il);
            if(sehir_bul!=NULL){
                printf("Sehir bulundu....\n");
                printf("Plaka: %d \n", sehir_ara(&head, s, il)->plaka);
                printf("Isim: %s ---> ", sehir_ara(&head,s,il)->isim);
                yazdir_tekk(sehir_ara(&head, s, il)->komsu_sehir);
                printf("\n");
                printf("Bolge: %s\n",sehir_ara(&head,s,il)->bolge);
                printf("Komsu sayisi: %d \n ", sehir_ara(&head,s,il)->komsu_sayisi);

                }
            else{
                printf("");
                int n, m;
                char f[10];
                printf("Sehir bulunamadi....\n ");
                printf("Bu sehiri eklemek isterseniz 1'i tuslayin: ");
                scanf("%d",&n);
                if(n==1){
                    printf("Sehirin bolgesini girin: ");
                    scanf("%s",&f);
                    printf("Sehirin komsu sayisini girin: ");
                    scanf("%d",&m);
                    struct dugum * kullanicii = dugum_al(s,il,f,m);
                    doubly(&head,kullanicii);
                    printf("\nSehir eklendi...\n");
                    }
            }

            break;

        case 4:
            printf("");
            int sil_kullanici;
            char isim_sil[25];
            printf("Silmek istediginiz ilin plakasi: \n");
            scanf("%d", &sil_kullanici);
            printf("Silmek istediginiz ilin adi: \n");
            scanf("%s", &isim_sil);
            struct dugum*sill = sehir_ara(&head, sil_kullanici, isim_sil);
            if(sill!=NULL){
                sil(&head, sill);
                printf("Sehir silindi..\n");
            }
            else
                printf("Boyle bir sehir yok.\n");
            break;

        case 5:
            printf("Lutfen bir bolge girin: \n");
            char al[15];
            scanf("%s",&al);
            bolge_ara(&head,al);
            break;

        case 6:
            printf("");
            int sayi;
            printf("Lutfen bir sayi giriniz: ");
            scanf("%d",&sayi);
            printf(" %d 'den // dan büyük ve esit illerin listesi: \n", sayi);
            komsu_sayisi_ara(&head,sayi);
            break;

        case 7:
            printf("");
            int a1,a2;
            printf("Ortak komsulari listelemek icin sayi araligindaki ilk sayiyi girin: \n");
            scanf("%d",&a1);
            printf("Ikinci sayiyi girin: \n");
            scanf("%d",&a2);
            komsu_sayisi_ortak(&head,a1,a2);
            break;

        case 8:
            yazdir(head);
            break;
        case 9:
            printf("");
            int z3=0;
            int z1, z2;
            printf("Komþusunu silmek istediginiz ilin plakasi: ");
            scanf("%d", &z1);
            printf("Silmek istediginiz ilin plakasi: ");
            scanf("%d", &z2);
            komsu_sil(&sehir_ara(&head, z1, " ")->komsu_sehir,z2);
            sehir_ara(&head,z1, "")->komsu_sayisi--;
            break;

        case 0:
            printf("Çýkýlýyor....\n");
            break;

        default:
            printf("Geçerli bir seçim girin!\n");

        }

    }while(secim);


}
int main()
{

    setlocale(0,"Turkish");

    /// ÞEHÝR OKUMA
    char satir[400],*karakter;
    FILE *dosya;
    dosya = fopen("sehirler.txt", "r");
    struct dugum* ilk = NULL;

    struct komsu * ilk_komsu;

    if(dosya==NULL){
        printf("Dosya bulunamadi...");
    }
    else{
            while(!feof(dosya)){
                karakter=fgets(satir,400,dosya);
                if(feof(dosya))
                    break;
                int virgul=0,virgul_say=0;
                int i = 0;
                int j,a,b,c,d;
                char gecici[250];

                struct dugum eklenecek;
                eklenecek.komsu_sehir = NULL;
                while(satir[i]!='\0'){



                    if(satir[i] != ',' && satir[i]!='\n'){
                        gecici[virgul] = satir[i];
                        virgul++;
                        i++;

                    }

                    else if(satir[i]==','){
                        virgul_say++;
                        gecici[virgul] ='\0';
                        virgul=0;
                          if(virgul_say==1){
                            eklenecek.plaka = atoi(gecici);
                        i++;
                        }
                        else if(virgul_say==2){

                            strcpy(eklenecek.isim,gecici);
                            i++;
                        }
                        else if(virgul_say==3){

                            strcpy(eklenecek.bolge,gecici);
                            i++;
                        }
                        else if(virgul_say>3){
                            i++;
                        }
                    }
                    else if(satir[i] == '\n'){
                        virgul=0;
                        break;
                    }

                    }
                    eklenecek.komsu_sayisi = virgul_say-2;
                    struct dugum*sehirr = dugum_al(eklenecek.plaka,eklenecek.isim,eklenecek.bolge,eklenecek.komsu_sayisi);
                    doubly(&head, sehirr);
                    i++;

                }

        }
fclose(dosya);



/// ÞEHÝR OKUMA SONU


/// KOMÞU OKUMA

char satir2[400],*karakter1;
    FILE *dosya2;
    dosya2 = fopen("sehirler.txt", "r");

    if(dosya==NULL){
        printf("Dosya bulunamadi...");
    }
    else{
            while(!feof(dosya)){
                karakter1=fgets(satir2,400,dosya);
                if(feof(dosya2))
                    break;
                int virgul=0,virgul_say=0;
                int i = 0;
                int j,a,b,c,d;
                char gecici[250];

                struct dugum eklenecek;

                eklenecek.komsu_sehir = NULL;
                while(satir2[i]!='\0'){



                    if(satir2[i] != ',' && satir2[i]!='\n'){
                        gecici[virgul] = satir2[i];
                        virgul++;
                        i++;

                    }

                    else if(satir2[i]==','){
                        virgul_say++;
                        gecici[virgul] ='\0';
                        virgul=0;
                          if(virgul_say==1){
                            eklenecek.plaka = atoi(gecici);
                        i++;
                        }
                        else if(virgul_say==2){

                            strcpy(eklenecek.isim,gecici);
                            i++;
                        }
                        else if(virgul_say==3){

                            strcpy(eklenecek.bolge,gecici);
                            i++;
                        }
                        else{

                            //struct komsu * komsu_olustur = dugum_yap(sehir_ara(&head,0,gecici)->plaka);
                            singly(&sehir_ara(&head,eklenecek.plaka,eklenecek.isim)->komsu_sehir,sehir_ara(&head,0,gecici)->plaka);
                            i++;
                        }
                    }
                    else if(satir2[i] == '\n'){

                        gecici[virgul] = '\0';
                        virgul=0;
                        singly(&sehir_ara(&head,eklenecek.plaka,eklenecek.isim)->komsu_sehir,sehir_ara(&head,0,gecici)->plaka);
                        break;
                    }

                    }

                    i++;

                }

        }
fclose(dosya2);


/// KOMÞU OKUMA SONU

menu();
fclose(output);

return 0;
}
