#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

main(){
	int std, lfd, len, choice, cport;
	char str[20], str1[20], err[20];
	cport = 8888;
	struct sockaddr_in saddr, caddr;

	std = socket(AF_INET, SOCK_STREAM, 0);
	if(std<0)
		perror("Error");

	bzero(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr);
	saddr.sin_port = htons(cport);
	connect(std, (struct sockaddr *)&saddr, sizeof(saddr));
	for(;;)	{
		read(std, str, 20);
		if(strcmp(str, "Exit") == 0){
			printf("Exitting!\n");
			break;
		}
		printf("Received: %s\nError?(1 - YES or 0 - NO): ", str);
		scanf("%d", &choice);
		if(choice == 0)write(std, "-1", sizeof("-1"));
		else{
			printf("Enter the sequence no of the frame where error has occured");
			scanf("%s", err);
			write(std, err, sizeof(err));
			read(std, str, 20);
			printf("Received the transmitted frame: %s\n", str);
		}
	}
	close(std);
}
