/*
 * tcpserver.c
 *
 *  Created on: Apr 20, 2022
 *      Author: controllerstech.com
 */


#include "lwip/opt.h"

#include "lwip/api.h"
#include "lwip/sys.h"
#include "usart.h"
#include "tcpserver.h"
#include "string.h"
#include "MSGHandler.h"
static struct netconn *conn, *newconn;
static struct netbuf *buf;
static ip_addr_t *addr;
static unsigned short port;
char msg[100];
char smsg[200];


/**** Send RESPONSE every time the client sends some data ******/
static void tcp_thread(void *arg)
{
	//HAL_UART_Transmit(&huart3,"server tcp_thread\r\n",20,100);
	err_t err, accept_err, recv_error;

	/* Create a new connection identifier. */
	conn = netconn_new(NETCONN_TCP);

	if (conn!=NULL)
	{
		/* Bind connection to the port number 7. */
		err = netconn_bind(conn, IP_ADDR_ANY, 10);

		if (err == ERR_OK)
		{
			//HAL_UART_Transmit(&huart3,"server listening\r\n",20,100);
			/* Tell connection to go into listening mode. */
			netconn_listen(conn);

			while (1)
			{
				HAL_UART_Transmit(&huart3,"server ready\r\n",20,100);
				/* Grab new connection. */
				accept_err = netconn_accept(conn, &newconn);

				/* Process the new connection. */
				if (accept_err == ERR_OK)
				{
					HAL_UART_Transmit(&huart3,"server connected\r\n",20,100);
					/* receive the data from the client */
					while (netconn_recv(newconn, &buf) == ERR_OK)
					{

						/* Extrct the address and port in case they are required */
						addr = netbuf_fromaddr(buf);  // get the address of the client
						port = netbuf_fromport(buf);  // get the Port of the client

						/* If there is some data remaining to be sent, the following process will continue */
						do
						{

							strncpy (msg, buf->p->payload, buf->p->len);   // get the message from the client

							MSGReceive(msg);


							// Or modify the message received, so that we can send it back to the client
							int len = sprintf (smsg, "\"%s\" was sent by PROJECT JAVELIN\n", msg);
								HAL_UART_Transmit(&huart3,smsg,len,100);
							netconn_write(newconn, smsg, len, NETCONN_COPY);  // send the message back to the client
							memset (msg, '\0', 100);  // clear the buffer
						}
						while (netbuf_next(buf) >0);

						netbuf_delete(buf);
					}

					/* Close connection and discard connection identifier. */
					netconn_close(newconn);
					netconn_delete(newconn);
				}
			}
		}
		else
		{
			//HAL_UART_Transmit(&huart3,"netconn failed\r\n",20,100);
			netconn_delete(conn);
		}
	}
	//HAL_UART_Transmit(&huart3,"nullconn\r\n",20,100);
}


void tcpserver_init(void)
{
	//HAL_UART_Transmit(&huart3,"server made\r\n",20,100);
  sys_thread_new("tcp_thread", tcp_thread, NULL, DEFAULT_THREAD_STACKSIZE,osPriorityHigh);
}
