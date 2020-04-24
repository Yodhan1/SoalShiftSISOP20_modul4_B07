# SoalShiftSISOP20_modul4_B07
## Soal1
### Dekrip&Enkrip
Kodingan Mengkonversi path yang diberikan ke enkripsi atau dekripsi sesuai dengan state yang diberikan
```
char* Denkrip(char *Ori,int Den_key,int State){
    char Cori[107]="";
    strcpy(Cori,Ori);
    if(State == 1){
        Den_key*= -1;
    }
    int lenCode = strlen(Code);
    int lenOri = strlen(Cori);
    if(Cori[lenOri-4]=='.'){
        lenOri -= 4;
    }
    for (int i = 0;i < lenOri;i++){
        for(int j = 0; j < lenCode;j++){
            if(Cori[i] == Code[j]){
                int Shift;
                Shift = j + Den_key;
                Cori[i] = Code[(Shift+lenCode)%lenCode];
                j=lenCode;
            }
        }
    }
    return Cori;
}
```
- ```Ori``` mengambil path yang dituju
- ``` Den_key``` key yang digunakan untuk enkripsi
- ```State``` apakah dipakai untuk enkripsi(0) atau dekripsi(1)
- ```Den_key*= -1``` jika dekripsi maka nilainya dibalik
- ```if(Cori[lenOri-4]=='.')``` jika nilai tersebut merupakan ektensi maka tidak diubah extensinya
- ```Shift = j + Den_key``` memasukan index dan jauh pengkonversian
- ```Cori[i] = Code[(Shift+lenCode)%lenCode]``` mengubah nilai sejauh nilai yang diinginkan (penambahan untuk menghindari nilai negatif)
- ```return Cori``` mengembalikan string yang sudah dikonversi
kendala : tidak tahu apa yang harus di masukin dan di berikan kedalam fungsi
## Soal2
### Enkrip
mengenkripsi dengan memotongnya jadi beberapa bagian
```
void Enkrip_2(char *filename,size_t size){
    char * buffer = (char *)malloc(1024);
    FILE *exsistingFile = fopen(filename,"rb"),*outputFile;
    int fileCount=0;
    char newFileName[1007]="";
    size_t chunkSize;
    do
    {   
        sprintf (newFileName,"%s.%03d",filename,fileCount);
        fileCount ++;
        outputFile = fopen(newFileName,"w");
        chunkSize = size > 1024 ? 1024 : size;
        chunkSize = fread( buffer, sizeof( char ), chunkSize, exsistingFile );
        size -= chunkSize;
        fwrite(buffer,sizeof(char),chunkSize,outputFile);
        fclose(outputFile);

    } while ( size > 0 );
}
```
- ```filename``` mendapatkan path dari file yang ingin dikonversi
- ```size``` untuk menentukan besar dari file
- ```char * buffer = (char *)malloc(1024)``` untuk tempat penyimpanan nilai
- ```FILE *exsistingFile = fopen(filename,"rb"),*outputFile```membuka file yang akan di potong potong; rb digunakan untuk baca perbyte
- ```sprintf (newFileName,"%s.%03d",filename,fileCount)``` menamai bagian potongan file
- ```outputFile = fopen(newFileName,"w")``` membuka file yang akan diisi
- ```chunkSize = size > 1024 ? 1024 : size``` mengecek apakah lebih besar size atau 1024 mengambil yang lebih keci;
- ```chunkSize = fread( buffer, sizeof( char ), chunkSize, exsistingFile )``` menbaca sebanyak chunk
- ```size -= chunkSize;``` mengurangi total size dari file
- ```fwrite(buffer,sizeof(char),chunkSize,outputFile)``` menulis di dalam file
- ```while ( chunkSize > 0 )``` selama file masih dapat dipotong maka dipotong terus
### Dekrip
mengdekripsi program dengan menyatukan kembali sehingga dapat dibaca?
```
void Denkrip_2(char *filename){
    FILE *NewFile = fopen(filename,"w"),*inputFile;
    int fileCount=0;
    char oldFileName[1007]="",ch;
    sprintf (oldFileName,"%s.%03d",filename,fileCount);
    inputFile = fopen(oldFileName,"r");
    while ( inputFile != NULL )
    {   
        while( ( ch = fgetc(inputFile) ) != EOF )
	      fputc(ch,NewFile);
        fclose(inputFile);
        fileCount ++;
        sprintf (oldFileName,"%s.%03d",filename,fileCount);
        inputFile = fopen(oldFileName,"r");
    }
}
```
- ```filename``` mendapatkan path dari file yang ingin dikonversi
- ```size``` untuk menentukan besar dari file
- ```FILE *NewFile = fopen(filename,"wb"),*inputFile```membuka file yang akan di potong potong
- ```sprintf (oldFileName,"%s.%03d",filename,fileCount);``` menamai bagian pegabungan file
- ```inputFile = fopen(oldFileName,"r")``` membuka file yang akan diisi
- ```while( ( ch = fgetc(inputFile) ) != EOF )``` menbaca sampai habis file
- ```fputc(ch,NewFile)``` memasukan char ke tujuan
kendala : tidak tahu apa yang harus di masukin dan di berikan kedalam fungsi
## Soal3
Soal tidak dikerjakan karena tidak paham apa yang harus dibuat
## Soal4
### LOG
Kodingan mengambil nilai Level , CMD dan Desc yang diberikan untuk ditambahkan dengan time
```
void Log(char *Level,char*CMD,char *Desc)
{
    time_t times=time(NULL);
    char now[100];
	strftime(now,100,"%Y%m%d-%H:%M:%S",localtime(&times));
    char Res[107];
    char filePath[1007]="/home/yodhan/fs.log";
    sprintf(Res,"%s::%s::%s::%s",Level,now,CMD,Desc);
    FILE *fPtr;
    fPtr = fopen(filePath, "a");
    fputs(Res, fPtr);
    fclose(fPtr);
}
```
- ```Level``` berisi antara "INFO" atau "WARNING"
- ```CMD``` berisi command yang menjalanakan
- ```Desc``` berisi semua path yang didapatkan
- ```char now[100]``` menyimpan nilai dari time
- ```strftime(now,100,"%Y%m%d-%H:%M:%S",localtime(&times))``` memasukan nilai dari Time
- ```char filePath[1007]="/home/yodhan/fs.log"``` memasukan path yang dituju
- ```fPtr = fopen(filePath, "a"); fputs(Res, fPtr);``` membuka dan memasukan input kedalam file

