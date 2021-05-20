// Bilal Emir Günay 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h> 
#include <signal.h>

int oyuncuNumarasi;
FILE *f;


void toplamCevaplamaSuresiAlarm(int signum){
    
    printf("\nSüre bitti. Kazanan yok.\n");
    fprintf(f,"\nSüre bitti. Kazanan yok.\n" );
    exit(0);

}


void oyun(int A, int B){
    struct timespec baslangic, bitis, oyunBaslangic, oyunBitis; 
    
    clock_gettime(CLOCK_REALTIME, &oyunBaslangic);

    srand(time(NULL));  
    int rdeger,tahmin;
    oyuncuNumarasi=1;

   

    signal(SIGALRM,toplamCevaplamaSuresiAlarm);
    alarm(B);

    rdeger = rand()%99;

    fprintf(f, "rdeger: %d\n",rdeger);
    fprintf(f, "A: %d B: %d\n",A,B);

    int minDeger=0;
    int maksDeger=99;

    while(1){

        if(oyuncuNumarasi==1){ //Oyuncu1
            clock_gettime(CLOCK_REALTIME, &baslangic);
            printf("Oyuncu 1 [%d-%d] arasý bir sayý girsin:",minDeger,maksDeger);
           
            scanf("%d",&tahmin);
            
            clock_gettime(CLOCK_REALTIME, &bitis);
            long seconds = bitis.tv_sec - baslangic.tv_sec;
            long nanoseconds = bitis.tv_nsec - baslangic.tv_nsec;
            int gecenSure = (seconds + nanoseconds*1e-9)*1000;

            if((gecenSure/1000) > A){
                printf("\nSüre bitti. Oyuncu 1 kaybetti.");
                fprintf(f,"oyuncu1 gereken sürede cevaplamadý.\nKazanan: oyuncu2\n");
                printf("\nOyun sonlandýrýlýyor...");

                break;

            }



            fprintf(f,"oyuncu1 tahmini %d\n",tahmin);

            if(rdeger == tahmin){ 
                fprintf(f,"oyuncu1 geçen süre: %d ms\n",gecenSure); 
                printf("Doðru. Oyuncu 1 Kaybetti.\n");
                fprintf(f,"Kazanan: oyuncu2\n");
                
                break;               
                

            }else if((tahmin > maksDeger) || (tahmin < minDeger)){
             
                printf("Hata. Oyuncu 1 Kaybetti.\n");
                fprintf(f,"Kazanan: oyuncu2\n");
                
                break;
            
            }else{
                fprintf(f,"oyuncu1 geçen süre: %d ms\n",gecenSure);
                printf("Yanlýþ. Geçen süre: %d milisaniye\n",gecenSure);
                if((tahmin > minDeger) && (tahmin < maksDeger) && (tahmin < rdeger) ){
                    minDeger = tahmin;
                
                }else if((tahmin < maksDeger) && (tahmin > minDeger) && (tahmin > rdeger) ) {
                    maksDeger = tahmin;
                }

            }
            oyuncuNumarasi=2;
            
    

        }else if(oyuncuNumarasi==2){

            clock_gettime(CLOCK_REALTIME, &baslangic);

            printf("Oyuncu 2 [%d-%d] arasý bir sayý girsin:",minDeger,maksDeger);
            scanf("%d",&tahmin);

            clock_gettime(CLOCK_REALTIME, &bitis);
            long seconds = bitis.tv_sec - baslangic.tv_sec;
            long nanoseconds = bitis.tv_nsec - baslangic.tv_nsec;
            int gecenSure = (seconds + nanoseconds*1e-9)*1000;

            
            if((gecenSure/1000) > A){
                printf("\nSüre bitti. Oyuncu 2 kaybetti.");
                fprintf(f,"oyuncu2 gereken sürede cevaplamadý.\nKazanan: oyuncu1\n");
                printf("\nOyun sonlandýrýlýyor...");

                break;
            }

            fprintf(f,"oyuncu2 tahmini %d\n",tahmin);
            


            if(rdeger == tahmin){ 
                fprintf(f,"oyuncu2 geçen süre: %d ms\n",gecenSure);
                printf("Doðru. Oyuncu 2 Kaybetti.\n");
                fprintf(f,"Kazanan: oyuncu1\n");
               
                break;

            }else if((tahmin > maksDeger) || (tahmin < minDeger)){
             
                printf("Hata. Oyuncu 2 Kaybetti.\n");
                fprintf(f,"Kazanan: oyuncu1\n");
                
                break;
            
            }else{
                fprintf(f,"oyuncu2 geçen süre: %d ms\n",gecenSure);
                printf("Yanlýþ. Geçen süre: %d milisaniye\n",gecenSure);
                if((tahmin > minDeger) && (tahmin < maksDeger) && (tahmin < rdeger) ){
                    minDeger = tahmin;
                
                }else if((tahmin < maksDeger) && (tahmin > minDeger) && (tahmin > rdeger)) {
                    maksDeger = tahmin;
                }

            }

            oyuncuNumarasi=1;

        }     
    }

    clock_gettime(CLOCK_REALTIME, &oyunBitis);
    long seconds_2 = oyunBitis.tv_sec - oyunBaslangic.tv_sec;
    long nanoseconds_2 = oyunBitis.tv_nsec - oyunBaslangic.tv_nsec;
    int toplamSure = (seconds_2 + nanoseconds_2*1e-9)*1000;
    
    fprintf(f,"Toplam süre: %d ms",toplamSure);
}

int main(int argc, char *argv[]){
    int A = atoi(argv[1]);
    int B = atoi(argv[2]);
    
    f=fopen("oyun_bilgi.txt","w");
	
	if(f==NULL){
		printf("\nDosya Oluþturulamadý.");
	}

    oyun(A,B);

    fclose(f);

    return 0;
}

