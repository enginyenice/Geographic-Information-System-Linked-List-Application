#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


/* Nodelar */
struct node
{
    int plaka;
    char sehirAdi[20];
    char bolge[5];
    int komsu_sayisi;
    struct node * ileri;
    struct node * geri;
    struct node * komsuNode;

};
struct komsuNode
{
    int komPlaka;
    struct komsuNode * komIleri;
};


/* Fonksiyonlar */

/* Menuler */
void menu(); // Menu Ekrani
void sehirAra(); // Sehir Arama menusu
void komsuIslemMenu(struct node *iter,int sehirPlaka); // Komsu islemleri menusu
void sehirSil(); // Sehir silme menusu
void komsuSil(struct node *r); // Komsu Silme menusu
void sehirDuzenle(); // Sehir duzenleme menusu

/* Arama */
void isimArama(); // Isime gore sehir arama
void plakaArama(); // Plakaya gore sehir arama
void bolgeAra(); // Bolge kisaltmasina gore sehirleri arama
void kriterArama(); // Kriterlere gore sehir arama
int komsuPlakaBul(struct node *r, char sehirAdi[20]); // Komsunun plakasinin bulunmasi

int sehirToPlaka(char sehirAdi[20]); // Sehir Adini Plaka numarasina cevirme

/* Okuma */
FILE *yazilacakDosya; //Yazilacak dosyanin genel tanimi
void dosyaOku(int status); // dosyanin Okunma islemi
void parcala(char kelime[200],int status); // Dosyadan gelen satirin parcalanma islemi
void dosyaYazma(); // Outputs yazma islemi

/* Ekleme */
struct node * ekle(struct node * r,int plaka,char sehirAdi[20],char bolge[5],int komsu_sayisi); // Sehir ekleme
struct komsuNode * komekle(struct komsuNode* r,int komPlaka,int sehirPlaka); // Komsu Ekleme
void sehirEkle(); // Sehir ekleme menusu

/* Ekrana Cikti Verme */
void ekranaYaz(struct node* r); // Ekrana bilgileri cikartir
void renkDegistir(int renk); // Ekran rengini degistirir
void menuAdiOlustur(char menuAdi[100],int renk,int son); // Menu olusturur
void sehirGetir(int plaka); // Sehir bilgisini getirir
void komsulariniGetir(struct node * r); // Komsularini ekrana getirir

/* Silme */
void komsuSilAuto(struct node *r,int plaka); //Otomatik komsu silme
struct node * sil(struct node * r,struct node *iter,int plaka); //  Sehir silme
struct komsuNode * komsuyusil(struct komsuNode * kroot,struct komsuNode * kiter,struct node * r,int plaka); //komsu silme

/* Kontroller */
int komsuKontrol(struct node* r,int plaka,int sehirPlaka); // Komsu kontrol
int sehirIsimKontrol(struct node *r,char sehirAdi[20]); // Ayni isme ait sehir var mi
void komsuCek(); // Komsularini ceker
void bolgeRenkleri(char bolge[5]); // Bolge renklendirir

/* Structlar Ilk Tutucular*/
struct node * root;
struct komsuNode * komsuRoot;

struct komsuNode * komekle(struct komsuNode* r,int komPlaka,int sehirPlaka)
{
    struct node * Globaliter;
    Globaliter = root;
    while(Globaliter->plaka  != sehirPlaka)
    {
        Globaliter = Globaliter->ileri;

    }

    //printf("Eklenecek Plaka: %d , komPlaka: %d , sehirPlaka %d\n",Globaliter->plaka,komPlaka,sehirPlaka);
    if(Globaliter->komsuNode == NULL)
    {
        r = (struct komsuNode*)malloc(sizeof(struct komsuNode));
        r->komIleri = NULL;
        r->komPlaka = komPlaka;
        Globaliter->komsuNode = (void *)r;
        Globaliter->komsu_sayisi = Globaliter->komsu_sayisi+1;
        return r;
    }
    else
    {
        if(r->komPlaka >  komPlaka)
        {

            struct komsuNode * temp = (struct komsuNode*)malloc(sizeof(struct komsuNode));

            temp->komIleri = r;


            temp->komPlaka = komPlaka;
            Globaliter->komsu_sayisi = Globaliter->komsu_sayisi+1;
            Globaliter->komsuNode = (void *)temp;
            return temp;
        }
        else
        {
            struct komsuNode * iter;
            iter = r;
            while(iter->komIleri !=NULL && iter->komIleri->komPlaka < komPlaka)
            {
                iter = iter->komIleri;

            }
            if(iter->komIleri == NULL)
            {
                struct komsuNode * temp = (struct komsuNode*)malloc(sizeof(struct komsuNode));
                iter->komIleri = temp;

                temp->komIleri = NULL;
                temp->komPlaka = komPlaka;
                Globaliter->komsu_sayisi = Globaliter->komsu_sayisi+1;

                return r;

            }
            else
            {
                struct komsuNode * temp = (struct komsuNode*)malloc(sizeof(struct komsuNode));

                temp->komIleri = iter->komIleri;
                iter->komIleri = temp;

                temp->komPlaka = komPlaka;
                Globaliter->komsu_sayisi = Globaliter->komsu_sayisi+1;

                return r;
            }
        }
    }
    return r;
};
struct node * ekle(struct node * r,int plaka,char sehirAdi[20],char bolge[5],int komsu_sayisi)
{
    if(r == NULL)
    {
        r = (struct node*)malloc(sizeof(struct node));
        r->ileri = NULL;
        r->geri = NULL;


        r->plaka = plaka;
        r->komsu_sayisi = komsu_sayisi;
        strcpy(r->sehirAdi,sehirAdi);
        strcpy(r->bolge,bolge);
        r->komsuNode = NULL;


        return r;
    }
    else
    {
        if(r->plaka >  plaka)
        {

            struct node * temp = (struct node*)malloc(sizeof(struct node));

            temp->ileri = r;
            temp->geri = NULL;
            r->geri = temp;

            temp->plaka = plaka;
            temp->komsu_sayisi = komsu_sayisi;
            strcpy(temp->sehirAdi,sehirAdi);
            strcpy(temp->bolge,bolge);
            temp->komsuNode = NULL;
            return temp;
        }
        else
        {
            struct node * iter;
            iter = r;
            while(iter->ileri !=NULL && iter->ileri->plaka < plaka)
            {
                iter = iter->ileri;

            }
            if(iter->ileri == NULL)
            {
                struct node * temp = (struct node*)malloc(sizeof(struct node));
                iter->ileri = temp;
                temp->geri = iter;
                temp->ileri = NULL;
                temp->plaka = plaka;
                temp->komsu_sayisi = komsu_sayisi;
                strcpy(temp->sehirAdi,sehirAdi);
                strcpy(temp->bolge,bolge);
                temp->komsuNode = NULL;
                return r;

            }
            else
            {
                struct node * temp = (struct node*)malloc(sizeof(struct node));
                iter->ileri->geri = temp;
                temp->ileri = iter->ileri;
                iter->ileri = temp;
                temp->geri = iter;
                temp->plaka = plaka;
                temp->komsu_sayisi = komsu_sayisi;
                strcpy(temp->sehirAdi,sehirAdi);
                strcpy(temp->bolge,bolge);
                temp->komsuNode = NULL;
                return r;
            }
        }
    }
    return r;
};
struct komsuNode * komsuyusil(struct komsuNode * kroot,struct komsuNode * kiter,struct node * r,int plaka)
{
    /*
    printf("Kroot %d\n", kroot->komPlaka);
    printf("Kiter %d\n", kiter->komPlaka);
    printf("Plaka %d\n", plaka);
    */

