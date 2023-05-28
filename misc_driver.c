#include<linux/miscdevice.h> //misc_register and misc_deregister
#include<linux/fs.h>  //struct file definition
#include<linux/kernel.h> //pr_info
#include<linux/init.h> 
#include<linux/module.h>  //THIS_MODULE , module_init and module_exit
#define BUFFER_SIZE 256
#include<linux/ioctl.h>    
#include<linux/err.h>     
#include<linux/uaccess.h>     //copy_to_user and copy_from_user

#define CREATE_TRACE_POINTS
#include <trace/events/shubhangi.h> // Include tracepoint header

#define SHUBHANGI_WRITE _IOW(0xB8,0x31,char*) //major and minor number which doesn't conflict with existing devices
#define SHUBHANGI_READ _IOR(0xB8,0x32,char*)

static int etx_misc_open(struct inode *inode, struct file *file){
	pr_info("misc device open\n");
	return 0;
}
static int etx_misc_close(struct inode *inodep, struct file *filp){
	pr_info("misc device close\n");
	return 0;
}
static ssize_t etx_misc_write(struct file *filp, const char __user *buf, size_t count, loff_t *offp){
/*filp is the file pointer,
 * count is the size of requested data transfer,
 *  buff points to the user buffer holding the data to be written or,
 *   the empty buffer where the newly read data should be placed.
 *   loff_t - long offset type, offp indicates the file position the user is accessing
 *the buff argument to the read and write methods is a user-space pointer. Therefore, it cannot be directly dereferenced by kernel code

*/
	pr_info("misc device write\n");
	    char kernel_buffer[BUFFER_SIZE];

    if (count >= BUFFER_SIZE) {
        // Buffer overflow protection
        return -1;
    }

    // Copy data from user space to kernel buffer
    if (copy_from_user(kernel_buffer, buf, count))
        pr_info("Couldn't be written to kernel buffer\n");

    // Print received data to kernel logs
    printk(KERN_INFO "Received data from user: %s\n", kernel_buffer);

    // Return the number of bytes written
	return count;
}
static ssize_t etx_misc_read(struct file *filp, char __user *buf, size_t count, loff_t *offp){
	pr_info("misc device read\n"); //f_pos is the current reading or writing position, loff_t is a 64_bit value (basically long long )
    char kernel_buffer[BUFFER_SIZE] = "Data from driver";

    size_t buffer_length = strlen(kernel_buffer);
    size_t bytes_to_copy = min(buffer_length, count);

    // Copy data from kernel buffer to user space
    if (copy_to_user(buf, kernel_buffer, bytes_to_copy)) //returns no. of bytes that couldn't be copied, so returns 0 on success
        pr_info("couldn't be read from kernel buffer\n");

    // Return the number of bytes read
    return bytes_to_copy;
}
static long int my_ioctl(struct file *filp, unsigned cmd, unsigned long arg){
	//int32_t value=20;
	char kernel_read_buffer[BUFFER_SIZE];
	char kernel_buffer[BUFFER_SIZE]="Hi user ~ from kernel!";
	switch(cmd){
		case SHUBHANGI_WRITE:
			
			if(copy_from_user(kernel_read_buffer,(char*)arg,sizeof(kernel_read_buffer)) ){
					pr_err("data write err!\n");
			}
			pr_info("ioctl write value=%s\n",kernel_read_buffer);
			break;
		case SHUBHANGI_READ:
			if(copy_to_user((char*)arg,kernel_buffer,sizeof(kernel_buffer)) ){
				pr_err("data read err~!\n");
			}
			pr_info("ioctl read done!\n");
			// trigger the tracepoint
			trace_shubhangi_tracepoint(kernel_buffer);
			break;
		default:
			pr_info("default\n");
			break;
	}
	return 0;
}
static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.write = etx_misc_write,
	.read = etx_misc_read,
	.open = etx_misc_open,
	.release = etx_misc_close,
	.unlocked_ioctl = my_ioctl,
	.llseek = no_llseek,  //The llseek method is used to change the current read/write position in a file, and the new position is returned as a (positive) return value.
};
struct miscdevice etx_misc_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "shubhangi_misc_driver",
	.fops = &fops,
};
static int __init misc_init(void){
	int err;
	err = misc_register(&etx_misc_device); //The structure (etx_misc_device here) passed is linked into the kernel and may not be destroyed until it has been unregistered.
	if(err){
		pr_err("misc_register failed\n");
		return err;
	}
	pr_info("misc_register init done!!\n");
	return 0;
}
static void __exit misc_exit(void){
	misc_deregister(&etx_misc_device);
	pr_info("misc_register exit done!\n");
}
module_init(misc_init);
module_exit(misc_exit);
MODULE_LICENSE("GPL");

