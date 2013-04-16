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
int major = 252;
/* Buffer to store data */
char *memory_buffer;


/*****************************************************************************/
/* init-funksjon (kalles når modul lastes) */


volatile avr32_pio_t *piob = &AVR32_PIOB;
volatile avr32_pio_t *pioc = &AVR32_PIOC;


void button_isr(void) {

}
static int __init driver_init (void) {
  
  printk("<1> driver_init\n");
/* allokere device-nummer */
  /* Registering device */
  int result = register_chrdev(major, "STK1000_LEDBUTTON_DRIVER", &driver_fops);
  if (result < 0) {
    printk("<1>memory: cannot obtain major number %d\n", major);
    return result;
  }

  /* Allocating memory for the buffer */
  memory_buffer = kmalloc(1, GFP_KERNEL); 
  if (!memory_buffer) { 
    result = -ENOMEM;
    memory_exit(); 
    return result;
  } 
  memset(memory_buffer, 0, 1);

  /* be om tilgang til I/O-porter */


  /*
 dev_t dev;

  int r =alloc_chrdev_region(&dev, 0,16,"STK1000_LEDBUTTON_DRIVER");
  printk(KERN_INFO "device id: %d",r);
  int piob_check = check_region((int)&AVR32_PIOB,1);
  int pioc_check = check_region((int)&AVR32_PIOC,1);
  if (piob_check && pioc_check){
  	printk(KERN_INFO "Diddnt get the regions we wanted.");
  }

else{

 request_region((int)&AVR32_PIOB,1,"STK1000_LEDBUTTON_DRIVER");
 request_region((int)&AVR32_PIOC,1,"STK1000_LEDBUTTON_DRIVER");
}
*/
  
	

  /* initialisere PIO-maskinvaren (som i øving 2) */
	 //Setup buttons
	//register_interrupt( button_isr, AVR32_PIOB_IRQ/32, AVR32_PIOB_IRQ % 32, BUTTONS_INT_LEVEL);
	piob->per = 0xff;
	piob->puer= 0xff;
	piob->ier = 0xff;
	//Setup leds
	pioc->per = 0xff;
	pioc->oer = 0xff;
  /* registrere device i systemet (må gjøres når alt annet er initialisert) */

  return 0;
}
/*****************************************************************************/
/* exit-funksjon (kalles når modul fjernes fra systemet) */

static void __exit driver_exit (void) {
   /* Freeing the major number */
  unregister_chrdev(major, "STK1000_LEDBUTTON_DRIVER");

  /* Freeing buffer memory */
  if (memory_buffer) {
    kfree(memory_buffer);
  }

  printk("<1> driver_exit\n");
  
}

/*****************************************************************************/
/* fops-funksjoner */

static int driver_open (struct inode *inode, struct file *filp) {
  
  return 0;
}

/*---------------------------------------------------------------------------*/

static int driver_release (struct inode *inode, struct file *filp) {
  return 0;
}

/*---------------------------------------------------------------------------*/

static ssize_t driver_read (struct file *filp, char __user *buff,
              size_t count, loff_t *offp) {
  printk("<1> driver_read\n");
  /* Transfering data to user space */ 
  copy_to_user(buf,memory_buffer,1);

  /* Changing reading position as best suits */ 
  if (*f_pos == 0) { 
    *f_pos+=1; 
    return 1; 
  } else { 
    return 0; 
  }
/*
//Limits to only first 8 bits from IOB
  int button = ((int)piob->isr)%256;
  button = button & ~(((int)piob->pdsr)%256);
  */
  return 0;

}

/*---------------------------------------------------------------------------*/

static ssize_t driver_write (struct file *filp, const char __user *buff,
               size_t count, loff_t *offp) {
  return 0;
}

/*****************************************************************************/
/* modul-beskrivelsesmakroer */

module_init (driver_init);  /* angir hva som er init-funksjon */
module_exit (driver_exit);  /* angir hva som er exit-funksjon */

MODULE_LICENSE ("GPL");     /* programlisens for modulen */
MODULE_DESCRIPTION ("");    /* tekstlig beskrivelse */
MODULE_VERSION ("");        /* versjonsnummer */
MODULE_AUTHOR ("");         /* forfatter(e) */

