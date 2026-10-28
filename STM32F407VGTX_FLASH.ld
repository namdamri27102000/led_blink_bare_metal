ENTRY(Reset_Handler)

MEMORY {
	FLASH (rx): ORIGIN = 0x08000000, LENGTH = 1024K
	SRAM (rwx): ORIGIN = 0x20000000, LENGTH = 128K
	CCMRAM (rwx): ORIGIN = 0x10000000, LENGTH = 64K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM); /* use to specify the MSP in startup code*/

SECTIONS {
	.isr_vector_tb :
		{
		. = ALIGN(4);
		KEEP(*(.isr_vector_tb))
		. = ALIGN(4);
		} >FLASH
	.text :
		{
		. = ALIGN(4);
		*(.text)
		*(.text*)
		. = ALIGN(4);
		} >FLASH
	.rodata :
		{
		. = ALIGN(4);
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
		_erodata = .;
		} >FLASH
	.data :
		{
		. = ALIGN(4);
		_sdata = .;
		*(.data)
		*(.data*)
		*(.RamFunc)
		*(.RamFunc*)
		. = ALIGN(4);
		_edata = .;
		} >SRAM AT> FLASH
	.bss :
		{
		. = ALIGN(4);
		_sbss = .;
		*(.bss)
		*(.bss*)
		. = ALIGN(4);
		_ebss = .;
		} >SRAM
}


