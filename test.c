#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h> //O_RDWR flag which means open file for reading and writing is here
 // File control header file
#include<sys/ioctl.h> // Input/output control header file
#include<sys/stat.h> // File status header file
#include<unistd.h> // close
#define BUFFER_SIZE 256
#define MSHV_SHUBHANGI_WRITE _IOW(0xB8,0x31,char*)
#define MSHV_SHUBHANGI_READ _IOR(0xB8,0x32,char*)
int main(){
        printf("Opening driver\n");
        int fd = open("/dev/shubhangi_misc_driver",O_RDWR); // Open device driver file with read and write permissions
        if(fd < 0){
                printf("Can't open the device file\n");
                return 0;
        }
        char write_buffer[BUFFER_SIZE] = "Hello, driver!";
        char read_buffer[BUFFER_SIZE];
        // Writing to the driver
        printf("Writing to driver: %s\n", write_buffer);
        write(fd, write_buffer, strlen(write_buffer));
        // Reading from the driver
         printf("Reading from driver\n");
         ssize_t num_bytes_read = read(fd, read_buffer, BUFFER_SIZE);
         if (num_bytes_read < 0) {
                 perror("Error reading from driver");
                 close(fd);
                 return 0;
    }
         read_buffer[num_bytes_read] = '\0';  // Null-terminate the string
        printf("Read: %s\n", read_buffer);
        printf("Ioctl write to kernel space/driver\n");
        //int32_t value=5;
        ioctl(fd,MSHV_SHUBHANGI_WRITE,write_buffer);
        printf("ioctl reading from kernel space\n");
        ioctl(fd,MSHV_SHUBHANGI_READ,read_buffer);
        printf("ioctl read %s from kernel space\n",read_buffer);
        printf("Closing Driver\n");
        close(fd);
}