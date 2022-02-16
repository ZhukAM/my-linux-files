/*
*  simple kobject implementation 
*  kobject with param and name
*  /sys/kernel/my_kobject/my_sys
*  calculate sum a+b+c[@]
*  insmod module_name.ko a=@ b=@ c=@,@,@,@,@
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>

static int a = 0;
module_param (a, int, 0);

static int b = 0;
module_param (b, int, 0);

static int c[] = {0, 0, 0, 0, 0};
static int num = sizeof(c)/sizeof(c[0]);
module_param_array (c, int, &num, S_IRUGO | S_IWUSR);

static struct kobject *my_kobj;
static int sum = 0;

static ssize_t my_sys_show(struct kobject *my_kobj, struct kobj_attribute *attr,
                		   char *buf)
{
	return sprintf(buf, "%d\n", sum);
}

static ssize_t my_sys_store(struct kobject *my_kobj, struct kobj_attribute *attr,
			                const char *buf, size_t cnt)
{
	int ret;
	ret = kstrtoint(buf, 10, &sum);
	if(ret < 0)
		return ret;
	return cnt;
}

static struct kobj_attribute my_sys_attribute =
                                  __ATTR(my_sys, 0664, my_sys_show, my_sys_store);

static int __init solution_init(void){
	int i, ret;
	sum = a + b;
	
	my_kobj = kobject_create_and_add("my_kobject", kernel_kobj);
	if (!my_kobj)
		return -ENOMEM;  

    ret = sysfs_create_file(my_kobj, &my_sys_attribute.attr);
    if (ret)
		kobject_put(my_kobj);
	for (i = 0; i < num; i++){
		sum += c[i];
	}	
	printk(KERN_INFO "%d\n", sum);
	return 0;
}

static void __exit solution_exit(void){
	printk(KERN_INFO "Leaving my_kobject\n");
	kobject_put(my_kobj);
	return;
}

module_init(solution_init);
module_exit(solution_exit);
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("sample_kobject_module_with_param");
MODULE_AUTHOR("Aleks Zhuk <aleks.m.zhuk@gmail.com>");
