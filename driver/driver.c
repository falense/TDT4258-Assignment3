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
int major;

/* Buffer to store data */
char *memory_buffer;
//char *button_buffer;
//char *led_buffer;


/*****************************************************************************/
/* init-funksjon (kalles når modul lastes) */


volatile avr32_pio_t *piob = &AVR32_PIOB;
volatile avr32_pio_t *pioc = &AVR32_PIOC;


void button_isr(void) {

}
static int __init driver_init (void) {
  
  printk("<1> driver_init\n");
  /* allokere device-nummer */
  major = 252;

  /* Allocating memory for the buffer */
  memory_buffer = kmalloc(1, GFP_KERNEL); 
  if (!memory_buffer) { 
    result = -ENOMEM;
    driver_exit(); 
    return result;
  } 
  memset(memory_buffer, 0, 1);

  /*
  button_buffer = kmalloc(1, GFP_KERNEL); 
  if (!button_buffer) { 
    result = -ENOMEM;
    driver_exit(); 
    return result;
  } 
  memset(button_buffer, 0, 1);
  
  led_buffer = kmalloc(1, GFP_KERNEL); 
  if (!led_buffer) { 
    result = -ENOMEM;
    driver_exit(); 
    return result;
  } 
  memset(led_buffer, 0, 1);
  */


  /* be om tilgang til I/O-porter */

  /* buttons */
  per_res = check_region(piob->per, 1);
  puer_res = check_region(piob->puer, 1);
  ier_res = check_region(piob->ier, 1);

  if(per_res){
    printk("<1>buttons: cannot reserve piob->per\n"); 
    driver_exit();
    return per_res;
  }
  if(puer_res){
    printk("<1>buttons: cannot reserve piob->puer\n"); 
    driver_exit();
    return puer_res;
  }
  if(ier_res){
    printk("<1>buttons: cannot reserve piob->ier\n"); 
    driver_exit();
    return ier_res;
  }

  request_region(piob->per, 1, "STK1000_LEDBUTTON_DRIVER");
  request_region(piob->puer, 1, "STK1000_LEDBUTTON_DRIVER");
  request_region(piob->ier, 1, "STK1000_LEDBUTTON_DRIVER");

  /* leds */
  perLED_res = check_region(pioc->per, 1);
  oer_res = check_region(pioc->oer, 1);

  if(perLED_res){
    printk("<1>leds: cannot reserve pioc->per\n"); 
    driver_exit();
    return perLED_res;
  }
  if(oer_res){
    printk("<1>leds: cannot reserve pioc->oer\n"); 
    driver_exit();
    return oer_res;
  }

  request_region(pioc->per, 1, "STK1000_LEDBUTTON_DRIVER");
  request_region(pioc->oer, 1, "STK1000_LEDBUTTON_DRIVER");

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
  int result = register_chrdev(major, "STK1000_LEDBUTTON_DRIVER", &driver_fops);
  if (result < 0) {
    printk("<1>memory: cannot obtain major number %d\n", major);
    return result;
  }

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

  /*
  if (button_buffer) {
    kfree(button_buffer);
  }

  if (led_buffer) {
    kfree(led_buffer);
  }
  */

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

  /* leds */
  if(!perLED_res){
    release_region(pioc->per,1);
  }
  if(!oer_res){
    release_region(pioc->oer,1);
  }


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
  copy_to_user(buff,memory_buffer,1);


  /*
  //Limits to only first 8 bits from IOB
  int buttons_pressed = ((int)piob->isr)%256;
  buttons_pressed = buttons_pressed & ~(((int)piob->pdsr)%256);
  memset(button_buffer, (char) button_pressed, 1);
  copy_to_user(buff,button_buffer,1);
  */


  /* Changing reading position. If one byte is read, 0 is returned to indicate
    that the end of file has been read (this driver only transfers one byte) */
  if (*f_pos == 0) { 
    *f_pos+=1; 
    return 1; 
  } 
  else { 
    return 0; 
  }

}

/*---------------------------------------------------------------------------*/

static ssize_t driver_write (struct file *filp, const char __user *buff,
               size_t count, loff_t *offp) {

  printk("<1> driver_write\n");
  if(count > 1){
    count = 1;
    printk("<1> This driver transfers maximum one byte\n");
  }

  copy_from_user(memory_buffer,buff,count);

  /*
  //copy_from_user(led_buffer,buff,count);
  pioc->sodr = led_buffer;   //Turn on the leds 
  pioc->codr = ~led_buffer; //Turns of the rest, hence the negation.
  */
  return 1;
  

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

