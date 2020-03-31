#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <netdb.h>  
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int port = 8090;

unsigned long get_file_size(const char *path)
{
    unsigned long filesize = -1;
    struct stat statbuff;
    if(stat(path, &statbuff) < 0)
	return filesize;
    else
        return statbuff.st_size;
}


int main(int argc, char **argv)
{
    unsigned long filesize;   
    int socket_descriptor; 
    int i;
    int iter=0;
    int rem;  
    char buf[4096];
    int fd; 
    int fd_ts = -1; 
    struct sockaddr_in address;
	int f_socket_descriptor;
	struct sockaddr_in f_address;
	int write_file;

  	write_file = 1;

	char led;
	char led_ctrl;
	int link_fd;
	unsigned int count=0;

/*
    led ^= 0x1;
    led_ctrl = led+0x30;
    write(led_fd, &led_ctrl, 1);
*/
#if 0
	 link_fd = open("/sys/class/gpio/gpio34/value", O_WRONLY);
        if(link_fd < 0) {
            printf("open gpio 34 state dev failed\n");
            return -1;
        }

#endif

#if 1
    bzero(&address,sizeof(address));  
    address.sin_family=AF_INET;  
    address.sin_addr.s_addr=inet_addr(argv[1]);
    address.sin_port=htons(port);  
  
    socket_descriptor=socket(AF_INET,SOCK_DGRAM,0);//IPV4
#endif
#if 1
                bzero(&f_address,sizeof(f_address));
                f_address.sin_family=AF_INET;
                f_address.sin_addr.s_addr=inet_addr("127.0.0.1");
                f_address.sin_port=htons(12555);

                f_socket_descriptor=socket(AF_INET,SOCK_DGRAM,0);//IPV4
#endif

/*
    filesize = get_file_size(argv[1]);
    printf("file size:%d\r\n", filesize);

    iter = filesize / 1400;
    rem = filesize % 1400;*/
    fd = open(argv[2], O_RDONLY);
    if(fd < 0) {
        printf("open %s failed\n", argv[1]);
        return -1;
    }
    if(argc == 4){
	fd_ts = open(argv[3], O_RDWR | O_CREAT);
    	if(fd_ts < 0) {
        	printf("open %s failed\n", argv[2]);
        	return -1;
    	}
    }
    do
    {   
        read(fd, buf, 1024); 
	if(fd_ts > 0)
		write(fd_ts, buf, 1024);      
        sendto(socket_descriptor,buf,1024,0,(struct sockaddr *)&address,sizeof(address));  
	sendto(f_socket_descriptor,buf,1024,0,(struct sockaddr *)&f_address,sizeof(f_address));
	count ++;
	if(count >= 25){
		count=0;
		led ^= 0x01;
		led_ctrl = led+0x30;
	//	write(link_fd, &led_ctrl, 1);				
	}
    } while(1);
    /*
    read(fd, buf, rem);
    sendto(socket_descriptor,buf,rem,0,(struct sockaddr *)&address,sizeof(address)); */
    close(fd);
    close(fd_ts);
    close(socket_descriptor);  
    printf("send file finish\r\n");
}