    if(kiter->komPlaka == kroot->komPlaka)
    {
        struct komsuNode * temp;
        temp = kiter->komIleri;
        kiter->komIleri = NULL;
        free(kiter);

        r->komsuNode = (void *)temp;

        r->komsu_sayisi = r->komsu_sayisi - 1;
        return temp;
    }
    else
    {
        struct komsuNode * niter;
        niter = kroot;
        while(niter->komIleri != NULL)
        {
            if(niter->komIleri->komPlaka == plaka)
            {
                break;
            }
            niter = niter->komIleri;
        }
        //printf("Niter Plaka %d", niter->komPlaka);
        if(niter->komIleri != NULL)
        {
            struct komsuNode * temp;
            temp = kiter->komIleri;
            niter->komIleri = temp;

            kiter->komIleri = NULL;
            free(kiter);
            r->komsu_sayisi = r->komsu_sayisi - 1;
            r->komsuNode = (void *)kroot;

            return kroot;
        }
        else if(niter->komIleri == NULL)
        {
            free(niter->komIleri);
            r->komsuNode = (void *)kroot;

            r->komsu_sayisi = r->komsu_sayisi - 1;
            return kroot;


        }
    }







    return kroot;

};
struct node * sil(struct node * r,struct node *iter,int plaka)
{

    if(iter->ileri == NULL && iter->geri == NULL)
    {
        return NULL;
    }
    if(iter == root)
    {
        struct node *temp;
        temp = iter->ileri;
        iter->ileri = NULL;
        temp->geri = NULL;
        free(iter);
        return temp;
    }
    else
    {
        if(iter->ileri != NULL)
        {
            struct node *tempIleri;
            struct node *tempGeri;
            tempIleri = iter->ileri;
            tempGeri  = iter->geri;

            iter->ileri = NULL;
            iter->geri = NULL;

            tempGeri->ileri = tempIleri;
            tempIleri->geri = tempGeri;
            free(iter);

        }
        else
        {
            struct node *tempGeri;
            tempGeri = iter->geri;

            iter->geri = NULL;
            tempGeri->ileri = NULL;
            free(iter);
        }
    }

