    /*
    Created by luigi on 24/01/2024.
     Client in c che utilizza le socket per comunicare con
     il server e leggere dati mandati da quest'ultimo


     La socket prende tre parametri(int famiglia,int tipo,int protocollo)
    */

    //Includiamo le librerie necessarie
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    //#include <sys/socket.h>
    //#include <arpa/inet.h>
    //Il main prende due argomenti. Il primo indica il numero di parametri
    //Il secondo invece è un array con gli elementi che contiene
    int main(int argc,char **argv)
    {
        int sockfd,n;
        char recvline[1025];
        struct sockaddr_in servaddr;
        //Il numero dei parametri inseriti deve essere uguale a 2
        if(argc!=2)
        {
            fprintf(stderr,"usage: %s <IPaddress> \n",argv[0]);
            exit(1);
        }
        //La socket ci da in output un intero che è un descrittore univoco che ci permette
        //Di riferirci a quella soocket. Se <0 allora cìè stato un errore
        if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
        {
            fprintf(stderr,"socket error \n");
        }
        //Riempiamo i campi della struct
        servaddr.sin_family=AF_INET;
        //Conversione della porta in network order
        servaddr.sin_port=htons(65000);
        //Conversione dell'indirizzo ip in network order e salvataggio in servaddr
        if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0)
        {
            fprintf(stderr,"inet_pton error for %s \n",argv[1]);
            exit(1);
        }
        //Associa la socket all'indirizzo
        if(connect(sockfd,(struct sockaddr *)&servaddr),sizeof(servaddr))<0)
        {
            fprintf(stderr,"connect error\n");
            exit(1);
        }

        while((n=read(sockfd,recvline,1024))>0)
        {
            recvline[n]=0;
            if(fputs(recvline,stdout)==EOF)
            {
                fprintf(stderr,"fputs error\n");
                exit(1);
            }
        }
        if(n<0)
        {
            fprintf(stderr,"read error \n");
            exit(1);
        }else
        {
            printf("%d",n);
        }
        exit(0);
    }

