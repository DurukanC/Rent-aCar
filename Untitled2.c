#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARAC_SAYISI 300

typedef struct {
	char *musteriAdi;
	char *musteriSoyadi;
}musteriBilgileri;

typedef struct {
	int gun;
	int ay;
	int yil;
	
}tarihBilgileri;

typedef struct {
	int arac_id;
	int kirada_mi;
	char marka[20];
	char model[20];
	double kiralama_ucreti;
	musteriBilgileri musteri;
	tarihBilgileri kiralamaTarihi;
	tarihBilgileri teslimTarihi;
}aracBilgileri;

typedef struct{
	aracBilgileri *data;
	unsigned int size;
}aracListesi;

typedef enum {
	musteri=0, personel=1
}yetkiSeviyeleri;

void yeniAracEkle(aracListesi *liste) {

    if (liste->size == ARAC_SAYISI) {
        printf("Hata: Liste dolu!\n");
        return;
    }
    int arac_id,i;
    printf("Lutfen eklemek istediginiz aracin ID bilgisini giriniz:");
    scanf("%d", &arac_id);
    for (i= 0;i< liste->size;i++) {
        if (liste->data[i].arac_id == arac_id) {
            printf("Hata: Bu arac ID'si zaten kullaniliyor!\n");
            return;
        }
    }
    liste->data[liste->size].arac_id = arac_id;
    printf("Lutfen eklemek istediginiz aracin Marka bilgisini giriniz:");
    scanf("%s", liste->data[liste->size].marka);
    printf("Lutfen eklemek istediginiz aracin Model bilgisini giriniz:");
    scanf("%s", liste->data[liste->size].model);
    printf("Lutfen eklemek istediginiz aracin Kiralama Ucret bilgisini giriniz:");
    scanf("%lf", &liste->data[liste->size].kiralama_ucreti);
    liste->data[liste->size].kirada_mi = 0; 
    liste->data[liste->size].musteri.musteriAdi = NULL; 
    liste->data[liste->size].musteri.musteriSoyadi = NULL;
    liste->data[liste->size].kiralamaTarihi.gun = 0; 
    liste->data[liste->size].kiralamaTarihi.ay = 0;
    liste->data[liste->size].kiralamaTarihi.yil = 0;
    liste->data[liste->size].teslimTarihi.gun = 0;
    liste->data[liste->size].teslimTarihi.ay = 0;
    liste->data[liste->size].teslimTarihi.yil = 0;
    liste->size++; 
}

void aracListele(aracListesi *liste) {
    int i;
    printf("AracID\tMarka\tModel\tFiyat\n");
    
    liste->data[liste->size].arac_id = 1;
    strcpy(liste->data[liste->size].marka, "Renault");
    strcpy(liste->data[liste->size].model, "Clio");
    liste->data[liste->size].kiralama_ucreti = 200;
    liste->size++;

    liste->data[liste->size].arac_id = 2;
    strcpy(liste->data[liste->size].marka, "Volkswagen");
    strcpy(liste->data[liste->size].model, "Golf");
    liste->data[liste->size].kiralama_ucreti = 250;
    liste->size++;

    liste->data[liste->size].arac_id = 3;
    strcpy(liste->data[liste->size].marka, "Toyota");
    strcpy(liste->data[liste->size].model, "Corolla");
    liste->data[liste->size].kiralama_ucreti = 300;
    liste->size++;

    liste->data[liste->size].arac_id = 4;
    strcpy(liste->data[liste->size].marka, "Ford");
    strcpy(liste->data[liste->size].model, "Focus");
    liste->data[liste->size].kiralama_ucreti = 220;
    liste->size++;
    
    liste->data[liste->size].arac_id = 5;
    strcpy(liste->data[liste->size].marka, "Fiat");
    strcpy(liste->data[liste->size].model, "Egea");
    liste->data[liste->size].kiralama_ucreti = 250;
    liste->size++;
    
    liste->data[liste->size].arac_id = 6;
    strcpy(liste->data[liste->size].marka, "Mercedes");
    strcpy(liste->data[liste->size].model, "C180");
    liste->data[liste->size].kiralama_ucreti = 400;
    liste->size++;
    
    liste->data[liste->size].arac_id = 7;
    strcpy(liste->data[liste->size].marka, "Auidi");
    strcpy(liste->data[liste->size].model, "A5");
    liste->data[liste->size].kiralama_ucreti = 420;
    liste->size++;
    
    liste->data[liste->size].arac_id = 8;
    strcpy(liste->data[liste->size].marka, "BMW");
    strcpy(liste->data[liste->size].model, "420i");
    liste->data[liste->size].kiralama_ucreti = 450;
    liste->size++;
    
    for (i = 0; i < liste->size; i++) {
        printf("%d\t%s\t%s\t%.2lf\n", liste->data[i].arac_id, liste->data[i].marka, liste->data[i].model,liste->data[i].kiralama_ucreti);
    }
}
   
