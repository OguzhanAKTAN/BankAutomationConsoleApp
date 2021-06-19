#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void beklet(int saniye);

struct musteri
{
    char isim[50];
    char hspturu[7];
    int hspkontrol;
    int numara;
    float bakiye;
    float havale_ucret;
    float ek_hesap;
};
struct bos
{
    char bos_isim[50];
};

void random_numara(struct musteri *);
void ana_menu(int musteri_sayisi,struct musteri *,struct bos *);
void yeni_hesap(int musteri_sayisi,struct musteri *,struct bos *);
void giris(int musteri_sayisi,struct musteri *,struct bos *);
void musteri_menu(int bulunan_mst,int musteri_sayisi,struct musteri *,struct bos *);
void admin_giris(int musteri_sayisi,struct musteri *,struct bos *);
void para_cekme(char gecici2[],int boyut,int bulunan_mst,struct musteri *);
void para_yatirma(char gecici2[],int boyut,int bulunan_mst,struct musteri *);
void havale(char gecici2[],int boyut,int bulunan_mst,struct musteri *,struct bos *);
void hesap_kapama(int musteri_sayisi,int bulunan_mst,struct musteri *,struct bos *);
void admin_hesap_kapama(int musteri_sayisi,struct musteri *,struct bos *);
void admin_hesap_blok(int blok_sayac,struct musteri *,struct bos *);
void admin_blok_kaldir(int blok_sayac,struct musteri *,struct bos *);

