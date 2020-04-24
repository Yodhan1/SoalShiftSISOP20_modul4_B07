#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/wait.h>

static const char *dirpath = "/home/yodhan/Document";
static const  char *Code="9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO";

/*
void Findpath(char *path){
    int pathlen=strlen(path);
    char newpath[107]="";

    if(pathlen>6){
        char Cmp[6];
        // Cmp[0] = Path[0];
        // Cmp[1] = Path[1];
        // Cmp[2] = Path[2];
        // Cmp[3] = Path[3];
        // Cmp[4] = Path[4];
        // Cmp[5] = Path[5];
        strcpy(Cmp,path);//maybe need to change in future
        if(strcmp("encv1_",Cmp)==0){
            Den_key=7;
            strcpy(newpath,Denkrip(path,Den_key,0));
        }else if(strcmp("encv2_",Cmp)==0){
            
        }else{
            strcpy(newpath,path);
        }
    }
}*/
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

void Denkrip_2(char *filename){
    FILE *NewFile = fopen(filename,"wb"),*inputFile;
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

void Log(char *Level,char*CMD,char *Desc)
{
    time_t times=time(NULL);
    char now[100]="";
	strftime(now,100,"%Y%m%d-%H:%M:%S",localtime(&times));
    char Res[107]="";
    char filePath[1007]="/home/yodhan/fs.log";
    sprintf(Res,"%s::%s::%s::%s",Level,now,CMD,Desc);
    FILE *fPtr;
    fPtr = fopen(filePath, "a");
    fputs(Res, fPtr);
    fclose(fPtr);
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
	int res;

	res = lstat(path, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_access(const char *path, int mask)
{
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("INFO","access",Tujuan);
	int res;

	res = access(path, mask);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readlink(const char *path, char *buf, size_t size)
{
	int res;

	res = readlink(path, buf, size - 1);
	if (res == -1)
		return -errno;

	buf[res] = '\0';
	return 0;
}


static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(path);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		if (filler(buf, de->d_name, &st, 0))
			break;
	}

	closedir(dp);
	return 0;
}

static int xmp_mknod(const char *path, mode_t mode, dev_t rdev)
{
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("INFO","mknod",Tujuan);
	int res;
	/* On Linux this could just be 'mknod(path, mode, rdev)' but this
	   is more portable */
	if (S_ISREG(mode)) {
		res = open(path, O_CREAT | O_EXCL | O_WRONLY, mode);
		if (res >= 0)
			res = close(res);
	} else if (S_ISFIFO(mode))
		res = mkfifo(path, mode);
	else
		res = mknod(path, mode, rdev);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_mkdir(const char *path, mode_t mode)
{
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("INFO","mkdir",Tujuan);
	int res;

	res = mkdir(path, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_unlink(const char *path)
{
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("WARNING","unlink",Tujuan);
	int res;

	res = unlink(path);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_rmdir(const char *path)
{
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("WARNING","rmdir",Tujuan);
	int res;

	res = rmdir(path);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_symlink(const char *from, const char *to)
{
     char mix[1007]="";
    strcpy(mix,from);
    strcpy(mix,"::");
    strcpy(mix,to);
    Log("INFO","symlink",mix);
	int res;

	res = symlink(from, to);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_rename(const char *from, const char *to)
{
    char mix[1007]="";
    strcpy(mix,from);
    strcpy(mix,"::");
    strcpy(mix,to);
    Log("INFO","rename",mix);
	int res;

	res = rename(from, to);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_link(const char *from, const char *to)
{
     char mix[1007]="";
    strcpy(mix,from);
    strcpy(mix,"::");
    strcpy(mix,to);
    Log("INFO","link",mix);
	int res;

	res = link(from, to);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_chmod(const char *path, mode_t mode)
{
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("INFO","chmod",Tujuan);
	int res;

	res = chmod(path, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_chown(const char *path, uid_t uid, gid_t gid)
{
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("INFO","chown",Tujuan);
	int res;

	res = lchown(path, uid, gid);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_truncate(const char *path, off_t size)
{
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("INFO","truncate",Tujuan);
	int res;

	res = truncate(path, size);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_utimens(const char *path, const struct timespec ts[2])
{
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("INFO","itimens",Tujuan);
	int res;
	struct timeval tv[2];

	tv[0].tv_sec = ts[0].tv_sec;
	tv[0].tv_usec = ts[0].tv_nsec / 1000;
	tv[1].tv_sec = ts[1].tv_sec;
	tv[1].tv_usec = ts[1].tv_nsec / 1000;

	res = utimes(path, tv);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_open(const char *path, struct fuse_file_info *fi)
{
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("INFO","open",Tujuan);
	int res;

	res = open(path, fi->flags);
	if (res == -1)
		return -errno;

	close(res);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,struct fuse_file_info *fi)
{
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("INFO","read",Tujuan);
	int fd;
	int res;

	(void) fi;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static int xmp_write(const char *path, const char *buf, size_t size,off_t offset, struct fuse_file_info *fi)
{
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("INFO","write",Tujuan);
	int fd;
	int res;

	(void) fi;
	fd = open(path, O_WRONLY);
	if (fd == -1)
		return -errno;

	res = pwrite(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static int xmp_statfs(const char *path, struct statvfs *stbuf)
{
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("INFO","statfs",Tujuan);
	int res;

	res = statvfs(path, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_create(const char* path, mode_t mode, struct fuse_file_info* fi) {
    char Tujuan[107]="";
    strcpy(Tujuan,path);
    Log("INFO","crate",Tujuan);
    (void) fi;

    int res;
    res = creat(path, mode);
    if(res == -1)
	return -errno;

    close(res);

    return 0;
}



static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.access		= xmp_access,
	.readlink	= xmp_readlink,
	.readdir	= xmp_readdir,
	.mknod		= xmp_mknod,
	.mkdir		= xmp_mkdir,
	.symlink	= xmp_symlink,
	.unlink		= xmp_unlink,
	.rmdir		= xmp_rmdir,
	.rename		= xmp_rename,
	.link		= xmp_link,
	.chmod		= xmp_chmod,
	.chown		= xmp_chown,
	.truncate	= xmp_truncate,
	.utimens	= xmp_utimens,
	.open		= xmp_open,
	.read		= xmp_read,
	.write		= xmp_write,
	.statfs		= xmp_statfs,
	.create     = xmp_create,
};

int main(int argc, char *argv[])
{
    umask(0);
    return fuse_main(argc, argv, &xmp_oper, NULL);
}