int gunFarkiHesapla(tarihBilgileri kiralamaTarihi, tarihBilgileri teslimTarihi) {
    if (kiralamaTarihi.gun > teslimTarihi.gun) {
        teslimTarihi.ay -= 1;
        teslimTarihi.gun += 30;
    }
    if (kiralamaTarihi.ay > teslimTarihi.ay) {
        teslimTarihi.yil -= 1;
        teslimTarihi.ay += 12;
    }
    tarihBilgileri tarihFarki;
    tarihFarki.gun = teslimTarihi.gun - kiralamaTarihi.gun;
    tarihFarki.ay = teslimTarihi.ay - kiralamaTarihi.ay;
    tarihFarki.yil = teslimTarihi.yil - kiralamaTarihi.yil;
    int gunFarki = tarihFarki.yil * 365 + tarihFarki.ay * 30 + tarihFarki.gun;
    return gunFarki;
}

double fiyatHesapla(aracBilgileri arac, tarihBilgileri kiralamaTarihi, tarihBilgileri teslimTarihi) {
    int gunFarki = gunFarkiHesapla(kiralamaTarihi, teslimTarihi);
    double toplamFiyat = arac.kiralama_ucreti * gunFarki;
    if (gunFarki >= 7 && gunFarki < 30) {
        toplamFiyat *= 0.9;  
    } else if (gunFarki >= 30) {
        toplamFiyat *= 0.8;  
    }
    
    return toplamFiyat;
}

void kiralanmisAracBilgileri(aracListesi *liste) {
    int i;
    int kiradakiAracSayisi=0;
    printf("Kiralanmis Araclarin Bilgileri:\n");
    
    for (i = 0; i < liste->size; i++) {
        if (liste->data[i].kirada_mi == 1) {
        	kiradakiAracSayisi++;
            printf("AracID: %d\n", liste->data[i].arac_id);
            printf("Marka: %s\n", liste->data[i].marka);
            printf("Model: %s\n", liste->data[i].model);
            printf("Kiralama Ucreti: %.2lf\n", liste->data[i].kiralama_ucreti);
            printf("Kira Bilgileri:\n");
            printf("Musteri Adi: %s\n", liste->data[i].musteri.musteriAdi);
            printf("Musteri Soyadi: %s\n", liste->data[i].musteri.musteriSoyadi);
            printf("Kiralama Tarihi: %d/%d/%d\n", liste->data[i].kiralamaTarihi.gun, liste->data[i].kiralamaTarihi.ay, liste->data[i].kiralamaTarihi.yil);
            printf("Teslim Tarihi: %d/%d/%d\n", liste->data[i].teslimTarihi.gun, liste->data[i].teslimTarihi.ay, liste->data[i].teslimTarihi.yil);
            printf("Kira Ucreti: %.2lf\n", fiyatHesapla(liste->data[i], liste->data[i].kiralamaTarihi, liste->data[i].teslimTarihi));
            printf("------------------------------\n");
        }
    }
    if(kiradakiAracSayisi==0) {
    	printf("Kiralanmis arac bilgisi bulunmamaktadir. Butun araclar musaittir.\n");
	}
}

