#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<locale.h>
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
void menu();
void sehirEkle();
void sehirAra();
void isimArama();
void plakaArama();
void dosyaOku(int status);
void sehirSil();
void bolgeAra();
void komsuCek();
struct komsuNode * komekle(struct komsuNode* r,int komPlaka,int sehirPlaka);
void parcala(char kelime[200],int status);
struct node * ekle(struct node * r,int plaka,char sehirAdi[20],char bolge[5],int komsu_sayisi);
struct node * sil(struct node * r,struct node *iter,int plaka);
int komsuPlakaBul(struct node *r, char sehirAdi[20]);
int komsuKontrol(struct node* r,int plaka,int sehirPlaka);
void komsulariniGetir(struct node * r);
int komsuKontrol(struct node* r,int plaka,int sehirPlaka);
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
        Globaliter->komsuNode = r;
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
            Globaliter->komsuNode = temp;
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

        r->komsuNode = temp;

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
            r->komsuNode = kroot;

            return kroot;
        }
        else if(niter->komIleri == NULL)
        {
            free(niter->komIleri);
            r->komsuNode = kroot;

            r->komsu_sayisi = r->komsu_sayisi - 1;
            return kroot;


        }
    }







    return kroot;

};

struct node * sil(struct node * r,struct node *iter,int plaka)
{

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
    system("cls");
    struct node * iter;
    iter = r;
    if(iter == NULL)
    {
        printf("Liste Bos\n");
    }
    else
    {

        while(iter != NULL)
        {
            printf(">> [%d] %s %s %d, ",iter->plaka,iter->sehirAdi,iter->bolge,iter->komsu_sayisi);
            struct komsuNode *kom;
            kom = iter->komsuNode;
            while(kom != NULL)
            {
                printf("[%d]",kom->komPlaka);
                kom = kom->komIleri;

            }
            iter = iter->ileri;
            printf("\n");
        }
    }

}
int main()
{
    setlocale(LC_ALL, "Turkish");
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
    printf("Bir deger giriniz...\n");
    printf("1-)Sehir Listesi\n");
    printf("2-)Sehir Ekle\n");
    printf("3-)Arama Yap\n");
    printf("4-)Sehir Sil\n");
    printf("9-)Cikis Yap\n");
    printf("Secim: ");
    scanf("%d",&secim);
    switch(secim)
    {
    case 1:
        ekranaYaz(root);
        break;
    case 2:
        sehirEkle();
        break;
    case 3:
        sehirAra();
        break;
    case 4:
        sehirSil();
        break;
    case 9:
        printf("Gule gule\n");
        exit(0);
        break;
    }

}
void komsuSil(struct node *r)
{
    int plaka;
    printf("Silmek istenilen komsunun plakasi: ");
    scanf("%d",&plaka);
    struct komsuNode * kiter;
    struct komsuNode * kroot;
    kroot = r->komsuNode;
    kiter = r->komsuNode;
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
    } else {
        printf("\n!!!Komsu bulunamadi!!!\n");
    }


}
void sehirEkle()
{

    system("cls");
    int plaka;
    char  sehirAdi[20];
    char  bolge[5];
    printf("Sehir Ekle:\n");
    printf("Plaka No:" );
    scanf("%d",&plaka);
    printf("Sehir Adi:" );
    scanf("%s",sehirAdi);
    printf("Bolge:" );
    scanf("%s",bolge);
    if(sehirKontrol(root,plaka)  == 0)
    {
        root = ekle(root,plaka,sehirAdi,bolge,0);

    }
    else if(sehirKontrol(root,plaka) == 1)
    {
        printf("Boyle bir sehir var. Tekrar ekleyemessiniz\n");
    }
    else
    {
        printf("Plaka Hatali %d",plaka);
    }


}
void sehirAra()
{
    system("cls");
    int secim;
    printf("Arama Tipi\n");
    printf("1-) Isim\n");
    printf("2-) Plaka\n");
    printf("3-) Bolge\n");
    printf("4-) Kritere Gore Arama\n");
    printf("Secim yapiniz: ");
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
void kriterArama()
{
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
    while(iter != NULL)
    {
        if(iter->komsu_sayisi > min && iter->komsu_sayisi< max)
        {
            printf("Plaka:[%d]\tSehir Adi:%s\tBolge: %s\tKomsu Sayisi: %d\n",iter->plaka,iter->sehirAdi,iter->bolge,iter->komsu_sayisi);
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
            printf("\n\nSehir Bilgileri [Isim Aramasi][%s]\n",sehirAdi);
            printf("Plaka: %d\t Sehir Adi: %s\t Bolge: %s\n\n",iter->plaka,iter->sehirAdi,iter->bolge);
            komsulariniGetir(iter);
            printf("Toplam Komsu Sayisi: %d\n",iter->komsu_sayisi);
            searchStatus = 1;
            int status;
            printf("Komsunu silmek ister misiniz ?  0 Hayir 1 Evet: ");
            scanf("%d",&status);
            if(status == 0)
            {
                break;
            }
            else if(status == 1)
            {
                komsuSil(iter);
            }
            break;
        }
        iter = iter->ileri;
    }
    if(searchStatus == 0)
    {
        system("cls");
        printf("Sehir Bilgileri [Plaka Aramasi][%s]\n",sehirAdi);
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
            printf("\n\nSehir Bilgileri [Plaka Aramasi][%d]\n",plaka);
            printf("Plaka: %d\t Sehir Adi: %s\t Bolge: %s\n\n",iter->plaka,iter->sehirAdi,iter->bolge);
            komsulariniGetir(iter);
            printf("Toplam Komsu Sayisi: %d\n",iter->komsu_sayisi);
            searchStatus = 1;
            int status;
            printf("Komsunu silmek ister misiniz ?  0 Hayir 1 Evet: ");
            scanf("%d",&status);
            if(status == 0)
            {
                break;
            }
            else if(status == 1)
            {
                komsuSil(iter);
            }
            break;
        }
        iter = iter->ileri;
    }
    if(searchStatus == 0)
    {
        system("cls");
        printf("Sehir Bilgileri [Plaka Aramasi][%d]\n",plaka);
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
    iter = root;
    kNode = r->komsuNode;

    printf("Komsu Bilgileri\n");
    while(kNode != NULL)
    {

        while(iter != NULL)
        {

            if(kNode->komPlaka == iter->plaka)
            {
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
        if(status == 0)
            printf("Sehir Listesi Aktariliyor...\n");
        else if(status == 1)
            printf("Komsu Listesi Aktariliyor...\n");


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

        printf("Ana dizinde sehirler.txt dosyasi bulunamadi.!!!");
        exit(404);

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
    char bolge[5];
    printf("Bolge kisaltmasini giriniz: ");
    scanf("%s",bolge);
    struct node * iter;
    iter = root;
    int searchStatus = 0;
    printf("Bolge Bilgileri [Bolge Aramasi][%s]\n",bolge);
    while(iter != NULL)
    {
        if(strcmp(iter->bolge,bolge) == 0)
        {

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


}
void sehirSil()
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
            printf("\n\nSilmek Istediginiz Sehirin Bilgileri [Plaka Aramasi][%d]\n",plaka);
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
                root = sil(root,iter,plaka);

            }

            break;
        }
        iter = iter->ileri;
    }
    if(searchStatus == 0)
    {
        printf("\n\nSehir Bilgileri [Plaka Aramasi][%d]\n",plaka);
        printf("Sehir bulunamadi\n\n");
    }


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

    komIter = iter->komsuNode;
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
    //printf("Plaka: %d\n",plaka);
    struct komsuNode * kiter;
    struct komsuNode * kroot;
    kroot = r->komsuNode;
    kiter = r->komsuNode;
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
    } else {
      //  printf("\n!!!Komsu bulunamadi!!!\n");
    }


}
