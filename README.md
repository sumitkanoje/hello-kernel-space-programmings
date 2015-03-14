Kernel Space Programming
---

####Problem Statement:
Implement and add a loadable kernel module to Linux kernel, demonstrate using insmod, lsmod and rmmod commands. A sample kernel space program should print the "Hello World" while loading the kernel module and "Goodbye World" while unloading the kernel module.

####Objectives:

To study kernel space programming steps and commands like insmod, lsmod and rmmod

####Theory: 

######What is a loadable kernel module?

To add a new code to a Linux kernel, it is necessary to add some source files to kernel source tree and recompile the kernel. You can also add code to the Linux kernel while it is running. A chunk of code added in such way is called a loadable kernel module. 

######Typical modules:

Device drivers, File system drivers , System calls

######Advantages of modules

* There is no necessity to rebuild the kernel, when a new kernel option is added.

2. Modules help find system problems (if system problem caused a module just don't load it).

3. Modules are much faster to maintain and debug.

4. Modules once loaded are in as much fast as kernel.

######Module Implementation

* Modules are stored in the file system as ELF object files.
* The kernel makes sure that the rest of the kernel can reach the module's global symbols.
* Module must know the addresses of symbols (variables and functions) in the kernel and in other modules (/proc/kallsyms).
* The kernel keeps track of the use of modules, so that no modules is unloaded while another module or kernel is using it (/proc/modules)
* The kernel considers only modules that have been loaded into RAM by the insmod program and for each of them allocates memory area containing: a module object
* null terminated string that represents module's name
* the code that implements the functions of the module

######Module Object

####Programs for linking and unlinking

####1) insmod 

* inserts the module into the kernel space.

* Reads from the name of the module to be linked

* Locates the file containing the module's object code

* Computes the size of the memory area needed to store the module code, its name, and the module object.

* Invokes the create_module( ) system call

####2) Insmod

* Invokes the query_module( ) system call Using the kernel symbol table, the module symbol tables, and the address returned by the create_module( ) system call, relocates the object code included in the module's file.

* Allocates a memory area in the User Mode address space and loads with a copy of the module object.

* Invokes the init_module( ) system call, passing to it the address of the User Mode memory area.

* Releases the User Mode memory area and terminates

####3) lsmod

* reads /proc/modules and displays on the terminal.

####4) Rmmod

* reads the name of the module to be unlinked.

* Invokes the query_module( )

* Invokes the delete_module( ) system call

####5) modprobe

* takes care of possible complications due to module dependencies, uses depmod program and /etc/modules.conf file Compiling kernel module

* A kernel module is not an independent executable, but an object file which will be linked into the kernel in runtime and they should be compiled with

 -c flag

 _KERNEL_ symbol

 CONFIG_MODVERSIONS symbol

####Steps for the program compilation, linking, loading and executing

1. Edit a Hello.c program

2. Edit a makefile

3. The program and makefile should be kept in a single folder.

4. Change directory to this folder

5. Execute “ make” on terminal

6. Execute insmod Hello.ko from this folder.

7. Execute dmesg from a terminal to see the kernel buffer

8. contents (reads the kernel log file /var/log/syslog)

9. Execute lsmod from this folder.

10. Execute rmmod Hello.ko from this folder when done.

####Files created after building the module

* Hello.o - Module object file before linking

* Hello.mod.c - Contains module’s information

* Hello.mod.o - After compilation and linking of Hello.mod.c

* Modules.order - The order in which two or three modules get linked..

* Modules.symvers - Symbol versions if any.

* Hello.ko - A module kernel object file after linking Hello.o and

* Hello.mod.o - Hello.mod.c details

#####Hello.mod.c details

Include/linux/module.h , include/linux/vermagic.h, include/linux/kernel.h

* ####Step 1 –

	* Find all modules from the files listed in $(MODVERDIR)/ 

	* modpost is then used to create one <module>.mod.c file

	* Create one Module.symvers file with CRC for all exported symbols

	* Compile all <module>.mod.c files

	* Final link of the module to a <module.ko> file

* ####Step 2 - is used to place certain information in the module's ELF

	* Version magic (see include/linux/vermagic.h for full details)

	* Kernel release

	* GCC Version

	* Module info

	* Module version (MODULE_VERSION)

	* Module license (MODULE_LICENSE)

* ####Step 3 - is used to allow module versioning in external modules, where the CRC of each module is retrieved from the Module.symvers file.

###Module definition:

```
struct module __this_module

__attribute__((section(".gnu.linkonce.this_module")

)) = {

.name = KBUILD_MODNAME,

.init = init_module,

#ifdef CONFIG_MODULE_UNLOAD

.exit = cleanup_module,

#endif

.arch = MODULE_ARCH_INIT

}
```
###The symbol version definitions:

(nm – modules in the object file- nm hello.ko)
```
static const struct modversion_info ____versions[]

__used

__attribute__((section("__versions"))) =

{

{ 0x4d5503c4, "module_layout" },

{ 0xb4390f9a, "mcount" },

{ 0x50eedeb8, "printk" },

}; 
```
• /usr/src/linux-version-headers/Module.symvers

• This file contains the list of symbols that are exported

by kernel to loadable 07/01/15 kernel modules (LKM).

###Conclusion:

Loadable kernel module is implemented and added to Linux kernel using insmod, lsmod and rmmod commands.