void aracKiralama(aracListesi *liste) {
    int i, id, kiralamaGunu, kiralamaAy, kiralamaYil, teslimGunu, teslimAy, teslimYil;
    char musteriAdi[20], musteriSoyadi[20];
    printf("*****Kiralama Bolumune Hosgeldiniz!*****\n");
    printf("*****Dikkat! Bilgilendirme...*****\n[*].Kiralama sureniz 1 haftadan fazla olursa (%%10)'luk bir INDIRIM uygulanacaktir.\n[*].Kiralama sureniz 1 aydan fazla olursa (%%20)'lik bir INDIRIM uygulanacaktir.\n");
    printf("Lutfen kiralayacaginiz aracin ID bilgisini giriniz:");
    scanf("%d", &id);
    for (i = 0; i < liste->size; i++) {
        if (liste->data[i].arac_id == id) {
            if (liste->data[i].kirada_mi == 1) {
                printf("Hata: Bu arac zaten kirada!\n");
                return;
            }
            printf("Lutfen kiralama tarihini (gun:ay:yil) seklinde giriniz:");
            scanf("%d:%d:%d", &kiralamaGunu, &kiralamaAy, &kiralamaYil);
            liste->data[i].kiralamaTarihi.gun = kiralamaGunu;
            liste->data[i].kiralamaTarihi.ay = kiralamaAy;
            liste->data[i].kiralamaTarihi.yil = kiralamaYil;
            printf("Lutfen teslim tarihini (gun:ay:yil) seklinde giriniz:");
            scanf("%d:%d:%d", &teslimGunu, &teslimAy, &teslimYil);
            liste->data[i].teslimTarihi.gun = teslimGunu;
            liste->data[i].teslimTarihi.ay = teslimAy;
            liste->data[i].teslimTarihi.yil = teslimYil;
            printf("Lutfen adinizi giriniz:");
            scanf("%s", musteriAdi);
            printf("Lutfen soyadinizi giriniz:");
            scanf("%s", musteriSoyadi);
            liste->data[i].musteri.musteriAdi = malloc(strlen(musteriAdi)+1);
            strcpy(liste->data[i].musteri.musteriAdi, musteriAdi);
            liste->data[i].musteri.musteriSoyadi = malloc(strlen(musteriSoyadi)+1);
            strcpy(liste->data[i].musteri.musteriSoyadi, musteriSoyadi);
            liste->data[i].kirada_mi = 1;
            double kiraFiyati = fiyatHesapla(liste->data[i], liste->data[i].kiralamaTarihi, liste->data[i].teslimTarihi);
            printf("Arac kiralandi! Odemeniz: %.2lf\n", kiraFiyati);
            return;
        }
    }
    printf("Hata: Arac bulunamadi!\n");
}


void personelKiralanmisAracTemizle(aracListesi *liste) {
	int arac_id;
    printf("Lutfen temizlemek istediginiz aracin ID bilgisini giriniz:");
    scanf("%d",&arac_id);
    int i;
    for (i = 0; i < liste->size; i++) {
        if (liste->data[i].arac_id == arac_id) {
            if (liste->data[i].kirada_mi) {
                liste->data[i].kirada_mi = 0;
                strcpy(liste->data[i].musteri.musteriAdi, "");
                strcpy(liste->data[i].musteri.musteriSoyadi, "");
                liste->data[i].kiralamaTarihi.gun = 0;
                liste->data[i].kiralamaTarihi.ay = 0;
                liste->data[i].kiralamaTarihi.yil = 0;
                liste->data[i].teslimTarihi.gun = 0;
                liste->data[i].teslimTarihi.ay = 0;
                liste->data[i].teslimTarihi.yil = 0;
                printf("Arac teslim edildi.\n");
                return;
            } 
			else {
                printf("Hata: Arac zaten kirada degil!\n");
                return;
            }
        }
    }
    printf("Hata: Arac bulunamadi!\n");
}

