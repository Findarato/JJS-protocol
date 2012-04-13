#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define SIZE 10000

main(){

	int std, lfd, len, i, j, status, sport;
	char str[1000], frame[20], temp[20], ack[20];
	struct sockaddr_in saddr, caddr;
	char * data;

	data = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
	sport = 8888;
	

	std = socket(AF_INET, SOCK_STREAM, 0);
	if(std<0)
		perror("Error");

	bzero(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(sport);
	lfd = bind(std, (struct sockaddr *)&saddr, sizeof(saddr));

	if(lfd)
	perror("Bind Error");

	listen(std, 5);
	len = sizeof(&caddr);
	lfd = accept(std, (struct sockaddr *)&caddr, &len);
	/*
	printf("Enter the text: ");
	scanf("%s", str);i = 0;
	*/

	printf(data);

	//str = data;
	
	while(i<strlen(str)){
		memset(frame, 0, 20);
		strncpy(frame, str+i, SIZE);
		printf("\nTransmitting frames: ");
		len = strlen(frame);
		for(j=0; j<len; j++){
			printf("%d", i+j);
			sprintf(temp, "%d", i+j);
			strcat(frame, temp);
		}


		write(lfd, frame, sizeof(frame));
		read(lfd, ack, 20);
		sscanf(ack, "%d", &status);
		if(status == -1)
			printf("\nTransmission successful");
		else{
			printf("Received error in: %d", status);
			printf("\nRetransmitting frame");
			frame[0] = str[status];
			frame[1] = '\0';write(lfd, frame, sizeof(frame));
		}
		i = i + SIZE;
	}

	write(lfd, "Exit", sizeof("Exit"));
	printf("\nExitting!\n");
	sleep(2);
	close(lfd);
	close(std);
} 