/* Entry Point */
ENTRY(Reset_Handler)

/* Specify the memory areas */
MEMORY
{
  RAM    (xrw)     : ORIGIN = 0x20000000,  LENGTH = 128K
  FLASH  (rx)      : ORIGIN = 0x08000000,  LENGTH = 512K
}

/* Heap and Stack Sizes */
_size_of_stack = 0x200;                         /* Size of stack in bytes */
_size_of_heap  = 0x0;                           /* Size of heap in bytes */

/* Highest usable address of the RAM. */
_end_of_ram = ORIGIN(RAM) + LENGTH(RAM) - 4;    /* End of RAM */


/* Define output sections */
SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data goes into FLASH */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH
  
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH
  
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM AT> FLASH


  /* Uninitialized data section */
  .bss :
  {
  	. = ALIGN(4);
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM

  .heap :
  {
  	. = ALIGN(4);
    _start_of_heap = .;
    . += _size_of_heap;

    . = ALIGN(4);
     _end_of_heap = .;
  } >RAM

  .stack :
  {
  	. = ABSOLUTE(_end_of_ram) - _size_of_stack;
  	. = ALIGN(8);  
      
     _top_of_stack = .;

    . += _size_of_stack;

    . = ALIGN(8);

    /*
      The SP needs to be aligned on 8-Byte boundary. With the following definition,
      the initial stack pointer meets that requirement but is outside of the valid RAM
      range. (eg. it has the address 0x20020000). But due to the fact that the stack is
      "full descending", the push operation first decrements the SP pointer, and then
      writes the data
    */
    _initial_stack_pointer = .;
    
    /*
      The first accessable valid address of the stack is the initial stack pointer - 4
    */
    _bottom_of_stack = _initial_stack_pointer - 4;
  } >RAM
}
