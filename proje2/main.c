#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Dugum
{
    int veri;
    char harf;
    struct Dugum *left;
    struct Dugum *right;

};

struct Node
{
    int veri;
    struct Dugum *left;
    struct Dugum *right;

};

struct Dugum *yeni_dugum(int deger,char m)
{
    struct Dugum *yeni = (struct Dugum*)malloc(sizeof(struct Dugum));
    yeni->harf = m;
    yeni->veri = deger;
    yeni->left = NULL;
    yeni->right = NULL;

    return yeni;

}
int c=0;
int m=0;
int sayac_dizi1 = 1;
int bit_say =0;
char kod[][100];

void print(struct Dugum *temp,char *code)
{
    FILE *cikti = fopen("cikti.txt","a");
    kod[c][100];

    if(temp->left == NULL && temp->right == NULL)
    {
        printf("karakter %c kod %s\n ",temp->harf,code);
        fprintf(cikti,"karakter %c kod %s\n ",temp->harf,code);
        bit_say += (temp->veri * strlen(code));

        kod[m][0] = temp->harf;

        for(int j=0; j<strlen(code); j++)
        {
            kod[m][j+1] = code[j];
        }

        printf("\n");

        m++;

        return;
    }

    int length = strlen(code);

    char leftcode[20]="";
    char rightcode[20] ="";

    strcpy(leftcode,code);
    strcpy(rightcode,code);

    leftcode[length] = '0';
    leftcode[length+1] = '\0';

    rightcode[length] = '1';
    rightcode[length+1] = '\0';

    print(temp->left,leftcode);
    print(temp->right,rightcode);

    fclose(cikti);
}
int k=1;

void yaz(char *dizi1)
{
    FILE *cikti = fopen("cikti.txt","a");

    printf("\nLz77 algoritmasiyla olusan metin:\n%s\n",dizi1);
    fprintf(cikti,"\nLz77 algoritmasiyla olusan metin:\n%s \n",dizi1);

    printf("\n");
    fprintf(cikti,"\n");

    printf("\nDeflate algoritmasi sonucu karakterlerin kodlanmasi: \n");
    fprintf(cikti,"\nDeflate algoritmasi sonucu karakterlerin kodlanmasi: \n");

    printf("\n");
    fprintf(cikti,"\n");

    for(int i = 0; i<strlen(dizi1); i++)
    {
        for(int j=0; j<m; j++)
        {
            if(dizi1[i] == kod[j][0])
            {
git:
                if(kod[j][k] == '0' || kod[j][k] == '1')
                {
                    printf("%c",kod[j][k]);
                    fprintf(cikti,"%c",kod[j][k]);
                    k++;

                    if(kod[j][k] == '\0')
                    {
                        k=1;
                        break;
                    }

                    else
                    {
                        goto git;
                    }

                }

            }
        }
    }
    fclose(cikti);
}

