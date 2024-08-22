#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <linux/serial.h>
/* Include definition for RS485 ioctls: TIOCGRS485 and TIOCSRS485 */
#include <sys/ioctl.h>

struct serial_rs485 rs485conf;
/* Enable RS485 mode: */

int main()
{
    int serial_port_num;
    char serial_port[15];

    printf("Select a serial port (3/4): ");
    scanf("%d", &serial_port_num);

    sprintf(serial_port, "/dev/ttyS%d", serial_port_num);
    int serial_fd;

    //serial_fd = open(serial_port, O_RDWR | O_NOCTTY);
    serial_fd = open(serial_port, O_RDWR);
    if (serial_fd == -1)
    {
        perror("Failed to open serial port");
        return 1;
    }

    /* Enable RS485 mode: */
    rs485conf.flags |= SER_RS485_ENABLED;

    /* Set logical level for RTS pin equal to 1 when sending: */
    rs485conf.flags |= SER_RS485_RTS_ON_SEND;
    /* or, set logical level for RTS pin equal to 0 when sending: */
    rs485conf.flags &= ~(SER_RS485_RTS_ON_SEND);

    /* Set logical level for RTS pin equal to 1 after sending: */
    rs485conf.flags |= SER_RS485_RTS_AFTER_SEND;
    /* or, set logical level for RTS pin equal to 0 after sending: */
    rs485conf.flags &= ~(SER_RS485_RTS_AFTER_SEND);

    /* Set rts delay before send, if needed: */
    //rs485conf.delay_rts_before_send = 1000;

    /* Set rts delay after send, if needed: */
    //rs485conf.delay_rts_after_send = 1000;

    /* Set this flag if you want to receive data even while sending data */
    rs485conf.flags |= SER_RS485_RX_DURING_TX;

    if (ioctl (serial_fd, TIOCSRS485, &rs485conf) < 0) {
        /* Error handling. See errno. */
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if (tcgetattr(serial_fd, &tty) != 0)
    {
        perror("Error from tcgetattr");
        return 1;
    }

    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;

    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0)
    {
        perror("Error from tcsetattr");
        return 1;
    }

    char tx_buffer[50];// = "hello world!\n";
    int size = sprintf(tx_buffer,"Port: %s\n", serial_port);

    ssize_t bytes_written = write(serial_fd, tx_buffer, size/*sizeof(tx_buffer)*/);
    if (bytes_written < 0)
    {
        perror("Error writing to serial port");
        close(serial_fd);
        return 1;
    }
    printf("\rtx_buffer: \n %s ", tx_buffer);

    char rx_buffer[256];
    int bytes_read = read(serial_fd, rx_buffer, sizeof(rx_buffer));
    if (bytes_read > 0)
    {
        rx_buffer[bytes_read] = '\0';
        printf("\rrx_buffer: \n %s ", rx_buffer);
    }
    else
    {
        printf("No data received.\n");
    }

    close(serial_fd);

    return 0;
}