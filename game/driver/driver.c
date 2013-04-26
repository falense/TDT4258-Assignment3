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

/* Buffer to store data */
char *led_buffer;


/*****************************************************************************/
/* init-funksjon (kalles når modul lastes) */


#define DEVICE_NAME "STK1000_LEDBUTTON_DRIVER"

volatile avr32_pio_t *piob = &AVR32_PIOB;
volatile avr32_pio_t *pioc = &AVR32_PIOC;

struct cdev *driver;

static int __init driver_init (void) {

  /* allokere device-nummer */
  major = 252;
  int result;
  result = register_chrdev(major, DEVICE_NAME, &driver_fops);
  if (result < 0) {
    printk("<1>memory: cannot obtain major number %d\n", major);
    return result;
  }

  
  led_buffer = kmalloc(1, GFP_KERNEL); 
  if (!led_buffer) { 
    driver_exit(); 
    return -ENOMEM;
  } 
  memset(led_buffer, 0, 1);

  request_region(piob, pioc-piob, DEVICE_NAME);
  
  piob->per = 0xffffffff;   //enable the registers
  piob->oer = 0xffffff00;   //set the output registers
  piob->codr = 0xffffff00; // clear output data registers on every pin execpt the 8 first (buttons)
  piob->puer = 0x000000ff; //enable pullup-resistors for the 8 first pins

  return 0;
}
/*****************************************************************************/
/* exit-funksjon (kalles når modul fjernes fra systemet) */

static void __exit driver_exit (void) {
   /* Freeing the major number */
  unregister_chrdev(major, "STK1000_LEDBUTTON_DRIVER");

  /* Freeing buffer memory */

  if (led_buffer) {
    kfree(led_buffer);
  }
  
  
}

/*****************************************************************************/
/* fops-funksjoner */

static int driver_open (struct inode *inode, struct file *filp) {
  
  return 0;   /* Success */
}

/*---------------------------------------------------------------------------*/

static int driver_release (struct inode *inode, struct file *filp) {

  return 0; /* Success */
}

/*---------------------------------------------------------------------------*/

static ssize_t driver_read (struct file *filp, char __user *buff,
              size_t count, loff_t *offp) {

  char buttons = piob->pdsr;
  buttons = ~buttons;
  copy_to_user(buff,&buttons,1);
  
  return 1;

}

/*---------------------------------------------------------------------------*/

static ssize_t driver_write (struct file *filp, const char __user *buff,
               size_t count, loff_t *offp) {


  copy_from_user(led_buffer,buff,1);

  piob->codr = 0xffffff00; // clear output data registers on every pin execpt the 8 first (buttons)
  unsigned int ledmapping = 0;
  char usrled = led_buffer[0];

  /*
  This code translate between two representations for LED patterns. As input to this translation we have usrled,
  which is copied from the user. As output we have ledmapping which is set on the LEDs using the statement piob->sodr. 
  */
  //Led 0
  if ((usrled & 0x01) > 0){
    ledmapping = ledmapping | 0x00000100;
  }
  //Led 1
  if ((usrled & 0x02) > 0){
    ledmapping = ledmapping | 0x00000200;
  }
  //Led 2
  if ((usrled & 0x04) > 0){
    ledmapping = ledmapping | 0x00000400;
  }
  //Led 3
  if ((usrled & 0x08) > 0){
    ledmapping = ledmapping | 0x00002000;
  }
  //Led 4
  if ((usrled & 0x10) > 0){
    ledmapping = ledmapping | 0x00004000;
  }
  //Led 5
  if ((usrled & 0x20) > 0){
    ledmapping = ledmapping | 0x00008000;
  }
  //Led 6
  if ((usrled & 0x40) > 0){
    ledmapping = ledmapping | 0x00010000;
  }
  //Led 7
  if ((usrled & 0x80) > 0){
    ledmapping = ledmapping | 0x40000000;
  }

  piob->sodr = ledmapping;
  

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