void deflate(char *dizi, char*dizi1)
{
    FILE *cikti = fopen("cikti.txt","a");

    int frekans[100000];
    char harf_tut[100000];
    int sayac =0,sayac1 = 1,z=0,toplam=0;
    int uzunluk = strlen(dizi);

    for(int i=0; i<uzunluk; i++)
    {
        if(dizi[i] != '\0')
        {
            for(int j=i+1; j<uzunluk; j++)
            {
                if(dizi[j] == dizi[i] && dizi[j] != '\0')
                {
                    sayac++;
                    dizi[j] ='\0';
                }
            }

            harf_tut[c] = dizi[i];
            c++;

            frekans[z] = sayac+1;
            z++;

            sayac=0;
        }
    }

    printf("\nLz77 sonucu harfler ve tekrar sayilari:\n");
    fprintf(cikti,"\nLz77 sonucu harfler ve tekrar sayilari:\n");

    for(int i=0; i<z; i++)
    {
        printf("%c harfi %d tane \n",harf_tut[i],frekans[i]);
        fprintf(cikti,"%c harfi %d tane \n",harf_tut[i],frekans[i]);
    }

    printf("\n\n");
    fprintf(cikti,"\n\n");
    printf("LZ77 Algoritmasi ile olusan metni kullanarak Deflate Algoritmasi \n\n");
    fprintf(cikti,"LZ77 Algoritmasi ile olusan metni kullanarak Deflate Algoritmasi \n\n");

    char temp2;
    int tmp1;

    for(int i=0; i<z; i++)
    {
        for(int j=z-1 ; j>i; j--)
        {
            if(frekans[j-1]>frekans[j])
            {
                tmp1=frekans[j-1];
                temp2 = harf_tut[j-1];

                frekans[j-1]=frekans[j];
                harf_tut[j-1] = harf_tut[j];

                frekans[j]=tmp1;
                harf_tut[j] = temp2;
            }
        }
    }

    struct Dugum **pointer = (struct Dugum**)malloc(sizeof(struct Dugum*)*1);

    for(int i=0; i<z; i++)
    {
        pointer[i] = yeni_dugum(frekans[i],harf_tut[i]);
        sayac1++;
        pointer = (struct Dugum**)realloc(pointer,sizeof(struct Dugum*)*sayac1);
    }

    int k=0;
    int j=0;
    int x= strlen(harf_tut);

    while(k<strlen(harf_tut)-1)
    {
        x++;

        struct Dugum *sol = (struct Dugum*)malloc(sizeof(struct Dugum));
        sol = pointer[j];
        struct Dugum *sag = (struct Dugum*)malloc(sizeof(struct Dugum));
        sag = pointer[j+1];
        struct Dugum *topla = (struct Node*)malloc(sizeof(struct Node));

        topla->left = sol;
        topla->right = sag;
        topla->veri = sol->veri + sag->veri;

        pointer = (struct Node**)realloc(pointer,sizeof(struct Node*)*x);
        pointer[z] = topla;
        z++;

        struct Dugum **tmp = (struct Dugum**)malloc(sizeof(struct Dugum*)*1);

        for(int i=0; i< z; i++)
        {
            for(int b=z-1 ; b>i; b--)
            {
                if(pointer[b-1]->veri > pointer[b]->veri)
                {
                    tmp=pointer[b-1];
                    pointer[b-1]=pointer[b];
                    pointer[b]=tmp;
                }
            }
        }

        k++;
        j=j+2;
    }

    printf("Huffman Agaci \n\n");
    fprintf(cikti,"Huffman Agaci \n\n");

    for(int i=0; i<z; i++)
    {
        if(pointer[i]->left == 0 && pointer[i]->right == 0)

        {
            printf("son veri : %c\n ",pointer[i]->harf);
            fprintf(cikti,"son veri : %c\n ",pointer[i]->harf);

            printf("sol : %s\n ",pointer[i]->left);
            fprintf(cikti,"sol : %s\n ",pointer[i]->left);

            printf("sag : %s\n ",pointer[i]->right);
            fprintf("sag : %s\n ",pointer[i]->right);

        }

        else
        {
            printf("son veri : %d\n ",pointer[i]->veri);
            fprintf(cikti,"son veri : %d\n ",pointer[i]->veri);

            printf("sol : %d\n ",pointer[i]->left->veri);
            fprintf(cikti,"sol : %d\n ",pointer[i]->left->veri);

            printf("sag : %d\n ",pointer[i]->right->veri);
            fprintf(cikti,"sag : %d\n ",pointer[i]->right->veri);

        }
    }

    char code[20]="";
    code[0] = '\0';
    print(pointer[z-1],code);
    yaz(dizi1);

    printf("\n\nDeflate sonucu metnin boyutu %d byte\n\n\n ",(bit_say/8));
    fprintf(cikti,"\n\nDeflate sonucu metnin boyutu %d byte\n\n\n ",(bit_say/8));

    fclose(cikti);
}

