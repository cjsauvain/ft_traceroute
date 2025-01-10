#include "ft_traceroute.h"

static struct msghdr	initialize_msghdr(void)
{
	struct msghdr		msghdr;
	struct sockaddr_in	sender_addr;
	char				buffer[BUFFER_SIZE];
	struct iovec		msg_iov;
	struct cmsghdr		cmsg;

	memset(&msghdr, 0, sizeof(msghdr));
	msghdr.msg_name = &sender_addr;
	msghdr.msg_namelen = sizeof(sender_addr);
	msghdr.msg_iov = &msg_iov;
	msghdr.msg_iovlen = 1;
	msghdr.msg_control = &cmsg;
	msghdr.msg_controllen = 
	msghdr.flags = 
}

void	receive_icmp_reply(int fd_socket)
{
	struct msghdr	msghdr;

	msghdr = initialize_msghdr();
	if (recvmsg(fd_socket, &msghdr, IP_RECVERR) == -1)
	{
		perror("recvmsg");
		exit(1);//do clean exit
	}
}
