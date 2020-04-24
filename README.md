# SoalShiftSISOP20_modul4_B07
## Soal1
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
## Soal2
## Soal3
## Soal4
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
