#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/kernel.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL v2");

const struct i2c_device_id at24cxx_id[] = 
{
		{"at24cxx",0},
		{}/*结束标志*/
};

dev_t dev;

struct cdev cdev;
struct i2c_client *at_client = NULL;
struct class *dev_class = NULL;
struct device *dev_device  =NULL;


static ssize_t at24cxx_read(struct file*filp,char __user *buf,size_t count,loff_t *offset)
{
	unsigned char addr;
	unsigned char data;

	// 1.获取用户要访问的地址
	copy_from_user(&addr,buf,1);

	// 2.把地址发送到I2C总线上
	data = i2c_smbus_read_byte_data(at_client, addr);

	// 3.把数据上报到用户空间
	copy_to_user(buf,&data,1);

	return count;
}

static ssize_t at24cxx_write(struct file*filp,const char __user *buf,size_t count,loff_t *offset)
{
	unsigned char buffer[2];
	int ret;

	// 1.获取用户要访问的地址
	copy_from_user(buffer, buf, 2);

	// 2.把地址和数据发送到I2C总线上
	ret = i2c_smbus_write_byte_data(at_client, buffer[0], buffer[1]);
	if(ret<0)
		return -EIO;
	
	return count;
}

struct file_operations at24cxx_fops = 
{
	.owner = THIS_MODULE,
	.read = at24cxx_read,
	.write = at24cxx_write,
};

int at24cxx_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	alloc_chrdev_region(&dev, 0, 1, "at24cxx");
	cdev_init(&cdev, &at24cxx_fops);
	cdev_add(&cdev, dev, 1);
	dev_class = class_create(THIS_MODULE, "at24cxx");
	dev_device = device_create(dev_class, NULL, dev, NULL, "at24cxx");

	at_client = client;

	return 0;
}

int at24cxx_remove(struct i2c_client *client)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&cdev);
	unregister_chrdev_region(dev, 1);

	return 0;
}

struct i2c_driver at24cxx_drv = 
{
	.driver = 
	{
		.name = "at24cxx",
		.owner = THIS_MODULE,
	},
	.probe = at24cxx_probe,
	.remove = at24cxx_remove,
	//匹配时使用
	.id_table = at24cxx_id,
};

static int __init at24cxx_init(void)
{
	i2c_add_driver(&at24cxx_drv);
	return 0;
}

static void __exit at24cxx_exit(void)
{
	i2c_del_driver(&at24cxx_drv);
}

module_init(at24cxx_init);
module_exit(at24cxx_exit);
