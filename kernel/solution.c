//#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
//#include <checker.h>

//extern call_me(const char* message); 

static int __init hello_init(void){
    //void call_me(KERN_INFO "Hello from my module");
    printk(KERN_INFO "Hello, loading\n");
    return 0;
}

static void __exit hello_exit(void){
    printk(KERN_INFO "Leaving\n");
    return;
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
