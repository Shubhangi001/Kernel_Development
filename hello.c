#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");
int __exit hello(void)
{
 pr_info("Hello, world\n");
 return 0;
}
void hello_exit(void)
{
 pr_info("Goodbye, cruel world\n");
}
module_init(hello);
module_exit(hello_exit);
