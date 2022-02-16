#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <checker.h>
 
extern int array_sum(short *arr, size_t n);
extern ssize_t generate_output(int sum, short *arr, size_t size, char *buf);

static int __init solution_init(void){
	short arr_1[] = {1, 2, 3, 4, 5, 6, 7};
	int sum_arr_1 = 28; int i;
    for(i=0; i<10; ++i) {
        char buffer[500] = {0};
		int sum_1 = array_sum(arr_1, sizeof(arr_1)/sizeof(short));
		generate_output(sum_1, arr_1, sizeof(arr_1)/sizeof(short), buffer);
		if(sum_1 == sum_arr_1)
			printk(KERN_INFO "%s\n", buffer);
		else 
			printk(KERN_ERR "%s\n", buffer);
    } 
	CHECKER_MACRO;
    return 0;
}

static void __exit solution_exit(void){
	CHECKER_MACRO;
    return;
}

module_init(solution_init);
module_exit(solution_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("sample_hello_module");
MODULE_AUTHOR("Aleks Zhuk <aleks.m.zhuk@gmail.com>");
