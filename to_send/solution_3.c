/*
* simple kobject implementation
*  kobject with name /sys/kernel/my_kobject/my_sys
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>

static struct kobject *my_kobj;
static int count = 0;

static ssize_t my_sys_show(struct kobject *my_kobj, struct kobj_attribute *attr,
                		   char *buf)
{
	count++;
	return sprintf(buf, "%d\n", count);
}

static ssize_t my_sys_store(struct kobject *my_kobj, struct kobj_attribute *attr,
			                const char *buf, size_t cnt)
{
	int ret;
	ret = kstrtoint(buf, 10, &count);
	if(ret < 0)
		return ret;
	return cnt;
}

static struct kobj_attribute my_sys_attribute =
                                  __ATTR(my_sys, 0664, my_sys_show, my_sys_store);

static int __init solution_init(void)
{
	int ret;
	my_kobj = kobject_create_and_add("my_kobject", kernel_kobj);
	if (!my_kobj)
		return -ENOMEM;  

    ret = sysfs_create_file(my_kobj, &my_sys_attribute.attr);
    if (ret)
		kobject_put(my_kobj);

	return ret;
}

static void __exit solution_exit(void)
{
	printk(KERN_INFO "Leaving my_kobject\n");
	kobject_put(my_kobj);
	return;		
}

module_init(solution_init);
module_exit(solution_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("sample_hello_module");
MODULE_AUTHOR("Aleks Zhuk <aleks.m.zhuk@gmail.com>");
