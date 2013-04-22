/*****************************************************************************
 *
 * Øving 3 uCSysDes, driverkoden
 *
 *****************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/slab.h> /* kmalloc() */

#include "ap7000.h"



/* prototyper */

static int __init driver_init(void);
static void __exit driver_exit(void);
static int driver_open (struct inode *inode, struct file *filp);
static int driver_release (struct inode *inode, struct file *filp);
static ssize_t driver_read (struct file *filp, char __user *buff,
                     size_t count, loff_t *offp);
static ssize_t driver_write (struct file *filp, const char __user *buff,
                      size_t count, loff_t *offp);

/* fops-struct */

static struct file_operations driver_fops = {
  .owner = THIS_MODULE,
  .read = driver_read,
  .write = driver_write,
  .open = driver_open,
  .release = driver_release
};


/* Global variables of the driver */
/* Major number */
int major;

int per_res, puer_res, ier_res, perLED_res, oer_res;


/* Buffer to store data */
char *memory_buffer;
char *button_buffer;
char *led_buffer;




/*****************************************************************************/
/* init-funksjon (kalles når modul lastes) */


#define DEVICE_NAME "STK1000_LEDBUTTON_DRIVER"

volatile avr32_pio_t *piob = &AVR32_PIOB;
volatile avr32_pio_t *pioc = &AVR32_PIOC;

struct cdev *driver;
void button_isr(void) {

}
static int __init driver_init (void) {

  printk("<1> driver_init\n");
  /* allokere device-nummer */
  major = 252;
  int result;
  result = register_chrdev(major, DEVICE_NAME, &driver_fops);
  if (result < 0) {
    printk("<1>memory: cannot obtain major number %d\n", major);
    return result;
  }

  
  button_buffer = kmalloc(1, GFP_KERNEL); 
  if (!button_buffer) { 
    driver_exit(); 
    return -ENOMEM;
  } 
  memset(button_buffer, 0, 1);
  
  led_buffer = kmalloc(1, GFP_KERNEL); 
  if (!led_buffer) { 
    driver_exit(); 
    return -ENOMEM;
  } 
  memset(led_buffer, 0, 1);

  /*
  per_res = check_region(piob->per, 1);

  if(per_res){
    printk("<1>buttons: cannot reserve piob->per\n"); 
    driver_exit();
    return per_res;
  }
  */

  request_region(piob, pioc-piob, DEVICE_NAME);
  /*
  piob->per = 0xffffffff;
  piob->oer = 0xfffffff00;
  piob->codr = 0xffffff00;
  piob->puer = 0x000000ff;*/

  piob->per = 0xffffffff;
  piob->oer = 0x000000ff;
  piob->codr = 0x000000ff;
  piob->puer = 0xffffff00;

  


  return 0;
}
/*****************************************************************************/
/* exit-funksjon (kalles når modul fjernes fra systemet) */

static void __exit driver_exit (void) {
   /* Freeing the major number */
  unregister_chrdev(major, "STK1000_LEDBUTTON_DRIVER");

  /* Freeing buffer memory */

  
  if (button_buffer) {
    kfree(button_buffer);
  }

  if (led_buffer) {
    kfree(led_buffer);
  }
  

/*
  // buttons
  if(!per_res){
    release_region(piob->per,1);
  }
  if(!puer_res){
    release_region(piob->puer,1);
  }
  if(!ier_res){
    release_region(piob->ier,1);
  }

  //leds 
  if(!perLED_res){
    release_region(pioc->per,1);
  }
  if(!oer_res){
    release_region(pioc->oer,1);
  }
  */

  printk("<1> driver_exit\n");
  
}

/*****************************************************************************/
/* fops-funksjoner */

static int driver_open (struct inode *inode, struct file *filp) {
  
  printk("<1> driver_open\n");
  return 0;   /* Success */
}

/*---------------------------------------------------------------------------*/

static int driver_release (struct inode *inode, struct file *filp) {
  printk("<1> driver_release\n");
  return 0; /* Success */
}

/*---------------------------------------------------------------------------*/

static ssize_t driver_read (struct file *filp, char __user *buff,
              size_t count, loff_t *offp) {
  printk("<1> driver_read\n");
  
  /* Transfering data to user space */ 
//  copy_to_user(buff,memory_buffer,1);


  /*
  //Limits to only first 8 bits from IOB
  int buttons_pressed = ((int)piob->isr)%256;
  buttons_pressed = buttons_pressed & ~(((int)piob->pdsr)%256);
  memset(button_buffer, (char) button_pressed, 1);
  copy_to_user(buff,button_buffer,1);
  */
/*
  printk("<1> driver_read\n");
  if(count > 1){
    count = 1;
    printk("<1> This driver transfers maximum one byte\n");
  }*/
  //char buttons = piob->pdsr
  //copy_to_user(piob->pdsr,buff,1);




  /* Changing reading position. If one byte is read, 0 is returned to indicate
    that the end of file has been read (this driver only transfers one byte) */
  return 0;

}

/*---------------------------------------------------------------------------*/

static ssize_t driver_write (struct file *filp, const char __user *buff,
               size_t count, loff_t *offp) {

  printk("<1> driver_write\n");
  if(count > 1){
    count = 1;
    printk("<1> This driver transfers maximum one byte\n");
  }

  copy_from_user(led_buffer,buff,count);
  printk("<1> Value written %d\n",led_buffer);

  piob->codr = 0xffffffff;
  piob->sodr =  *led_buffer;//(char)(integer%256);
  

  return 1;
}

/*****************************************************************************/
/* modul-beskrivelsesmakroer */

module_init (driver_init);  /* angir hva som er init-funksjon */
module_exit (driver_exit);  /* angir hva som er exit-funksjon */

MODULE_LICENSE ("GPL");     /* programlisens for modulen */
MODULE_DESCRIPTION ("");    /* tekstlig beskrivelse */
MODULE_VERSION ("");        /* versjonsnummer */
MODULE_AUTHOR ("");         /* forfatter(e) */