void yedekKayitAlma(aracListesi *liste) {
	int i;
	FILE *kiralamaBilgileri=fopen("kiralamaBilgileri.txt","a");
	if(kiralamaBilgileri==NULL) {
		fprintf(stderr,"Yedek kayit alinirken bir hata meydana geldi.");
		exit(1);
	}
	for(i=0;i<liste->size;i++) {
		if(liste->data[i].kirada_mi!=0) {
			fprintf(kiralamaBilgileri,"---------------------------------------------------------------------\n");
			fprintf(kiralamaBilgileri,"AracID: %d\n", liste->data[i].arac_id);
            fprintf(kiralamaBilgileri,"Marka: %s\n", liste->data[i].marka);
            fprintf(kiralamaBilgileri,"Model: %s\n", liste->data[i].model);
			fprintf(kiralamaBilgileri,"Musteri Adi: %s\n", liste->data[i].musteri.musteriAdi);
            fprintf(kiralamaBilgileri,"Musteri Soyadi: %s\n", liste->data[i].musteri.musteriSoyadi);
            fprintf(kiralamaBilgileri,"Kiralama Tarihi: %d/%d/%d\n", liste->data[i].kiralamaTarihi.gun, liste->data[i].kiralamaTarihi.ay, liste->data[i].kiralamaTarihi.yil);
            fprintf(kiralamaBilgileri,"Teslim Tarihi: %d/%d/%d\n", liste->data[i].teslimTarihi.gun, liste->data[i].teslimTarihi.ay, liste->data[i].teslimTarihi.yil);
            fprintf(kiralamaBilgileri,"Kira Ucreti: %.2lf\n", fiyatHesapla(liste->data[i], liste->data[i].kiralamaTarihi, liste->data[i].teslimTarihi));
			
		}
	}
	fclose(kiralamaBilgileri);
}


int main() {
	int belirlenenSifre=147852,kullanicininGirdigiSifre;
	yetkiSeviyeleri kullaniciYetkisi;
	char ch;
	aracListesi *liste; 
	liste = (aracListesi*) calloc(1, sizeof(aracListesi));
	if (!liste) {
		printf("Hata: Bellek yetersiz!\n");
		return 1;
    }
    liste->data = calloc(ARAC_SAYISI, sizeof(aracBilgileri));
    if (!liste->data) {
        printf("Hata: Bellek yetersiz!\n");
        free(liste);
        return 1;
    }
	printf("\t\t\t Otomobil Kiralama Sistemine Hosgeldiniz....\n");
	printf("Lutfen burada calisiyorsaniz sifrenizi giriniz(Calismiyorsaniz rastgele sayisal deger girip devam edin!):");
	scanf("%d",&kullanicininGirdigiSifre);
	if(belirlenenSifre==kullanicininGirdigiSifre) {
		kullaniciYetkisi=personel;
	}
	else{S
		kullaniciYetkisi=musteri;
	}
	do{
		printf("[1].Yeni arac eklemek istiyorsaniz 'E'\n[2].Arac kiralamak istiyorsaniz 'K'\n[3].Kiralanmis arac bilgilerini goruntulemek istiyorsaniz 'G'\n");
		printf("[4].Musteri teslim/cikisi gerceklestirmek istiyorsaniz 'C'\n[5].Sistemden cikis yapmak istiyorsaniz 'Q' tuslayiniz.");
		fflush(stdin);
		ch=getchar();
		switch(ch){
			case 'E':
			case 'e':
				if(kullaniciYetkisi==personel) {
                    yeniAracEkle(liste);
					}
                   
				else {
					printf("Bu alan sadece calisanlar tarafindan kullanilabilir!\n");	
				}
			
				break;
			case 'K':
			case 'k':
				aracListele(liste);
				aracKiralama(liste);
				break;
			case 'G':
			case 'g':
				if(kullaniciYetkisi==personel) {
					kiralanmisAracBilgileri(liste);
				}
				else {
					printf("Bu alan sadece calisanlar tarafindan kullanilabilir!\n");	
				}
				break;
		
			case 'C':	
			case 'c':
				if(kullaniciYetkisi==personel) {
					personelKiralanmisAracTemizle(liste);	
				}
				else {
					printf("Bu alan sadece calisanlar tarafindan kullanilabilir!\n");	
				}
				break;
			case 'Q':
			case 'q':
				yedekKayitAlma(liste);
				break;
			default:
				break;		
		}
		
	}while(ch!='Q');
	
	
	return 0;
}

