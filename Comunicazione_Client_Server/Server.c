    /*
        Created by luigi on 24/01/2024.
        Server che comunica con il client e gli manda una serie di dati
    */

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    //#include <sys/socket.h>
    //#include <arpa/inet.h>

    int main(int argc,char **argv)
    {
        int listenfd,connfd;
        struct sockaddr_in servaddr;
        char buff[4096];
        struct time_t ticks;


        //Apertura Socket
        if((listenfd=socket(AF_INET,SOCK_STREAM,0))<0)
        {
            perror("socket");
            exit(1);
        }
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        servaddr.sin_port=htons(65000);

        if(bind(listenfd,(struct sockaddr *) &servaddr,sizeof (servaddr))<0)
        {
            perror("bind");
            exit(1);
        }

        if(listen(listenfd,1024)<0)
        {
            perror("Listen");
            exit(1);
        }
        for(;;)
        {
            if((connfd=accept(listenfd,(struct sockaddr *)NULL,NULL))<0)
            {
                perror("Accept");
                exit(1);
            }
            ticks=time(NULL);
            snprintf(buff,sizeof (buff),"%.24s\r\n",ctime(&ticks));
            if(write(connfd,buff, strlen(buff))!= strlen(buff))
            {
                perror("write");
                exit(1);
            }
            close(connfd);
        }
    }