    return r;
}
int sehirKontrol(struct node* r,int plaka)
{
    struct node * iter;
    iter = r;
    int status = 0; //0 sehir yok 1 sehir var 2 plaka hatali
    if(plaka > 0)
    {
        while(iter != NULL)
        {
            if(iter->plaka == plaka)
            {
                status = 1;
            }
            iter = iter->ileri;
        }

    }
    else
    {
        status = 2;

    }

    return status;
}
void ekranaYaz(struct node* r)
{

    fprintf(yazilacakDosya,">> Tum sehirlerin listesi <<\n");
    system("cls");
    struct node * iter;
    iter = r;
    if(iter == NULL)
    {
        fprintf(yazilacakDosya,"Liste Bos\n");
        printf("Liste Bos\n");
    }
    else
    {

        while(iter != NULL)
        {
            bolgeRenkleri(iter->bolge);
            printf(">> [%d] %s %s %d, ",iter->plaka,iter->sehirAdi,iter->bolge,iter->komsu_sayisi);
            fprintf(yazilacakDosya,">> [%d] %s %s %d, ",iter->plaka,iter->sehirAdi,iter->bolge,iter->komsu_sayisi);

            struct komsuNode *kom;
            kom = (void *)iter->komsuNode;
            while(kom != NULL)
            {
                printf("->[%d]",kom->komPlaka);
                fprintf(yazilacakDosya,"->[%d]",kom->komPlaka);
                kom = kom->komIleri;

            }
            iter = iter->ileri;
            fprintf(yazilacakDosya,"\n");

            /*
                        fprintf(yazilacakDosya,"\t  *      * \n");
                        fprintf(yazilacakDosya,"\t ***     * \n");
                        fprintf(yazilacakDosya,"\t*****  ***** \n");
                        fprintf(yazilacakDosya,"\t  *     *** \n");
                        fprintf(yazilacakDosya,"\t  *      * \n");

            */

            printf("\n");

        }
        system("PAUSE");
        system("CLS");

    }

}
int main()
{
    dosyaYazma();
    root = NULL;
    dosyaOku(0);
    komsuCek();
    while(1)
    {
        menu();
    }

    return 0;
}
void menu()
{
    int secim;
    menuAdiOlustur("000",1,1);
    menuAdiOlustur("     ISLEMLER   ",10,0);
    menuAdiOlustur("1-)Sehir Listesi",11,0);
    menuAdiOlustur("2-)Sehir Ekle   ",12,0);
    menuAdiOlustur("3-)Sehir Sil    ",13,0);
    menuAdiOlustur("4-)Sehir Duzenle",9,0);
    menuAdiOlustur("5-)Arama Yap    ",14,0);
    menuAdiOlustur("9-)Kapat        ",15,0);
    menuAdiOlustur("000",1,1);
    menuAdiOlustur("Secim Yap: ",15,2);
    scanf("%d",&secim);
    system("cls");
    switch(secim)
    {
    case 1:
        ekranaYaz(root);
        break;
    case 2:
        sehirEkle();
        break;
    case 3:
        sehirSil();
        break;
    case 4:
        sehirDuzenle();
        break;
    case 5:
        sehirAra();
        break;
    case 9:
        fclose(yazilacakDosya);
        printf("Gule gule\n");
        exit(0);
        break;
    }

}
void komsuSil(struct node *r)
{
    fprintf(yazilacakDosya,"\n");
    int plaka = -999;
    char sehirAdi[20];
    //printf("Silmek istenilen komsunun plakasi: ");
    int secim;
komsuSilGo:
    menuAdiOlustur("000",1,1);
    menuAdiOlustur("     ISLEMLER   ",10,0);
    menuAdiOlustur("1-)Isime gore   ",11,0);
    menuAdiOlustur("2-)Plakaya gore ",12,0);
    menuAdiOlustur("0-)Geri         ",15,0);
    menuAdiOlustur("000",1,1);
    menuAdiOlustur("Secim Yap: ",15,2);
    scanf("%d",&secim);

    switch(secim)
    {
    case 1:
        printf("Sehir Adi giriniz: ");
        struct node * iter;
        iter = root;
        scanf("%s",sehirAdi);
        while(iter != NULL)
        {
            if(strcasecmp(iter->sehirAdi,sehirAdi) == 0)
            {
                plaka = iter->plaka;
            }
            iter = iter->ileri;

        }


        break;
    case 2:

        printf("Plaka giriniz: ");
        scanf("%d",&plaka);
        break;
    case 0:
        menu();
        break;
    }




    struct komsuNode * kiter;
    struct komsuNode * kroot;
    kroot = (void *)r->komsuNode;
    kiter = (void *)r->komsuNode;
    int status;
    while(kiter != NULL)
    {
        if(kiter->komPlaka == plaka)
        {
            status =1;
            break;
        }
        kiter = kiter->komIleri;
    }
    if(status == 1)
    {
        fprintf(yazilacakDosya,"%s ye ait %d plaka numarali komsu silindi.\n",r->sehirAdi,kiter->komPlaka);
        kroot = komsuyusil(kroot,kiter,r,plaka);
        struct node *iter;
        iter = root;
        while(iter->ileri != NULL)
        {
            if(iter->plaka == plaka)
            {
                break;
            }
            iter = iter->ileri;


        }

        komsuSilAuto(iter,r->plaka);

        komsulariniGetir(r);

    }
    else
    {

        printf("\n!!!Komsu bulunamadi!!!\n");
        system("PAUSE");
        system("cls");
        goto komsuSilGo;
    }

    system("PAUSE");
    system("cls");
}
void sehirEkle()
{
    fprintf(yazilacakDosya,"\n");
    system("cls");
    int plaka;
    char  sehirAdi[20];
    char  bolge[5];
    printf("Sehir Ekle:\n");
    fprintf(yazilacakDosya,"Sehir Ekle:\n");
    printf("Plaka No:" );
    scanf("%d",&plaka);
    fprintf(yazilacakDosya,"Eklenecek Plaka: %d\n",plaka);
    printf("Sehir Adi:" );
    scanf("%s",sehirAdi);
    fprintf(yazilacakDosya,"Eklenecek Sehir Adi: %s\n",sehirAdi);
    printf("Bolge:" );

    scanf("%s",bolge);
    fprintf(yazilacakDosya,"Eklenecek Bolge Adi: %s\n",bolge);
    if(sehirKontrol(root,plaka)  == 0)
    {
        if(sehirIsimKontrol(root,sehirAdi) == 0)
        {
            root = ekle(root,plaka,sehirAdi,bolge,0);
            fprintf(yazilacakDosya,"Sehir Eklendi. Sehir Bilgisi:\n");
            printf("Sehir Eklendi. Sehir Bilgisi:\n");
            sehirGetir(plaka);
        }
        else
        {
            fprintf(yazilacakDosya,"Boyle bir isimde sehir var. Tekrar ekleyemessiniz\n");
            printf("Boyle bir isimde sehir var. Tekrar ekleyemessiniz\n");
        }


    }
    else if(sehirKontrol(root,plaka) == 1)
    {
        printf("Boyle bir plakada sehir var. Tekrar ekleyemessiniz\n");
        fprintf(yazilacakDosya,"Boyle bir plakada sehir var. Tekrar ekleyemessiniz\n");
    }
    else
    {
        printf("Plaka Hatali %d",plaka);
        fprintf(yazilacakDosya,"Plaka Hatali %d",plaka);
    }


}
void sehirAra()
{
    fprintf(yazilacakDosya,"\n");
    fprintf(yazilacakDosya,"Arama Islemi\n");
    system("cls");
    int secim;
    menuAdiOlustur("000",1,1);
    menuAdiOlustur("     ARAMA      ",5,0);
    menuAdiOlustur("1-) Isime gore  ",4,0);
    menuAdiOlustur("2-) Plakaya gore",3,0);
    menuAdiOlustur("3-) Bolgeye gore",2,0);
    menuAdiOlustur("4-) Kritere gore",1,0);
    menuAdiOlustur("000",1,1);
    menuAdiOlustur("Secim Yap: ",15,2);
    scanf("%d",&secim);
    system("cls");
    switch(secim)
    {
    case 1:
        isimArama();
        break;
    case 2:
        plakaArama();
        break;
    case 3:
        bolgeAra();
        break;
    case 4:
        kriterArama();
        break;
    }

}
int sehirToPlaka(char sehirAdi[20])
{
    struct node *iter;
    iter = root;
    while(iter != NULL)
    {
        if(strcasecmp(iter->sehirAdi,sehirAdi) == 0)
        {
            return iter->plaka;
        }
        iter = iter->ileri;
    }
    return -99;

}
void sehirGetir(int plaka)
{
    struct node *iter;
    iter = root;
    while(iter!= NULL)
    {
        if(iter->plaka == plaka)
        {
            printf("[%d] %s %s\n",iter->plaka,iter->sehirAdi,iter->bolge);
            fprintf(yazilacakDosya,"[%d] %s %s\n",iter->plaka,iter->sehirAdi,iter->bolge);
            break;
        }
        iter = iter->ileri;

    }
}
void isimArama()
{
    char sehirAdi[20];
    printf("Sehir adini giriniz: ");
    scanf("%s",sehirAdi);
    struct node * iter;
    iter = root;
    int searchStatus = 0;
    while(iter != NULL)
    {
        if(strcmp(iter->sehirAdi,sehirAdi) == 0)
        {
            bolgeRenkleri(iter->bolge);
            fprintf(yazilacakDosya,"Sehir Bilgileri [Isim Aramasi][%s]\n",sehirAdi);
            printf("\n\nSehir Bilgileri [Isim Aramasi][%s]\n",sehirAdi);
            fprintf(yazilacakDosya,"Plaka: %d\t Sehir Adi: %s\t Bolge: %s\n",iter->plaka,iter->sehirAdi,iter->bolge);
            printf("Plaka: %d\t Sehir Adi: %s\t Bolge: %s\n",iter->plaka,iter->sehirAdi,iter->bolge);
            komsulariniGetir(iter);
            fprintf(yazilacakDosya,"Toplam Komsu Sayisi: %d\n",iter->komsu_sayisi);
            printf("Toplam Komsu Sayisi: %d\n",iter->komsu_sayisi);
            searchStatus = 1;
            komsuIslemMenu(iter,iter->plaka);
            break;
        }
        iter = iter->ileri;
    }
    if(searchStatus == 0)
    {
        system("cls");
        fprintf(yazilacakDosya,"Sehir Bilgileri [Plaka Aramasi][%s]\n",sehirAdi);
        printf("Sehir Bilgileri [Plaka Aramasi][%s]\n",sehirAdi);
        fprintf(yazilacakDosya,"Sehir bulunamadi.\n");
        printf("Sehir bulunamadi. Eklemek Istermisiniz ? 0 Hayir, 1 Evet: ");
        int status;
        scanf("%d",&status);
        switch(status)
        {
        case 0:
            break;
        case 1:
            sehirEkle();
            break;
        }


    }


}
void plakaArama()
{
    int plaka;
    printf("Plaka giriniz: ");
    scanf("%d",&plaka);
    struct node * iter;
    iter = root;
    int searchStatus = 0;
    while(iter != NULL)
    {
        if(iter->plaka == plaka)
        {
            bolgeRenkleri(iter->bolge);
            fprintf(yazilacakDosya,"Sehir Bilgileri [Plaka Aramasi][%d]\n",plaka);
            printf("\n\nSehir Bilgileri [Plaka Aramasi][%d]\n",plaka);
            fprintf(yazilacakDosya,"Plaka: %d\t Sehir Adi: %s\t Bolge: %s\n",iter->plaka,iter->sehirAdi,iter->bolge);
            printf("Plaka: %d\t Sehir Adi: %s\t Bolge: %s\n",iter->plaka,iter->sehirAdi,iter->bolge);
            komsulariniGetir(iter);
            fprintf(yazilacakDosya,"Toplam Komsu Sayisi: %d\n",iter->komsu_sayisi);
            printf("Toplam Komsu Sayisi: %d\n",iter->komsu_sayisi);
            searchStatus = 1;
            komsuIslemMenu(iter,iter->plaka);
            break;
        }
        iter = iter->ileri;
    }
    if(searchStatus == 0)
    {
        system("cls");
        fprintf(yazilacakDosya,"Sehir Bilgileri [Plaka Aramasi][%d]\n",plaka);
        printf("Sehir Bilgileri [Plaka Aramasi][%d]\n",plaka);
        fprintf(yazilacakDosya,"Sehir bulunamadi.\n");
        printf("Sehir bulunamadi. Eklemek Istermisiniz ? 0 Hayir, 1 Evet: ");
        int status;
        scanf("%d",&status);
        switch(status)
        {
        case 0:
            break;
        case 1:
            sehirEkle();
            break;
        }

    }


}
void komsulariniGetir(struct node * r)
{
    struct komsuNode * kNode;
    struct node * iter;
    iter = (void *)root;
    kNode = (void *)r->komsuNode;

    printf("Komsu Bilgileri\n");
    while(kNode != NULL)
    {

        while(iter != NULL)
        {

            if(kNode->komPlaka == iter->plaka)
            {
                fprintf(yazilacakDosya,"Komsu: %d %s %s\n",iter->plaka,iter->sehirAdi,iter->bolge);
                printf("Komsu: %d %s %s\n",iter->plaka,iter->sehirAdi,iter->bolge);
                break;
            }
            iter = iter->ileri;
        }
        kNode = kNode->komIleri;


    }

}
void dosyaOku(int status)
{
    FILE *dosya;
    dosya = fopen("sehirler.txt","r");
    if(dosya)
    {
        char birkelime[200];
        int c;
        do
        {

            c = fscanf(dosya,"%s",birkelime);
            if (feof(dosya))
            {
                break;
            }
            if(status == 0)
            {
                parcala(birkelime,0);
            }
            else if(status == 1)
            {
                parcala(birkelime,1);
            }
        }
        while (c != EOF);
        fclose(dosya);



    }
    else
    {

        if(status == 0)
        {
            fprintf(yazilacakDosya,"Ana dizinde sehirler.txt bulunamadi!!!\n");
            printf("Ana dizinde sehirler.txt dosyasi bulunamadi.!!!\n");
        }

        //exit(404);

    }


}
void parcala(char kelime[200],int status) // 0 gonderirsen sehir ceker 1 gonderirsen komsu ceker
{
    const char s[4] = ",";
    char *token;
    int plaka;
    char *sehirAdi[20];
    char *bolge[5];

    token = strtok(kelime, s);

    int a = 0;
    while( token != NULL )
    {

        if(status == 0)
        {
            if(a == 0)
            {
                plaka = atoi(token);
                //printf("%d\n", plaka);
                if(sehirKontrol(root,plaka) == 1)
                {
                    printf("Listede ayni sehirden birden fazla var. Plaka NO: %d\n",plaka);
                    plaka = 0;

                }
            }
            if(a == 1)
            {

                *sehirAdi = token;
                //printf( "%d-) %s | ",a, *sehirAdi);
            }
            if(a == 2)
            {
                *bolge = token;
                //printf( "%d-) %s \n",a, *bolge);
                if(plaka != 0 && *bolge != NULL && sehirAdi != NULL)
                {
                    root =  ekle(root,plaka,*sehirAdi,*bolge,0);
                }
            }

        }
        else if(status == 1)
        {
            int sehirPlaka;
            if(a == 0)
            {
                sehirPlaka = atoi(token);
            }
            if(a == 2)
            {

                // printf("\n");
            }
            if(a > 2)
            {
                //printf("%d| %d) %s\n ",sehirPlaka,komsuPlakaBul(root,token),token);


                if(komsuKontrol(root,komsuPlakaBul(root,token),sehirPlaka) == 1)
                {
                    printf("Listede ayni sehirden birden fazla var. Plaka NO: %d\n",komsuPlakaBul(root,token));


                }
                else
                {
                    komsuRoot = komekle(komsuRoot,komsuPlakaBul(root,token),sehirPlaka);
                }




            }


        }

        a++;

        token = strtok(NULL, s);
    }
}
void bolgeAra()
{
    fprintf(yazilacakDosya,"\n");
    char bolge[5];
    printf("Bolge kisaltmasini giriniz: ");
    scanf("%s",bolge);
    struct node * iter;
    iter = root;
    int searchStatus = 0;
    fprintf(yazilacakDosya,"Bolge Bilgileri [Bolge Aramasi][%s]\n",bolge);
    printf("Bolge Bilgileri [Bolge Aramasi][%s]\n",bolge);
    while(iter != NULL)
    {
        if(strcmp(iter->bolge,bolge) == 0)
        {
            bolgeRenkleri(iter->bolge);
            fprintf(yazilacakDosya,"Plaka: %d\t Sehir Adi: %s\t Bolge: %s\tKomsu Sayisi: %d\n",iter->plaka,iter->sehirAdi,iter->bolge,iter->komsu_sayisi);
            printf("Plaka: %d\t Sehir Adi: %s\t Bolge: %s\tKomsu Sayisi: %d\n",iter->plaka,iter->sehirAdi,iter->bolge,iter->komsu_sayisi);
            searchStatus = 1;
        }
        iter = iter->ileri;
    }
    if(searchStatus == 0)
    {
        printf("\n\nBolge Bilgileri [Bolge Aramasi][%s]\n",bolge);
        printf("Bolge bulunamadi\n\n");
    }

    system("PAUSE");
    system("CLS");
}
void sehirSil()
{
    fprintf(yazilacakDosya,"\n");
    system("cls");
    fprintf(yazilacakDosya,"Sehir Silme\n");
    int plaka = 0;
    char sehirAdi[20];
    menuAdiOlustur("000",1,1);
    menuAdiOlustur("     SEHIR SILME",10,0);
    menuAdiOlustur("1-)Plakaya Gore ",11,0);
    menuAdiOlustur("2-)Isime Gore   ",12,0);
    menuAdiOlustur("000",1,1);
    menuAdiOlustur("Secim Yap: ",15,2);
    int secim = 0;
    scanf("%d",&secim);
    int searchStatus = 0;






    if(secim == 1)
    {


        printf("Plaka giriniz: ");
        scanf("%d",&plaka);
        struct node * iter;
        iter = root;

        while(iter != NULL)
        {
            if(iter->plaka == plaka)
            {
                printf("\n\nSilmek Istediginiz Sehirin Bilgileri [Plaka Aramasi][%d]\n",plaka);
                bolgeRenkleri(iter->bolge);
                printf("Plaka: %d\t Sehir Adi: %s\t Bolge: %s\n\n",iter->plaka,iter->sehirAdi,iter->bolge);
                int status = 0;
                printf("Silmek icin 1 vazgecmek icin 0'a basiniz: ");
                scanf("%d",&status);
                searchStatus = 1;
                if(status == 0)
                {
                    break;
                }
                else if(status == 1)
                {
                    struct node *komsuSehirTarayici;
                    komsuSehirTarayici = root;
                    while(komsuSehirTarayici != NULL)
                    {
                        printf("%s\r",komsuSehirTarayici->sehirAdi);
                        komsuSilAuto(komsuSehirTarayici,plaka);
                        komsuSehirTarayici = komsuSehirTarayici->ileri;
                    }
                    fprintf(yazilacakDosya,"%s Isimli sehir Silindi.\n",iter->sehirAdi);
                    root = sil(root,iter,plaka);

                }

                break;
            }
            iter = iter->ileri;
        }
    }
    else if(secim == 2)
    {

        printf("Sehir ismi giriniz: ");
        scanf("%s",sehirAdi);
        struct node * iter;
        iter = root;


        while(iter != NULL)
        {
            if(strcasecmp(iter->sehirAdi,sehirAdi) == 0)
            {
                plaka = iter->plaka;
                bolgeRenkleri(iter->bolge);
                printf("\n\nSilmek Istediginiz Sehirin Bilgileri [Isim Aramasi][%s]\n",sehirAdi);
                printf("Plaka: %d\t Sehir Adi: %s\t Bolge: %s\n\n",iter->plaka,iter->sehirAdi,iter->bolge);
                int status = 0;
                printf("Silmek icin 1 vazgecmek icin 0'a basiniz: ");
                scanf("%d",&status);
                searchStatus = 1;
                if(status == 0)
                {
                    break;
                }
                else if(status == 1)
                {
                    struct node *komsuSehirTarayici;
                    komsuSehirTarayici = root;
                    while(komsuSehirTarayici != NULL)
                    {
                        printf("%s\r",komsuSehirTarayici->sehirAdi);
                        komsuSilAuto(komsuSehirTarayici,plaka);
                        komsuSehirTarayici = komsuSehirTarayici->ileri;
                    }
                    fprintf(yazilacakDosya,"%s Isimli sehir Silindi.\n",iter->sehirAdi);
                    root = sil(root,iter,iter->plaka);

                }

                break;
            }
            iter = iter->ileri;
        }



    }

    if(searchStatus == 0)
    {

        if(secim == 1)
        {
            fprintf(yazilacakDosya,"Sehir Bilgileri [Plaka Aramasi][%d]\n",plaka);
            printf("\n\nSehir Bilgileri [Plaka Aramasi][%d]\n",plaka);
            fprintf(yazilacakDosya,"Sehir bulunamadi\n");
            printf("Sehir bulunamadi\n\n");

        }
        else if(secim == 2)
        {
            fprintf(yazilacakDosya,"Sehir Bilgileri [Isim Aramasi][%s]\n",sehirAdi);
            printf("\n\nSehir Bilgileri [Plaka Aramasi][%s]\n",sehirAdi);
            fprintf(yazilacakDosya,"Sehir bulunamadi\n");
            printf("Sehir bulunamadi\n\n");
        }

    }

    system("PAUSE");
    system("CLS");
}
void komsuCek()
{
    dosyaOku(1);
}
int komsuPlakaBul(struct node *r, char sehirAdi[20])
{
    struct node * iter;
    iter = r;
    while(iter != NULL)
    {

        if(strcmp(iter->sehirAdi,sehirAdi) == 0)
        {

            return iter->plaka;
        }
        iter = iter->ileri;
    }

    printf("!!Dosya hatali!!");
    exit(404);
    return -999;
}
int komsuKontrol(struct node* r,int plaka,int sehirPlaka)
{
    struct node * iter;
    iter = r;
    struct komsuNode * komIter;
    int status = 0; //0 sehir yok 1 sehir var 2 plaka hatali
    while(iter->plaka != sehirPlaka)
    {
        iter = iter->ileri;

    }

    komIter = (void *)iter->komsuNode;
    if(komIter == NULL)
    {
        status = 0;

    }
    while(komIter!=NULL)
    {
        if(komIter->komPlaka== plaka)
        {
            status = 1;
        }
        komIter= komIter->komIleri;
    }
    return status;
}
void komsuSilAuto(struct node *r,int plaka)
{
    struct komsuNode * kiter;
    struct komsuNode * kroot;
    kroot = (void *)r->komsuNode;
    kiter = (void *)r->komsuNode;
    int status;
    while(kiter != NULL)
    {

        if(kiter->komPlaka == plaka)
        {
            status =1;
            break;
        }
        kiter = kiter->komIleri;
    }
    if(status == 1)
    {

        kroot = komsuyusil(kroot,kiter,r,plaka);
    }
    else
    {
        //printf("\n!!!Komsu bulunamadi!!!\n");
    }
}
void sehirDuzenle()
{
    fprintf(yazilacakDosya,"\n");
    system("cls");
    fprintf(yazilacakDosya,"Sehir Duzenle\n");
    int plaka = 0;
    char sehirAdi[20];
    menuAdiOlustur("000",1,1);
    menuAdiOlustur("   SEHIR DUZENLE",10,0);
    menuAdiOlustur("     SEHRI BUL  ",11,0);
    menuAdiOlustur("1-)Plakaya Gore ",12,0);
    menuAdiOlustur("2-)Isime Gore   ",13,0);
    menuAdiOlustur("000",1,1);
    menuAdiOlustur("Secim Yap: ",15,2);
    int secim = 0;
    int sonuc = 0;

    scanf("%d",&secim);
    //int searchStatus = 0;

    if(secim == 1)
    {
        printf("Plaka Giriniz: ");
        scanf("%d",&plaka);
        sonuc = sehirKontrol(root,plaka);

    }
    else if(secim == 2)
    {
        printf("Sehir Adi Giriniz: ");
        scanf("%s",sehirAdi);
        sonuc = sehirIsimKontrol(root,sehirAdi);

    }
    if(sonuc == 1)
    {
        if(secim == 2)
        {
            struct node *sehirPlakaCevir;
            sehirPlakaCevir = root;
            while(sehirPlakaCevir != NULL)
            {
                if(strcasecmp(sehirPlakaCevir->sehirAdi,sehirAdi) == 0)
                {
                    break;
                }
                sehirPlakaCevir = sehirPlakaCevir->ileri;
            }
            plaka = sehirPlakaCevir->plaka;


        }
        char sehirAdi[20];
        char bolge[5];
        int yeniPlaka;
        printf("Plaka: ");
        scanf("%d",&yeniPlaka);
        printf("Sehir adi: ");
        scanf("%s",sehirAdi);
        printf("Bolge adi: ");
        scanf("%s",bolge);
        int yeniPlakaKontrol = sehirKontrol(root,yeniPlaka);
        int yeniIsimKontrol = sehirIsimKontrol(root,sehirAdi);
        if(yeniPlakaKontrol == 1)
        {
            fprintf(yazilacakDosya,"%d Plaka numarasina ait baska bir sehir var.\n",yeniPlaka);
            printf("Yeni plakaya ait baska bir sehir var.\n");
            system("PAUSE");
            sehirDuzenle();
        }
        else if(yeniIsimKontrol == 1)
        {
            fprintf(yazilacakDosya,"%s Sehir adina ait baska bir sehir var.\n",sehirAdi);
            printf("Yeni isime ait baska bir sehir var.%s\n ",sehirAdi);
            system("PAUSE");
            sehirDuzenle();
        }
        else if(yeniPlakaKontrol == 0 && yeniIsimKontrol == 0)
        {

            // Sehri Ekledik.
            root = ekle(root,yeniPlaka,sehirAdi,bolge,0);
            struct node *yeniSehir;
            struct node *eskiSehir;
            yeniSehir = root;
            eskiSehir = root;
            while(yeniSehir->plaka != yeniPlaka)
            {
                yeniSehir = yeniSehir->ileri;
            }
            while(eskiSehir->plaka != plaka)
            {
                eskiSehir = eskiSehir->ileri;
            }

            fprintf(yazilacakDosya,"Duzenleme Oncesi: [%d] %s %s %d\n",eskiSehir->plaka,eskiSehir->sehirAdi,eskiSehir->bolge,eskiSehir->komsu_sayisi);
            yeniSehir->komsuNode = eskiSehir->komsuNode;
            yeniSehir->komsu_sayisi = eskiSehir->komsu_sayisi;
            sil(root,eskiSehir,plaka);

            struct node * Yiter;
            Yiter = root;
            while(Yiter != NULL)
            {
                struct komsuNode *kroot;
                struct komsuNode *kiter;
                kroot = (void *)Yiter->komsuNode;
                kiter = kroot;
                int kont = 0;
                while(kiter != NULL)
                {
                    if(kiter->komPlaka == plaka)
                    {
                        kroot = komekle(kroot,yeniPlaka,Yiter->plaka);
                        kont = 1;
                    }

                    kiter = kiter->komIleri;
                }
                if(kont == 1)
                {
                    komsuSilAuto(Yiter,plaka);
                }
                Yiter= Yiter->ileri;
            }
            fprintf(yazilacakDosya,"Duzenleme Sonrasi: [%d] %s %s %d\n",yeniSehir->plaka,yeniSehir->sehirAdi,yeniSehir->bolge,yeniSehir->komsu_sayisi);
        }
    }
    else if(sonuc == 0)
    {
        // Sehir Yok
        printf("Sehir yok eklemek ister misiniz?\n");
        int soru;
        printf("Hayir ise 0 Evet ise 1");
        scanf("%d",&soru);
        switch(soru)
        {
        case 0:
            break;
        case 1:
            sehirEkle();
            break;
        }
    }
}
void komsuEkle(struct node *r,int sehirPlaka)
{
    fprintf(yazilacakDosya,"\n");
    fprintf(yazilacakDosya,"Komsu Ekle\n");

    /*
    printf("Eklemek istediginiz komsunun plakasini giriniz: ");
    int plaka;
    scanf("%d",&plaka);
    */

    int plaka = -999;
    char sehirAdi[20];
    //printf("Silmek istenilen komsunun plakasi: ");
    int secim;
    menuAdiOlustur("000",1,1);
    menuAdiOlustur("     ISLEMLER   ",10,0);
    menuAdiOlustur("1-)Isime gore   ",11,0);
    menuAdiOlustur("2-)Plakaya gore ",12,0);
    menuAdiOlustur("0-)Geri        ",15,0);
    menuAdiOlustur("000",1,1);
    menuAdiOlustur("Secim Yap: ",15,2);
    scanf("%d",&secim);

    switch(secim)
    {
    case 1:
        printf("Sehir Adi giriniz: ");
        struct node * iter;
        iter = root;
        scanf("%s",sehirAdi);
        while(iter != NULL)
        {
            if(strcasecmp(iter->sehirAdi,sehirAdi) == 0)
            {
                plaka = iter->plaka;
            }
            iter = iter->ileri;

        }


        break;
    case 2:

        printf("Plaka giriniz: ");
        scanf("%d",&plaka);
        break;
    case 0:
        system("cls");
        menu();
        break;
    }






    if(sehirKontrol(root,plaka)  == 0 || plaka == -999)
    {
        if(secim == 1)
        {
            fprintf(yazilacakDosya,"%s Sehir adina ait boyle bir sehir yok.\n",sehirAdi);
            printf("%s Sehir adina ait boyle bir sehir yok.\n",sehirAdi);
            printf("Sehir eklemek ister misiniz? 0 Hayir 1 Evet");
            int karar;
            scanf("%d",&karar);
            if(karar == 0)
            {
                menu();
            }
            else if(karar == 1)
            {
                sehirEkle();
            }
        }
        else if(secim == 2)
        {
            fprintf(yazilacakDosya,"%d Plaka numarasina ait boyle bir sehir yok.\n",plaka);
            printf("%d Plaka numarasina ait boyle bir sehir yok.\n",plaka);
            printf("Sehir eklemek ister misiniz? 0 Hayir 1 Evet");
            int karar;
            scanf("%d",&karar);
            if(karar == 0)
            {
                menu();
            }
            else if(karar == 1)
            {
                sehirEkle();
            }
        }
    }
    else if(sehirKontrol(root,plaka) == 1 && plaka != -999)
    {
        if(plaka != sehirPlaka)
        {
            struct komsuNode *k;
            k = (void *)r->komsuNode;
            k = komekle(k,plaka,sehirPlaka);
            struct node *a;


            a = root;

            while(a->ileri != NULL)
            {
                if(a->plaka == plaka)
                {
                    break;
                }
                a = a->ileri;
            }

            struct komsuNode *kk;
            kk = (void *)a->komsuNode;
            kk = komekle(kk,sehirPlaka,plaka);

            fprintf(yazilacakDosya,"Komsu Eklendi. Plaka : %d\n",plaka);
            komsulariniGetir(r);

        }
        else
        {
            fprintf(yazilacakDosya,"Kendinizi komsu ekleyemezsiniz...\n");
            printf("Kendinizi komsu ekleyemezsiniz...\n");
        }

    }
    system("PAUSE");
    system("cls");
}
void komsuIslemMenu(struct node *iter,int sehirPlaka)
{

    menuAdiOlustur("000",1,1);
    menuAdiOlustur(" KOMSU ISLEMLERI",5,0);
    menuAdiOlustur(" 1-) Komsu sil  ",4,0);
    menuAdiOlustur(" 2-) Komsu ekle ",3,0);
    menuAdiOlustur(" 0-) Geri git   ",2,0);
    menuAdiOlustur("000",1,1);
    menuAdiOlustur("Secim Yap: ",15,2);


    int menu;
    scanf("%d",&menu);
    switch(menu)
    {
    case 1:
        komsuSil(iter);
        break;
    case 2:
        komsuEkle(iter,sehirPlaka);
    }
}
int sehirIsimKontrol(struct node *r,char sehirAdi[20])
{
    struct node * iter;
    iter = r;
    int status = 0; //0 sehir yok 1 sehir var

    while(iter != NULL)
    {
        if(strcasecmp(iter->sehirAdi,sehirAdi) == 0)
        {

            status = 1;
            break;
        }
        iter = iter->ileri;
    }

    return status;

}
void dosyaYazma()
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    system("mkdir outputs");
    system("cls");
    yazilacakDosya = fopen("outputs/output.txt", "a");
    fprintf(yazilacakDosya,"Olusturulma Tarihi : %s\n",asctime(tm));
}
void menuAdiOlustur(char menuAdi[100],int renk,int son)
{
    HANDLE hConsole;
    unsigned short int colors;
    hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    if(son == 0)
    {

        colors = 3;
        SetConsoleTextAttribute(hConsole, colors);
        printf("\t\t              |                    ");
        colors = renk;
        SetConsoleTextAttribute(hConsole, colors);
        printf("%s",menuAdi);
        colors = 3;
        SetConsoleTextAttribute(hConsole, colors);
        printf("                      |\n");


    }
    else if(son == 1)
    {
        colors = 3;
        SetConsoleTextAttribute(hConsole, colors);
        printf("\t\t              ############################################################\n");
    }
    else if(son == 2)
    {
        colors = 3;
        SetConsoleTextAttribute(hConsole, colors);
        printf("\t\t               ");
        colors = renk;
        SetConsoleTextAttribute(hConsole, colors);
        printf("%s",menuAdi);
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}
void renkDegistir(int renk)
{
    HANDLE hConsole;
    hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, renk);
}
void bolgeRenkleri(char bolge[5])
{
    if(strcasecmp(bolge,"MA") == 0)
        renkDegistir(1);
    else if(strcasecmp(bolge,"IA") == 0)
        renkDegistir(14);
    else if(strcasecmp(bolge,"KA") == 0)
        renkDegistir(2);
    else if(strcasecmp(bolge,"AK") == 0)
        renkDegistir(4);
    else if(strcasecmp(bolge,"DA") == 0)
        renkDegistir(5);
    else if(strcasecmp(bolge,"EG") == 0)
        renkDegistir(15);
    else if(strcasecmp(bolge,"GA") == 0)
        renkDegistir(11);
    else
        renkDegistir(15);

}

