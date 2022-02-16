#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/cdev.h>

static dev_t first;
static unsigned int count = 1, bytes = 0;
static int my_major = 240, my_minor = 0;
static struct cdev* my_cdev;
static char buf[10];

#define MYDEV_NAME "mychardev"
#define KBUF_SIZE (size_t) ((10) * PAGE_SIZE)

static int mychrdev_open(struct inode* inode, struct file* file){
	static int counter = 0;
	char *kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
	file->private_data = kbuf;
	counter++;
	return sprintf(buf, "%d %d\n", counter, bytes);
}

static int mychrdev_release(struct inode* inode, struct file* file){
	char *kbuf= file->private_data;
	if(kbuf)
		kfree(kbuf);
	kbuf = NULL;
	file->private_data = NULL;
	return 0;
}

static ssize_t mychrdev_read(struct file* file, char __user *buf,
			   size_t lbuf, loff_t *ppos){
	char *kbuf = file->private_data;
	int nbytes = lbuf - copy_to_user(buf, kbuf + *ppos, lbuf);
	*ppos += nbytes;
	return nbytes;
}

static ssize_t mychrdev_write(struct file* file,
               const char __user *buf, size_t lbuf, loff_t *ppos){
	char *kbuf = file->private_data;
	int nbytes = lbuf - copy_from_user(kbuf + *ppos, buf, lbuf);
	*ppos += nbytes; bytes += nbytes;
	return nbytes;
}

static const struct file_operations mycdev_fops = {
	.owner   = THIS_MODULE,
	.read    = mychrdev_read,
	.write   = mychrdev_write,
	.open    = mychrdev_open,
	.release = mychrdev_release
};

static int __init init_chrdev(void){
	printk(KERN_INFO "Hello, loading\n");

	first = MKDEV(my_major, my_minor);
	register_chrdev_region(first, count, MYDEV_NAME);
	
	my_cdev = cdev_alloc();

	cdev_init(my_cdev, &mycdev_fops);
	cdev_add(my_cdev, first, count);
	return 0;
}

static void __exit cleanup_chrdev(void){
	printk(KERN_INFO "Leaving\n");
	if(my_cdev)
		cdev_del(my_cdev);
	unregister_chrdev_region(first, count);
}

module_init(init_chrdev);
module_exit(cleanup_chrdev);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("sample_chrdev_module");
MODULE_AUTHOR("Aleks Zhuk <aleks.m.zhuk@gmail.com>");