void lz77()
{
    FILE *dosya = fopen("metin.txt","r");
    FILE *cikti = fopen("cikti.txt","a");

    char *dizi = malloc(sizeof(char)*1);
    dizi[0] = '\0';

    int sayac =0,sayac2=1,sayac_frekans=1,sayac_arama=1,sayac_ileri=1,sayac_harf=1;

    char *ileri_tampon = malloc(sizeof(char)*1);
    ileri_tampon[0] = '\0';

    char *arama_tamponu = malloc(sizeof(char)*1);
    arama_tamponu[0] = '\0';

    int say =0;
    int a = 0;
    int boyut = 0;
    int d = 0;

    fgets(ileri_tampon,2,dosya);
    sayac_ileri++;
    ileri_tampon = realloc(ileri_tampon,sizeof(char)*sayac_ileri);

    printf("[%d, %d, %s]\n",0,0,ileri_tampon);
    fprintf(cikti,"[%d, %d, %s]\n",0,0,ileri_tampon);

    strcat(dizi,ileri_tampon);
    sayac2++;
    dizi = realloc(dizi,sizeof(char)*sayac2);

    fgets(arama_tamponu,2,dosya);
    sayac_arama++;
    arama_tamponu = realloc(arama_tamponu,sizeof(char)*sayac_arama);

    int  boy = strlen(ileri_tampon);

    while(!feof(dosya))
    {
        while(d<boy)
        {
            if(ileri_tampon[d] == arama_tamponu[0])
            {

                strcat(ileri_tampon,arama_tamponu);
                sayac_ileri++;

                ileri_tampon = realloc(ileri_tampon,sizeof(char)*sayac_ileri);
                sayac_ileri++;

                boyut = strlen(ileri_tampon);
                a = d;

                fgets(arama_tamponu,2,dosya);
                sayac_arama++;
                arama_tamponu = realloc(arama_tamponu,sizeof(char)*sayac_arama);
                sayac_arama++;

                d++;
                say++;

                if(ileri_tampon[d] != arama_tamponu[0])
                {
                    goto git2;
                }
            }
            else
            {
                d++;
            }
        }
git2:
        if(say == 0)
        {
            printf("[%d, %d, %s]\n",0,0,arama_tamponu);
            fprintf(cikti,"[%d, %d, %s]\n",0,0,arama_tamponu);

            strcat(dizi,arama_tamponu);

            sayac2++;
            dizi = realloc(dizi,sizeof(char)*sayac2);
            sayac2++;

            strcat(ileri_tampon,arama_tamponu);

            sayac_ileri++;
            ileri_tampon = realloc(ileri_tampon,sizeof(char)*sayac_ileri);
            sayac_ileri++;

        }
        else
        {
            printf("[%d, %d, %s]\n ",(boyut - a - 1),say,arama_tamponu);
            fprintf(cikti,"[%d, %d, %s]\n ",(boyut - a - 1),say,arama_tamponu);

            strcat(dizi,arama_tamponu);

            sayac2++;
            dizi = realloc(dizi,sizeof(char)*sayac2);
            sayac2++;

            strcat(ileri_tampon,arama_tamponu);

            sayac_ileri++;
            ileri_tampon = realloc(ileri_tampon,sizeof(char)*sayac_ileri);
            sayac_ileri++;

        }
        fgets(arama_tamponu,2,dosya);

        sayac_arama++;
        arama_tamponu = realloc(arama_tamponu,sizeof(char)*sayac_arama);
        sayac_arama++;

        say = 0;
        boy = strlen(ileri_tampon);
        d=0;
    }

    printf("\nLz77 algoritmasiyla olusan metin:\n%s \n",dizi);
    fprintf(cikti,"\nLz77 algoritmasiyla olusan metin:\n%s \n",dizi);

    int uzunluk = strlen(dizi);

    printf("\nIslem sonrasi boyut %d bayt \n\n",uzunluk);
    fprintf(cikti,"\nIslem sonrasi boyut %d bayt \n\n",uzunluk);

    fclose(cikti);

    char *dizi1 = malloc(sizeof(char)*1);
    for(int i=0; i<strlen(dizi); i++)
    {
        dizi1[i] = dizi[i];
        sayac_dizi1++;
        dizi1 = realloc(dizi1,sizeof(char)*sayac_dizi1);

    }
    dizi1[strlen(dizi)] = '\0';

    deflate(dizi,dizi1);
}

int main()
{

    FILE *cikti = fopen("cikti.txt","w");
    printf("Lz77 algoritmasi\n");
    fprintf(cikti,"Lz77 algoritmasi \n");
    fclose(cikti);

    lz77();
}
