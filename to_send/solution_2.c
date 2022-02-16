#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <checker.h>
 
extern ssize_t get_void_size(void);       // size of any memory
extern void submit_void_ptr(void *p);     // check memory
extern ssize_t get_int_array_size(void);  // integer array
extern void submit_int_array_ptr(int *p); // check
extern void submit_struct_ptr(struct device *p);
extern void checker_kfree(void *p);       // free allocated memory

void* p1; int* p2; struct device* p3;

static int __init solution_init(void){
	ssize_t size_any = get_void_size();
    p1 = kmalloc(size_any, GFP_KERNEL);
    submit_void_ptr(p1);

	ssize_t size_array = get_int_array_size();
	p2 = (int*) kmalloc_array(size_array, sizeof(int), GFP_KERNEL);
	submit_int_array_ptr(p2);

	p3 = (struct device*) kmalloc(sizeof(struct device), GFP_KERNEL);
	submit_struct_ptr(p3);
    return 0;
}

static void __exit solution_exit(void){
	checker_kfree(p1);
	checker_kfree(p2);
	checker_kfree(p3);
    return;
}

module_init(solution_init);
module_exit(solution_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("sample_kernel_module");
MODULE_AUTHOR("Aleks Zhuk <aleks.m.zhuk@gmail.com>");
