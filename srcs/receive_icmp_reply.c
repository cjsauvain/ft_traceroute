#include "ft_traceroute.h"

static struct msghdr	initialize_msghdr(void)
{
	struct msghdr		msghdr;
	struct sockaddr		sender_addr;
	char				buffer[BUFFER_SIZE];
	struct iovec		msg_iov;
	char 				control_buffer[BUFFER_SIZE];

	msg_iov.iov_base = buffer;
	msg_iov.iov_len = BUFFER_SIZE;

	memset(&msghdr, 0, sizeof(msghdr));
	msghdr.msg_name = &sender_addr;
	msghdr.msg_namelen = sizeof(sender_addr);
	msghdr.msg_iov = &msg_iov;
	msghdr.msg_iovlen = 1;
	msghdr.msg_control = control_buffer;
	msghdr.msg_controllen = BUFFER_SIZE;

	return msghdr;
}

static void	check_errno(void)
{
	if (errno == EAGAIN)
		printf("errno: EAGAIN\n");
	if (errno == EWOULDBLOCK)
		printf("errno: EWOULDBLOCK\n");
	if (errno == EBADF)
		printf("errno: EBADF\n");
	if (errno == ECONNREFUSED)
		printf("errno: ECONNREFUSED\n");
	if (errno == EFAULT)
		printf("errno: EFAULT\n");
	if (errno == EINTR)
		printf("errno: EINTR\n");
	if (errno == EINVAL)
		printf("errno: EINVAL\n");
	if (errno == ENOMEM)
		printf("errno: ENOMEM\n");
	if (errno == ENOTCONN)
		printf("errno: ENOTCONN\n");
	if (errno == ENOTSOCK)
		printf("errno: ENOTSOCK\n");
}

void	receive_icmp_reply(int fd_socket)
{
	struct msghdr	msghdr;

	memset(&msghdr, 0, sizeof(msghdr));
	msghdr = initialize_msghdr();
	if (recvmsg(fd_socket, &msghdr, MSG_ERRQUEUE) == -1)
	{
		//perror("recvmsg");
		check_errno();
		exit(1);//do clean exit
	}
}
