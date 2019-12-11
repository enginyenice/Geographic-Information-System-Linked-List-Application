#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void menu();
void sehirEkle();
void sehirAra();
void isimArama();
void plakaArama();
struct node
{
    int plaka;
    char sehirAdi[20];
    char bolge[5];
    int komsu_sayisi;
    struct node * ileri;
    struct node * geri;

};
struct node * root;


struct node * ekle(struct node * r,int plaka,char sehirAdi[20],char bolge[5],int komsu_sayisi){
    if(r == NULL)
    {
        r = (struct node*)malloc(sizeof(struct node));
        r->ileri = NULL;
        r->geri = NULL;


        r->plaka = plaka;
        r->komsu_sayisi = komsu_sayisi;
        strcpy(r->sehirAdi,sehirAdi);
        strcpy(r->bolge,bolge);


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
                return r;
            }
        }
    }
    return r;
};
int sehirKontrol(struct node* r,int plaka){
    struct node * iter;
    iter = r;
    int status = 0; //0 sehir yok 1 sehir var
    while(iter != NULL)
    {
        if(iter->plaka == plaka)
        {
            status = 1;
        }
        iter = iter->ileri;
    }

    return status;
}
void ekranaYaz(struct node* r){
    system("cls");
    struct node * iter;
    iter = r;
    if(iter == NULL)
    {
        printf("Liste Bos\n");
    }
    else {

        while(iter != NULL)
    {
        printf(">> [%d] %s %s\n",iter->plaka,iter->sehirAdi,iter->bolge);
        iter = iter->ileri;
    }
    }

}
int main(){
    root = NULL;
    while(1)
    {
        menu();
    }

    return 0;
}
void menu(){
    int secim;
    printf("Bir deger giriniz...\n");
    printf("1-)Sehir Listesi\n");
    printf("2-)Sehir Ekle\n");
    printf("3-)Arama Yap\n");
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
    case 9:
        printf("Gule gule\n");
        exit(0);
        break;
    }

}
void sehirEkle(){

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
    } else {
        printf("Boyle bir sehir var. Tekrar ekleyemessiniz\n");
    }


}
void sehirAra(){
    system("cls");
    int secim;
    printf("Arama Tipi\n");
    printf("1-) Isim\n");
    printf("2-) Plaka\n");
    scanf("%d",&secim);
    system("cls");
    switch(secim){
    case 1:
        isimArama();
        break;
    case 2:
        plakaArama();
        break;
    }

}
void isimArama(){
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
            break;
        }
        iter = iter->ileri;
    }
        if(searchStatus == 0)
    {
         printf("\n\nSehir Bilgileri [Plaka Aramasi][%s]\n",sehirAdi);
        printf("Sehir bulunamadi\n\n");
    }


}
void plakaArama(){
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
            searchStatus = 1;
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