void kriterArama()
{
    fprintf(yazilacakDosya,"\n");
    system("cls");
    int min,max;
    printf("Kritere gore arama\n");
    printf("Minimum komsu sayisi giriniz: ");
    scanf("%d",&min);
    printf("Maxsimum degerini 0 tusuna basarak devre disi birakabilirsiniz.\n");
    printf("Maksimum komsu sayisi giriniz: ");
    scanf("%d",&max);
    if(max == 0)
    {
        max = 999999;
    }
    struct node * iter;
    iter = root;
    fprintf(yazilacakDosya,"Minimum Komsu Sayisi: %d\n",min);
    fprintf(yazilacakDosya,"Maksimum Komsu Sayisi(0 sonsuzu gosterir): %d\n",max);
    // [SehirAdeti][KomsuAdeti]


    struct node * sehirSay;
    sehirSay = root;
    int sehirSayisi = 0;
    while(sehirSay != NULL)
    {
        sehirSayisi++;
        sehirSay = sehirSay->ileri;
    }

    int plakalar[sehirSayisi][max];
    for(int i = 0; i<sehirSayisi; i++)
    {
        for(int k = 1; k< max; k++)
        {
            plakalar[i][k] = -99;

        }
    }
    int kosulluSehirler = 0;
    while(iter != NULL)
    {
        if(iter->komsu_sayisi >= min && iter->komsu_sayisi<= max)
        {


            bolgeRenkleri(iter->bolge);
            fprintf(yazilacakDosya,"Plaka:[%d] \t Sehir Adi:%s\tBolge: %s \t Komsu Sayisi: %d\n",iter->plaka,iter->sehirAdi,iter->bolge,iter->komsu_sayisi);
            printf("Plaka:[%d] \t Sehir Adi:%s \t Bolge: %s \t Komsu Sayisi: %d\t",iter->plaka,iter->sehirAdi,iter->bolge,iter->komsu_sayisi);
            struct komsuNode * komNode;
            komNode = (void *)iter->komsuNode;
            plakalar[kosulluSehirler][0] = iter->plaka;

            int komSehirler = 1;
            while(komNode != NULL)
            {

                plakalar[kosulluSehirler][komSehirler] = komNode->komPlaka;

                renkDegistir(15);
                //printf(" [%d] ",komNode->komPlaka);
                komSehirler++;
                komNode = komNode->komIleri;

            }
            printf("\n");
            printf("------------------------------------------------------------\n");



            kosulluSehirler++;
        }

        iter = iter->ileri;
    }

    printf("Ozel Arama Yapma Ister Misiniz ? (Hayir 0) (Evet 1)");
    int ozelSecim;
    scanf("%d",&ozelSecim);
    if(ozelSecim == 1)
    {
        int plakaOrIsim;
        menuAdiOlustur("000",1,1);
        menuAdiOlustur("1-) Isime gore  ",4,0);
        menuAdiOlustur("2-) Plakaya gore",3,0);
        menuAdiOlustur("0-) Geri  git   ",3,0);
        menuAdiOlustur("000",1,1);
        menuAdiOlustur("Secim Yap: ",15,2);
        scanf("%d",&plakaOrIsim);
        int KriterPlakalar[sehirSayisi];
        int sayac = 0;
        KriterPlakalar[0] = -99;
hataliSecim:
        if(plakaOrIsim == 1)
        {
            int temp = 0;
            while(temp != 1)
            {
                char tempSehirAdi[20];

                printf("%d. Sehir adini giriniz: Tamamlandiysa 0 giriniz: ", sayac+1);
                scanf("%s",tempSehirAdi);
                if(tempSehirAdi[0] == '0')
                {
                    temp = 1;
                }
                else
                {

                    int tempPlaka = sehirToPlaka(tempSehirAdi);
                    if(tempPlaka == -99)
                    {
                        printf("%s adinda bir sehir sistemde kayitli degildir.\n",tempSehirAdi);
                        goto hataliSecim;
                    }
                    KriterPlakalar[sayac] = tempPlaka;
                    sayac++;
                }
            }

        }
        else if(plakaOrIsim == 2)
        {
            int temp = 0;

            while(temp != 1)
            {

                int tempPlaka = -999;
                printf("%d. Sehir plakasini giriniz: Tamamlandiysa 0 giriniz: ", sayac+1);
                scanf("%d",&tempPlaka);
                if(tempPlaka == 0)
                {
                    temp = 1;
                }
                else
                {
                    if(sehirKontrol(root,tempPlaka) == 0)
                    {
                        printf("%d plakali sehir sistemde kayitli degildir.\n",tempPlaka);
                        goto hataliSecim;
                    }
                    KriterPlakalar[sayac] = tempPlaka;
                    sayac++;
                }
            }
        }
        int i = 0;
        while(i < sayac)
        {
            if(sehirKontrol(root,KriterPlakalar[i]) == 0)
            {
                printf("Boyle bir sehir sistemde yok %d",KriterPlakalar[i]);
                printf("Arama menusune yonlendiriliyorsunuz");
                system("PAUSE");
                system("cls");
                sehirAra();
            }
            i++;
        }


        /*
        AnaSehirPlaka
        KomsuSehirPlaka
        EkrandanAlinanPlaka
        A | Kom | Gir
        1 | 2 3 |  1
        2 | 1 3 |  2
        3 | 1 2 |

        */
        int yokMesaji = 1;
        if(KriterPlakalar[0] != -99)
        {



            printf("Aranan Sehirler\n");
            fprintf(yazilacakDosya,"Aranan Sehirler\n");
            for(int i = 0; i<sayac; i++)
            {
                sehirGetir(KriterPlakalar[i]);
            }
            printf("Ortak Sehirler Listesi\n");
            fprintf(yazilacakDosya,"Ortak Sehirler Listesi\n");

            for(int i = 0; i< sehirSayisi; i++)
            {
                int varMi = 0;
                for(int k = 1; k< max; k++)
                {

                    for(int l = 0; l< sayac; l++)
                    {
                        if(plakalar[i][k] == KriterPlakalar[l])
                        {


                            varMi++;
                            //printf("%d %d %d %d\n",sayac,varMi,KriterPlakalar[l],plakalar[i][k]);
                        }
                    }




                }
                if(varMi == sayac)
                {
                    //system("PAUSE");
                    sehirGetir(plakalar[i][0]);
                    yokMesaji = 0;
                }
                varMi = 0;


            }
        }
        if(yokMesaji == 1 && KriterPlakalar[0] == -99)
        {
            printf("Bu kriterlere uygun ortak sehirler bulunamadi.\n");
            fprintf(yazilacakDosya,"Bu kriterlere uygun ortak sehirler bulunamadi.\n");

        }


        system("PAUSE");
    }
}