int main()
{
    FILE *bireysel;
    FILE *ticari;
    int r;
    struct bos bsm[100];
    struct musteri mst[100];

    for(r=0;r<100;r++)
    {
        strcpy(mst[r].isim, "");
        strcpy(bsm[r].bos_isim, "");
        mst[r].bakiye=0;
        mst[r].hspkontrol=1;
    }
    int musteri_sayisi=0;
    random_numara(mst);

    if((bireysel = fopen("BIREYSEL.txt","r")) == NULL)
    {
        printf("\nDosya Okuma Hatasi\n");
        exit(1);
    }
    else
    {
        for(r=0;r<100;r++)
            {

                fscanf(bireysel,"%s %s %d %d %f %f",&mst[r].hspturu,&mst[r].isim,&mst[r].hspkontrol,&mst[r].numara,&mst[r].bakiye,&mst[r].ek_hesap);
            }
        fclose(bireysel);
    }
    if((ticari = fopen("TICARI.txt","r")) == NULL)
    {
        printf("\nDosya Okuma Hatasi\n");
        exit(1);
    }
    else
    {
        for(r=0;r<100;r++)
            {
                if(strcmp(mst[r].isim,bsm[r].bos_isim)==0)
                {
                    fscanf(ticari,"%s %s %d %d %f %f",&mst[r].hspturu,&mst[r].isim,&mst[r].hspkontrol,&mst[r].numara,&mst[r].bakiye,&mst[r].ek_hesap);
                }
                else
                {}

            }
        fclose(ticari);
    }
    ana_menu(musteri_sayisi,mst,bsm);
    return 0;
}
void random_numara(struct musteri *mst1)
{
    int i,j,temp;



    for(i=0;i<=99;i++)
    {
        temp=rand() % 100;
        for(j=0;j<=i-1;j++)
        {
            if(temp==mst1[j].numara)
                break;
        }
        if(i==j)
            mst1[i].numara=temp;
        else
            i--;
    }


}
void ana_menu(int musteri_sayisi,struct musteri *mst1,struct bos *bsm1)
{
    int admin_num,admin_sifre,c;
    char secim;
    musteri_sayisi=0;

        for (c=0;c<100;c++)
    {
        if(strcmp(mst1[c].isim,bsm1[c].bos_isim))
        {
            musteri_sayisi++;
        }
        else
        {}
    }

    beklet(2);
    printf("\n/////ANA MENU/////\n\n");
    beklet(2);
    printf("1.Yeni Hesap Acma\n");
    beklet(2);
    printf("2.Giris Yap\n");
    beklet(2);
    printf("3.Admin Girisi\n");
    beklet(2);
    printf("4.Programi Kapat\n");

    printf("\nSeciminiz (1-4) : "); scanf("%s",&secim);


    switch (secim)
    {
    case '0':
        ana_menu(musteri_sayisi,mst1,bsm1);
        break;
    case '1':
        yeni_hesap(musteri_sayisi,mst1,bsm1);
        printf("\n\nHesabiniz Basariyla olusturuldu!\n\n");
        beklet(50);
        ana_menu(musteri_sayisi,mst1,bsm1);
        break;
    case '2':
        giris(musteri_sayisi,mst1,bsm1);
        break;
    case '3':
        printf("\nAdmin Numara: "); scanf("%d",&admin_num);
        printf("Admin Sifre : "); scanf("%d",&admin_sifre);
        if(admin_num==9999 && admin_sifre==1234)
        {
            admin_giris(musteri_sayisi,mst1,bsm1);
        }
        else
        {
            printf("\nHatali Giris Yaptiniz\n");
            ana_menu(musteri_sayisi,mst1,bsm1);
        }
    case '4':
        exit(0);
        break;
    default:
        printf("\nHatali Giris Yaptiniz\n");
        ana_menu(musteri_sayisi,mst1,bsm1);

    }



}
void yeni_hesap(int musteri_sayisi, struct musteri *mst1, struct bos *bsm1)
{
    FILE *dekont;
    FILE *bireysel2;
    FILE *ticari2;
    char gecici[50];
    time_t t;
    int j,m=0;
    char hsp;
    t = time(NULL);
    for(j=0;j<100;j++)
    {
            if(strcmp(bsm1[j].bos_isim,mst1[m].isim))
            {
                m++;
                if(m==100)
                {
                    printf("\nMusteri Kapasitesi Dolu!!\n");
                    ana_menu(musteri_sayisi,mst1,bsm1);

                }
            }
            else
            {
                printf("\nHesap Turunu Seciniz\n");
                printf("\n1.Bireysel");
                printf("\n2.Ticari\n");
                printf("\nSeciminiz (1-2): "); scanf("%s",&hsp);
                switch(hsp)
                {
                case '1':
                strcpy(mst1[m].hspturu,"BIREYSEL");
                mst1[m].ek_hesap=500;
                printf("\nAdiniz : "); scanf("%s",mst1[m].isim);
                printf("\nMusteri Numaraniz = %d",mst1[m].numara);
                if((bireysel2 = fopen("BIREYSEL.txt","a+")) == NULL)
                {
                    printf("Dosya Acma Hatasi!\n");
                    exit(1);
                }
                fprintf(bireysel2,"%s %s %d %d %.2f %.2f ",mst1[m].hspturu,mst1[m].isim,mst1[m].hspkontrol,mst1[m].numara,mst1[m].bakiye,mst1[m].ek_hesap);
                fclose(bireysel2);
                itoa(mst1[m].numara,gecici,10);
                strcat(gecici,mst1[m].isim);
                strcat(gecici,".txt");
                if((dekont = fopen(gecici,"w+")) == NULL)
                {
                    printf("Dosya Acma Hatasi!\n");
                    exit(1);
                }
                fprintf(dekont,"%s%d NUMARALI %s HESABI ACILDI\n-------------------",ctime(&t),mst1[m].numara,mst1[m].isim);
                fclose(dekont);
                break;
                case '2':
                strcpy(mst1[m].hspturu,"TICARI");
                mst1[m].ek_hesap=1000;
                printf("\nAdiniz : "); scanf("%s",mst1[m].isim);
                printf("\nMusteri Numaraniz = %d",mst1[m].numara);
                if((ticari2 = fopen("TICARI.txt","a+")) == NULL)
                {
                    printf("Dosya Acma Hatasi!\n");
                    exit(1);
                }
                fprintf(ticari2,"%s %s %d %d %.2f %.2f ",mst1[m].hspturu,mst1[m].isim,mst1[m].hspkontrol,mst1[m].numara,mst1[m].bakiye,mst1[m].ek_hesap);
                fclose(ticari2);
                itoa(mst1[m].numara,gecici,10);
                strcat(gecici,mst1[m].isim);
                strcat(gecici,".txt");
                if((dekont = fopen(gecici,"w+")) == NULL)
                {
                    printf("Dosya Acma Hatasi!\n");
                    exit(1);
                }
                fprintf(dekont,"%s%d NUMARALI %s HESABI ACILDI\n-------------------",ctime(&t),mst1[m].numara,mst1[m].isim);
                fclose(dekont);
                break;
                default:
                printf("\nHATALI GIRIS YAPTINIZ\n");
                ana_menu(musteri_sayisi,mst1,bsm1);
                break;
                }
                break;
            }

    }
}
void giris(int musteri_sayisi,struct musteri *mst1,struct bos *bsm1)
{
    int num_giris,bulunan_mst,k;

    printf("\nMusteri Numaranizi Giriniz : "); scanf("%d",&num_giris);
    for(k=0;k<100;k++)
    {
        if(num_giris==mst1[k].numara)
        {
            bulunan_mst=k;
            if(mst1[bulunan_mst].hspkontrol==0)
            {
                printf("\nHESABINIZ BLOKE EDILMIS DURUMDA!\n");
                ana_menu(musteri_sayisi,mst1,bsm1);
            }
            if(strcmp(bsm1[bulunan_mst].bos_isim,mst1[bulunan_mst].isim))
            {
                musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
            }
            else
            {
                printf("\nDaha Kayitli Musteri Bulunmamaktadir!!\n");
                ana_menu(musteri_sayisi,mst1,bsm1);
            }
        }
    }
    if(bulunan_mst=-1)
    {
        printf("\nBu Numaraya Sahip Kayitli Musteri Bulunmamaktadir!\n");
        ana_menu(musteri_sayisi,mst1,bsm1);
    }
}
void musteri_menu(int bulunan_mst,int musteri_sayisi,struct musteri *mst1,struct bos *bsm1)
{
    FILE *dekont2;
    FILE *bireysel3;
    FILE *ticari3;
     char giris_secim;
     int s;
     char gecici2[50],dekont[500];
     char ek_hsp_onay;
     float ek_bakiye;
     time_t tmenu;

     if((bireysel3 = fopen("BIREYSEL.txt","w+")) == NULL)
     {
         printf("\nDosya Acma Hatasi\n");
         exit(1);
     }
     for(s=0;s<100;s++)
     {
         if(strcmp(bsm1[s].bos_isim,mst1[s].isim))
         {
            if(strcmp(mst1[s].hspturu, "BIREYSEL") == 0)
            {
                fprintf(bireysel3,"%s %s %d %d %.2f %.2f ",mst1[s].hspturu,mst1[s].isim,mst1[s].hspkontrol,mst1[s].numara,mst1[s].bakiye,mst1[s].ek_hesap);
            }
            else
            {}
         }
         else
         {}
     }
     fclose(bireysel3);
    if((ticari3 = fopen("TICARI.txt","w+")) == NULL)
     {
         printf("\nDosya Acma Hatasi\n");
         exit(1);
     }
     for(s=0;s<100;s++)
     {
         if(strcmp(bsm1[s].bos_isim,mst1[s].isim))
         {
             if(strcmp(mst1[s].hspturu, "TICARI") == 0)
             {
                 fprintf(ticari3,"%s %s %d %d %.2f %.2f ",mst1[s].hspturu,mst1[s].isim,mst1[s].hspkontrol,mst1[s].numara,mst1[s].bakiye,mst1[s].ek_hesap);
             }
             else
             {}
         }
         else
         {}
     }
     fclose(ticari3);
     itoa(mst1[bulunan_mst].numara,gecici2,10);
     strcat(gecici2,mst1[bulunan_mst].isim);
     strcat(gecici2,".txt");



            printf("\n%s HESAP\n",mst1[bulunan_mst].hspturu);
            beklet(2);
            printf("Ek Hesap Limitiniz :%.2f\n",mst1[bulunan_mst].ek_hesap);
            beklet(2);
            printf("\nAdiniz: %s\nMusteri Numaraniz: %d\nBakiyeniz: %.2f",mst1[bulunan_mst].isim,mst1[bulunan_mst].numara,mst1[bulunan_mst].bakiye);
            beklet(2);
            printf("\n\n/////MENU/////\n\n");
            beklet(2);
            printf("1.Ek Hesaptan Para Cek\n");
            beklet(2);
            printf("2.Para Cek\n");
            beklet(2);
            printf("3.Para Yatir\n");
            beklet(2);
            printf("4.Havale Yap\n");
            beklet(2);
            printf("5.Hesabi Kapa\n");
            beklet(2);
            printf("6.Dekont AL\n");
            beklet(2);
            printf("7.Ek Hesabi Sifirla\n");
            beklet(2);
            printf("0.Ana Menuye Don\n\n");

            printf("Seciminiz (1-4): "); scanf("%s",&giris_secim);
            switch(giris_secim)
            {
            case '0':
                ana_menu(musteri_sayisi,mst1,bsm1);
                break;
            case '1':
                printf("\nCekmek Isdetiginiz Miktar :"); scanf("%f",&ek_bakiye);
                if(ek_bakiye>mst1[bulunan_mst].ek_hesap)
                {
                    printf("\nBu Islem Icin Ek Hesap Limitiniz Yeterli Degildir!\n");
                    musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                }
                else
                {
                    mst1[bulunan_mst].bakiye=mst1[bulunan_mst].bakiye+ek_bakiye;
                    mst1[bulunan_mst].ek_hesap=mst1[bulunan_mst].ek_hesap-ek_bakiye;
                    if((dekont2 = fopen(gecici2,"a+"))==NULL)
                    {
                        printf("\nDosya Yazma Hatasi\n");
                        exit(1);
                    }
                    tmenu = time(NULL);
                    fprintf(dekont2,"\n%s%.2f TL EK HESAPTAN PARA CEKILDI\nBakiye:%.2f\n-------------------",ctime(&tmenu),ek_bakiye,mst1[bulunan_mst].bakiye);
                    fclose(dekont2);
                    musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                }
                break;
            case '2':
                if(strcmp(mst1[bulunan_mst].hspturu, "BIREYSEL") == 0)
                {
                  printf("\nBireysel Hesaplar Icin Para Cekme Limiti 750 TL Dir!\n");
                }
                if(strcmp(mst1[bulunan_mst].hspturu, "TICARI") == 0)
                {
                  printf("\nTicari Hesaplar Icin Para Cekme Limiti 1500 TL Dir!\n");
                }
                para_cekme(gecici2,50,bulunan_mst,mst1);
                musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                break;
            case '3':
                para_yatirma(gecici2,50,bulunan_mst,mst1);
                musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                break;
            case '4':
                havale(gecici2,50,bulunan_mst,mst1,bsm1);
                musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                break;
            case '5':
                if(mst1[bulunan_mst].bakiye!=0)
                {
                    printf("\nHesap Kapatmak Icin Bakiyenizin 0 Olmasi Gerekir!\n");
                    musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                }
                if(strcmp(mst1[bulunan_mst].hspturu, "BIREYSEL") == 0)
                {
                    if(mst1[bulunan_mst].ek_hesap!=500)
                    {
                        printf("\nHesap Kapatmak Icin Ek Hesap Limitinizin 500 TL Olmasi Gerekir!\n");
                        musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                    }
                    else
                    {
                       hesap_kapama(musteri_sayisi,bulunan_mst,mst1,bsm1);
                       if((bireysel3 = fopen("BIREYSEL.txt","w+"))==NULL)
                       {
                           printf("\nDosya Yazma Hatasi\n");
                           exit(1);
                       }
                            for(s=0;s<100;s++)
                            {
                                if(strcmp(bsm1[s].bos_isim,mst1[s].isim))
                                {
                                    if(strcmp(mst1[s].hspturu, "BIREYSEL") == 0)
                                    {
                                        fprintf(bireysel3,"%s %s %d %d %.2f %.2f ",mst1[s].hspturu,mst1[s].isim,mst1[s].hspkontrol,mst1[s].numara,mst1[s].bakiye,mst1[s].ek_hesap);
                                    }
                                    else
                                    {}
                                }
                                else
                                {}
                            }
                        fclose(bireysel3);
                        remove(gecici2);
                       ana_menu(musteri_sayisi,mst1,bsm1);
                    }
                }
                if(strcmp(mst1[bulunan_mst].hspturu, "TICARI") == 0)
                {
                    if(mst1[bulunan_mst].ek_hesap!=1000)
                    {
                       printf("\nHesap Kapatmak Icin Ek Hesap Limitinizin 1000 TL Olmasi Gerekir!\n");
                       musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                    }
                    else
                    {
                       hesap_kapama(musteri_sayisi,bulunan_mst,mst1,bsm1);
                       if((ticari3 = fopen("TICARI.txt","w+"))==NULL)
                       {
                           printf("\nDosya Yazma Hatasi\n");
                           exit(1);
                       }
                            for(s=0;s<100;s++)
                            {
                                if(strcmp(bsm1[s].bos_isim,mst1[s].isim))
                                {
                                    if(strcmp(mst1[s].hspturu, "TICARI") == 0)
                                    {
                                        fprintf(ticari3,"%s %s %d %d %.2f %.2f ",mst1[s].hspturu,mst1[s].isim,mst1[s].hspkontrol,mst1[s].numara,mst1[s].bakiye,mst1[s].ek_hesap);
                                    }
                                    else
                                    {}
                                }
                                else
                                {}
                            }
                        fclose(ticari3);
                        remove(gecici2);
                       ana_menu(musteri_sayisi,mst1,bsm1);
                    }
                }
                break;
            case '6':
                if((dekont2 = fopen(gecici2,"r"))==NULL)
                {
                    printf("\nDosya Okuma Hatasi\n");
                    exit(1);
                }
                printf("\n");
                while( fgets (dekont, 500, dekont2)!=NULL)
                {
                    printf("%s",dekont);
                    beklet(10);
                }
                fclose(dekont2);
                musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                break;
            case '7':
                if(strcmp(mst1[bulunan_mst].hspturu, "BIREYSEL") == 0)
                {
                    printf("\nEk Hesap Limitinizi Sifirlamak Icin %.2f TL Gerekmektedir\n",500-mst1[bulunan_mst].ek_hesap);
                    printf("\nOnayliyormusunuz?(e-h): "); scanf("%s",&ek_hsp_onay);
                    if(mst1[bulunan_mst].bakiye<500-mst1[bulunan_mst].ek_hesap)
                    {
                        printf("\nBakiyeniz Yeterli Degildir!\n");
                        musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                    }
                    else
                    {
                        switch(ek_hsp_onay)
                        {
                        case 'e':
                            mst1[bulunan_mst].bakiye=mst1[bulunan_mst].bakiye-(500-mst1[bulunan_mst].ek_hesap);
                            if((dekont2 = fopen(gecici2,"a+"))==NULL)
                            {
                                printf("\nDosya Yazma Hatasi\n");
                                exit(1);
                            }
                            tmenu = time(NULL);
                            fprintf(dekont2,"\n%s%.2f TL ODENEREK EK HESAP SIFIRLANDI\nBakiye:%.2f\n-------------------",ctime(&tmenu),(500-mst1[bulunan_mst].ek_hesap),mst1[bulunan_mst].bakiye);
                            fclose(dekont2);
                            mst1[bulunan_mst].ek_hesap=500;
                            printf("\nEk Hesabiniz Sifirlandi!\n");
                            musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                            break;
                        case 'E':
                            mst1[bulunan_mst].bakiye=mst1[bulunan_mst].bakiye-(500-mst1[bulunan_mst].ek_hesap);
                            if((dekont2 = fopen(gecici2,"a+"))==NULL)
                            {
                                printf("\nDosya Yazma Hatasi\n");
                                exit(1);
                            }
                            tmenu = time(NULL);
                            fprintf(dekont2,"\n%s%.2f TL ODENEREK EK HESAP SIFIRLANDI\nBakiye:%.2f\n-------------------",ctime(&tmenu),(500-mst1[bulunan_mst].ek_hesap),mst1[bulunan_mst].bakiye);
                            fclose(dekont2);
                            mst1[bulunan_mst].ek_hesap=500;
                            printf("\nEk Hesabiniz Sifirlandi!\n");
                            musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                            break;
                        default:
                            printf("\nIslem Iptal Edildi!\n");
                            musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                        }
                    }

                }
                if(strcmp(mst1[bulunan_mst].hspturu, "TICARI") == 0)
                {
                    printf("\nEk Hesap Limitinizi Sifirlamak Icin %.2f TL Gerekmektedir\n",1000-mst1[bulunan_mst].ek_hesap);
                    printf("\nOnayliyormusunuz?(e-h): "); scanf("%s",&ek_hsp_onay);
                    if(mst1[bulunan_mst].bakiye<1000-mst1[bulunan_mst].ek_hesap)
                    {
                        printf("\nBakiyeniz Yeterli Degildir!\n");
                        musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                    }
                    else
                    {
                        switch(ek_hsp_onay)
                        {
                        case 'e':
                            mst1[bulunan_mst].bakiye=mst1[bulunan_mst].bakiye-(1000-mst1[bulunan_mst].ek_hesap);
                            if((dekont2 = fopen(gecici2,"a+"))==NULL)
                            {
                                printf("\nDosya Yazma Hatasi\n");
                                exit(1);
                            }
                            tmenu = time(NULL);
                            fprintf(dekont2,"\n%s%.2f TL ODENEREK EK HESAP SIFIRLANDI\nBakiye:%.2f\n-------------------",ctime(&tmenu),(1000-mst1[bulunan_mst].ek_hesap),mst1[bulunan_mst].bakiye);
                            fclose(dekont2);
                            mst1[bulunan_mst].ek_hesap=1000;
                            printf("\nEk Hesabiniz Sifirlandi!\n");
                            musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                            break;
                        case 'E':
                            mst1[bulunan_mst].bakiye=mst1[bulunan_mst].bakiye-(1000-mst1[bulunan_mst].ek_hesap);
                            if((dekont2 = fopen(gecici2,"a+"))==NULL)
                            {
                                printf("\nDosya Yazma Hatasi\n");
                                exit(1);
                            }
                            tmenu = time(NULL);
                            fprintf(dekont2,"\n%s%.2f TL ODENEREK EK HESAP SIFIRLANDI\nBakiye:%.2f\n-------------------",ctime(&tmenu),(1000-mst1[bulunan_mst].ek_hesap),mst1[bulunan_mst].bakiye);
                            fclose(dekont2);
                            mst1[bulunan_mst].ek_hesap=1000;
                            printf("\nEk Hesabiniz Sifirlandi!\n");
                            musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                            break;
                        default:
                            printf("\nIslem Iptal Edildi!\n");
                            musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                        }
                    }

                }
                break;
            default:
                printf("\nHatali Giris Yaptiniz!\n");
                musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
                break;
            }
}
void para_cekme(char gecici2[],int boyut,int bulunan_mst,struct musteri *mst1)
{
    FILE *dekont3;
    time_t tcek;
    float x;
    printf("\nCekmek Istediginiz Miktar :"); scanf("%f",&x);
    if(strcmp(mst1[bulunan_mst].hspturu, "BIREYSEL") == 0 && x>750)
    {
       printf("\nBireysel Hesaplar Icin Para Cekme Limiti 750 TL Dir!\n");
       x=0;
       beklet(100);
    }
    if(strcmp(mst1[bulunan_mst].hspturu, "TICARI") == 0 && x>1500)
    {
       printf("\nTicari Hesaplar Icin Para Cekme Limiti 1500 TL Dir!\n");
       x=0;
       beklet(100);
    }
    if(x>mst1[bulunan_mst].bakiye)
    {
       printf("\nBakiyeniz Bu Islem Icin Yeterli Degildir!\n");
    }
    else
    {
       mst1[bulunan_mst].bakiye=mst1[bulunan_mst].bakiye-x;
       if((dekont3 = fopen(gecici2,"a+"))==NULL)
       {
           printf("\nDosya Yazma Hatasi\n");
           exit(1);
       }
       tcek = time(NULL);
       fprintf(dekont3,"\n%s%.2f TL PARA CEKILDI\nBakiye:%.2f\n-------------------",ctime(&tcek),x,mst1[bulunan_mst].bakiye);
       fclose(dekont3);
    }
    printf("\n");
}
void para_yatirma(char gecici2[],int boyut,int bulunan_mst,struct musteri *mst1)
{
    FILE *dekont4;
    time_t tyatir;
    float z;
    printf("Yatirmak Istediginiz Miktar :"); scanf("%f",&z);
    mst1[bulunan_mst].bakiye=mst1[bulunan_mst].bakiye+z;
    if((dekont4 = fopen(gecici2,"a+"))==NULL)
    {
        printf("\nDosya Yazma Hatasi\n");
        exit(1);
    }
    tyatir = time(NULL);
    fprintf(dekont4,"\n%s%.2f TL PARA YATIRILDI\nBakiye:%.2f\n-------------------",ctime(&tyatir),z,mst1[bulunan_mst].bakiye);
    fclose(dekont4);
    printf("\n");

}
void havale(char gecici2[],int boyut,int bulunan_mst,struct musteri *mst1,struct bos *bsm1)
{
    FILE *dekont5;
    time_t thavale;
    int aranan,i,bulunan;
    char hvl_secim;
    char hvl_gecici[50];
    float t;
    printf("Havale yapilacak numara : "); scanf("%d",&aranan);

    for(i=0;i<100;i++)
    {
        if(aranan==mst1[i].numara)
        {
            bulunan=i;
            if(strcmp(bsm1[bulunan].bos_isim,mst1[bulunan].isim))
            {}
            else
            {
              printf("\nBu Numaraya Sahip Kayitli Musteri Bulunmamaktadir!!\n");
              break;
            }
            printf("\nIsim : %s\nMusteri Numarasi: %d\n\n",mst1[bulunan].isim,mst1[bulunan].numara);
            printf("Bakiyeniz :%.2f\n",mst1[bulunan_mst].bakiye);
            printf("Havale Miktari :"); scanf("%f",&t);
            if(t<=0)
            {
                printf("\nHavale Miktari 0 Dan Kucuk Olamaz!\n");
                break;
            }
            if(strcmp(mst1[bulunan_mst].hspturu,"BIREYSEL") == 0)
            {
                printf("\n%.2f TL Havale Ucreti Kesilcektir!\n",t/50);
                if(t+(t/50)>mst1[bulunan_mst].bakiye)
                {
                    printf("\nBakiyeniz Bu Islem Icin Yeterli Degildir!\n");
                    printf("\nHAVALE ISLEMI IPTAL EDILDI!\n");

                }
                else
                {
                 printf("\nKabul Ediyormusunuz ?(e/h): "); scanf("%s",&hvl_secim);
                switch(hvl_secim)
                {
                case 'e':
                    strcpy(hvl_gecici,mst1[bulunan].isim);
                    strcat(hvl_gecici,".txt");
                    mst1[bulunan_mst].bakiye=mst1[bulunan_mst].bakiye-t;
                    mst1[bulunan].bakiye=mst1[bulunan].bakiye+t;
                    mst1[bulunan_mst].bakiye=mst1[bulunan_mst].bakiye-(t/50);
                    if((dekont5 = fopen(gecici2,"a+"))==NULL)
                    {
                        printf("\nDosya Yazma Hatasi\n");
                        exit(1);
                    }
                    thavale = time(NULL);
                    fprintf(dekont5,"\n%s%d NUMARALI %s %s HESABINA %.2f TL HAVALE GONDERILDI\n%.2f TL Havale UCRETI KESILDI\nBakiye:%.2f\n-------------------",ctime(&thavale),mst1[bulunan].numara,mst1[bulunan].hspturu,mst1[bulunan].isim,t,(t/50),mst1[bulunan_mst].bakiye);
                    fclose(dekont5);
                    if((dekont5 = fopen(hvl_gecici,"a+"))==NULL)
                    {
                        printf("\nDosya Yazma Hatasi\n");
                        exit(1);
                    }
                    fprintf(dekont5,"\n%s%d NUMARALI %s %s HESABINDAN %.2f TL HAVALE ALINDI\nBakiye:%.2f\n-------------------",ctime(&thavale),mst1[bulunan_mst].numara,mst1[bulunan_mst].hspturu,mst1[bulunan_mst].isim,t,mst1[bulunan].bakiye);
                    fclose(dekont5);
                    printf("\nHAVALE ISLEMI TAMAMLANDI\n");
                    break;
                case 'E':
                    strcpy(hvl_gecici,mst1[bulunan].isim);
                    strcat(hvl_gecici,".txt");
                    mst1[bulunan_mst].bakiye=mst1[bulunan_mst].bakiye-t;
                    mst1[bulunan].bakiye=mst1[bulunan].bakiye+t;
                    mst1[bulunan_mst].bakiye=mst1[bulunan_mst].bakiye-(t/50);
                    if((dekont5 = fopen(gecici2,"a+"))==NULL)
                    {
                        printf("\nDosya Yazma Hatasi\n");
                        exit(1);
                    }
                    thavale = time(NULL);
                    fprintf(dekont5,"\n%s%d NUMARALI %s %s HESABINA %.2f TL HAVALE GONDERILDI\n%.2f TL Havale UCRETI KESILDI\nBakiye:%.2f\n-------------------",ctime(&thavale),mst1[bulunan].numara,mst1[bulunan].hspturu,mst1[bulunan].isim,t,(t/50),mst1[bulunan_mst].bakiye);
                    fclose(dekont5);
                    if((dekont5 = fopen(hvl_gecici,"a+"))==NULL)
                    {
                        printf("\nDosya Yazma Hatasi\n");
                        exit(1);
                    }
                    fprintf(dekont5,"\n%s%d NUMARALI %s %s HESABINDAN %.2f TL HAVALE ALINDI\nBakiye:%.2f\n-------------------",ctime(&thavale),mst1[bulunan_mst].numara,mst1[bulunan_mst].hspturu,mst1[bulunan_mst].isim,t,mst1[bulunan].bakiye);
                    fclose(dekont5);
                    printf("\nHAVALE ISLEMI TAMAMLANDI\n");
                    break;
                default:
                   printf("\nHAVALE ISLEMI IPTAL EDILDI!\n");
                   break;
                }
                break;
                }
            }
            else
            {
                if(t>mst1[bulunan_mst].bakiye)
                {
                    printf("\nBakiyeniz Bu Islem Icin Yeterli Degildir!\n");
                    printf("\nHAVALE ISLEMI IPTAL EDILDI!\n");
                }
                else
                {
                    strcpy(hvl_gecici,mst1[bulunan].isim);
                    strcat(hvl_gecici,".txt");
                    mst1[bulunan_mst].bakiye=mst1[bulunan_mst].bakiye-t;
                    mst1[bulunan].bakiye=mst1[bulunan].bakiye+t;
                    if((dekont5 = fopen(gecici2,"a+"))==NULL)
                    {
                        printf("\nDosya Yazma Hatasi\n");
                        exit(1);
                    }
                    thavale = time(NULL);
                    fprintf(dekont5,"\n%s%d NUMARALI %s %s HESABINA %.2f TL HAVALE GONDERILDI\nBakiye:%.2f\n-------------------",ctime(&thavale),mst1[bulunan].numara,mst1[bulunan].hspturu,mst1[bulunan].isim,t,mst1[bulunan_mst].bakiye);
                    fclose(dekont5);
                    if((dekont5 = fopen(hvl_gecici,"a+"))==NULL)
                    {
                        printf("\nDosya Yazma Hatasi\n");
                        exit(1);
                    }
                    fprintf(dekont5,"\n%s%d NUMARALI %s %s HESABINDAN %.2f TL HAVALE ALINDI\nBakiye:%.2f\n-------------------",ctime(&thavale),mst1[bulunan_mst].numara,mst1[bulunan_mst].hspturu,mst1[bulunan_mst].isim,t,mst1[bulunan].bakiye);
                    fclose(dekont5);
                    printf("\nHAVALE ISLEMI TAMAMLANDI\n");
                }
            }
        }

    }
}
void hesap_kapama(int musteri_sayisi,int bulunan_mst,struct musteri *mst1,struct bos *bsm1)
{
    char secim2;
    printf("\nHESABINIZI KAPATMAK ISTEDIGINIZE EMIN MISINIZ? (E/H): "); scanf("%s",&secim2);
    switch(secim2)
    {
    case 'e':
        strcpy(mst1[bulunan_mst].isim, "");
        printf("\nHesabiniz Basari Ile Kapatildi!");
        break;
    case 'E':
        strcpy(mst1[bulunan_mst].isim, "");
        printf("\nHesabiniz Basari Ile Kapatildi!");
        break;
    default:
        printf("\nHESABINIZ KAPATILMADI\n");
        musteri_menu(bulunan_mst,musteri_sayisi,mst1,bsm1);
        break;

    }


}
void admin_giris(int musteri_sayisi,struct musteri *mst1,struct bos *bsm1)
{
    int p,blok_sayac=0;
    char admin_secim;
    float toplam_para=0;
    FILE *rapor;
    FILE *bireysel4;
    FILE *ticari4;

    if((bireysel4 = fopen("BIREYSEL.txt","w+")) == NULL)
     {
         printf("\nDosya Acma Hatasi\n");
         exit(1);
     }
     for(p=0;p<100;p++)
     {
         if(strcmp(bsm1[p].bos_isim,mst1[p].isim))
         {
            if(strcmp(mst1[p].hspturu, "BIREYSEL") == 0)
            {
                fprintf(bireysel4,"%s %s %d %d %.2f %.2f ",mst1[p].hspturu,mst1[p].isim,mst1[p].hspkontrol,mst1[p].numara,mst1[p].bakiye,mst1[p].ek_hesap);
            }
            else
            {}
         }
         else
         {}
     }
     fclose(bireysel4);
    if((ticari4 = fopen("TICARI.txt","w+")) == NULL)
     {
         printf("\nDosya Acma Hatasi\n");
         exit(1);
     }
     for(p=0;p<100;p++)
     {
         if(strcmp(bsm1[p].bos_isim,mst1[p].isim))
         {
             if(strcmp(mst1[p].hspturu, "TICARI") == 0)
             {
                 fprintf(ticari4,"%s %s %d %d %.2f %.2f ",mst1[p].hspturu,mst1[p].isim,mst1[p].hspkontrol,mst1[p].numara,mst1[p].bakiye,mst1[p].ek_hesap);
             }
             else
             {}
         }
         else
         {}
     }
     fclose(ticari4);

    if((rapor = fopen("RAPOR.txt","w+")) == NULL)
    {
        printf("\nDosya Yazma Hatasi!\n");
        exit(1);
    }
        for(p=0;p<100;p++)
    {
        toplam_para+=mst1[p].bakiye;
        if(mst1[p].hspkontrol==0)
        {
            blok_sayac++;
        }

    }

    fprintf(rapor,"Kayitli Musteri Sayisi :%d\nBloke Edilmis Hesap Sayisi :%d\nBloke Edilmis Hesaplar\n-------------------------",musteri_sayisi,blok_sayac);
    fclose(rapor);

    if((rapor = fopen("RAPOR.txt","a+")) == NULL)
    {
        printf("\nDosya Yazma Hatasi!\n");
        exit(1);

    }
    for(p=0;p<100;p++)
    {
        if(mst1[p].hspkontrol==0)
        {
            fprintf(rapor,"\n\n%s HESAP\nISIM:%s\nNO:%d\nBakiye:%.2f",mst1[p].hspturu,mst1[p].isim,mst1[p].numara,mst1[p].bakiye);
        }
    }
    fprintf(rapor,"\n\nBankadaki Toplam Para  :%.2f\n",toplam_para);
    fclose(rapor);


            beklet(2);
            printf("\n/////ADMIN MENU/////\n\n");
            beklet(2);
            printf("1.Rapor Al\n");
            beklet(2);
            printf("2.Hesap Bloke Et\n");
            beklet(2);
            printf("3.Hesap Bloke Kaldir\n");
            beklet(2);
            printf("4.Hesap Kapat\n");
            beklet(2);
            printf("5.Ana Menuye Don\n");
            beklet(2);

            printf("\nSeciminiz (1-3) : "); scanf("%s",&admin_secim);

            switch(admin_secim)
            {
            case '1':
                if(rapor = fopen("RAPOR.txt","r") == NULL)
                {
                   printf("\nDosya Okuma Hatasi!\n");
                   exit(1);
                }
                fscanf(rapor,"%d %d %d",&musteri_sayisi,&blok_sayac,&toplam_para);
                printf("\nKayitli Musteri Sayisi     :%d",musteri_sayisi);
                printf("\nBloke Edilmis Hesap Sayisi :%d",blok_sayac);
                printf("\nBankadaki Toplam Para      :%.2f\n",toplam_para);
                admin_giris(musteri_sayisi,mst1,bsm1);
                break;
            case '2':
                admin_hesap_blok(blok_sayac,mst1,bsm1);
                admin_giris(musteri_sayisi,mst1,bsm1);
                break;
            case '3':
                admin_blok_kaldir(blok_sayac,mst1,bsm1);
                admin_giris(musteri_sayisi,mst1,bsm1);
                break;
            case '4':
                admin_hesap_kapama(musteri_sayisi,mst1,bsm1);
                admin_giris(musteri_sayisi,mst1,bsm1);
                break;
            case '5':
                ana_menu(musteri_sayisi,mst1,bsm1);
                break;
            default:
                printf("\nHATALI GIRIS YAPTINIZ\n");
                admin_giris(musteri_sayisi,mst1,bsm1);
                break;
            }
}
void admin_hesap_kapama(int musteri_sayisi,struct musteri *mst1, struct bos *bsm1)
{
    int aranan_hesap,bul_hesap,v;
    printf("\nKapatilacak Hesap Numarasi: "); scanf("%d",&aranan_hesap);
    for(v=0;v<100;v++)
    {
        if(aranan_hesap==mst1[v].numara)
        {
            bul_hesap=v;
            if(strcmp(mst1[bul_hesap].isim,bsm1[bul_hesap].bos_isim))
            {}
            else
            {
              printf("\nBu Numaraya Sahip Kayitli Musteri Bulunmamaktadir!\n");
              break;
            }
            printf("\n%s HESAP\n",mst1[bul_hesap].hspturu);
            printf("%s\n",mst1[bul_hesap].isim);
            strcpy(mst1[bul_hesap].isim, "");
            mst1[bul_hesap].bakiye=0;
            mst1[bul_hesap].hspkontrol=1;
            printf("\nHesap Sifirlandi!");
            break;

            }


        }

}
void admin_hesap_blok(int blok_sayac,struct musteri *mst1,struct bos *bsm1)
{
    int aranan_hesap2,bul_hesap2,b;
    printf("\nBloke Edilecek Hesap Numarasi: "); scanf("%d",&aranan_hesap2);
    for(b=0;b<100;b++)
    {
        if(aranan_hesap2==mst1[b].numara)
        {
            bul_hesap2=b;
            if(strcmp(mst1[bul_hesap2].isim,bsm1[bul_hesap2].bos_isim))
            {}
            else
            {
                printf("\nBu Numaraya Sahip Kayitli Musteri Bulunmamaktadir!\n");
                break;
            }
            printf("\n%s HESAP\n",mst1[bul_hesap2].hspturu);
            printf("%s\n",mst1[bul_hesap2].isim);
            mst1[bul_hesap2].hspkontrol=0;
            printf("\nHesap Bloke Edildi!");
            break;

            }


        }
}
void admin_blok_kaldir(int blok_sayac,struct musteri *mst1,struct bos *bsm1)
{
    int aranan_hesap3,bul_hesap3,g;
    for(g=0;g<100;g++)
    {
        if(mst1[g].hspkontrol==0)
        {
            printf("\n\n%s HESAP\nISIM:%s\nNO:%d\nBakiye:%.2f",mst1[g].hspturu,mst1[g].isim,mst1[g].numara,mst1[g].bakiye);
        }
    }
    printf("\n\nBlok Kaldirilacak Hesap Numarasi: "); scanf("%d",&aranan_hesap3);

    for(g=0;g<100;g++)
    {
        if(aranan_hesap3==mst1[g].numara)
        {
            bul_hesap3=g;
            printf("\n%s HESAP\n",mst1[bul_hesap3].hspturu);
            printf("%s\n",mst1[bul_hesap3].isim);
            mst1[bul_hesap3].hspkontrol=1;
            printf("\nHesap Bloku Kaldirildi!");
            break;

            }


        }
}
void beklet(int saniye)
{
    int mili_saniye=10*saniye;
    clock_t start_time= clock();
    while(clock()<start_time+mili_saniye)
        ;
}
