# Kernel_Development
This GitHub repository contains codes that I wrote during my internship at Microsoft. The codes are related to kernels, device drivers, and tracepoints, and are intended to serve as a reference for anyone interested in learning low-level programming.

## Project Structure

- **Makefile**: Contains the compilation instructions for the kernel module.
- **first_kernel_module.c**: A sample kernel module printing hello world to the kernel logs.
- **misc_driver.c**: A kernel module that handles miscellaneous driver registration and implements the read, write, and ioctl operations..
- **test.c**: A sample user space test program to interact with the kernel module.
- **trace_header.h**: Header file defining tracepoints used in the module.

## Instructions

1. Build and install the kernel source tree before proceeding to anything.
2. Compile the first_kernel_module using the provided Makefile by giving the command `make`
    - The path for the kernel source directory should be changed accordingly. For example in the given Makefile, the kernel repository is cloned in this path: `~/linux`
    - The module can also be compiled using the command : ``make -C ~/linux M=`pwd` modules`` where "~/linux" should be replaced by path of the linux kernel repo.
3. Load the kernel module using the command: `sudo insmod first_kernel_module.ko`
    - .ko represents a kernel object and this file is created when we compile the kernel module as a loadable kernel module which is specified in the 
    - Note that a kernel module should only be loaded into a kernel that has been installed with the same configuration as the one used during compilation.
4. Unload the kernel module using the command: `sudo rmmod first_kernel_module.ko` 
5. Run the command `sudo dmesg` to check the kernel logs. (It can also be checked in /var/log/messages file)

## References

- https://lwn.net/Kernel/LDD3/
- https://www.kernel.org/doc/html/latest/trace/
- https://www.kernel.org/doc/html/latest/trace/tracepoints.html
- https://veithen.io/2013/12/19/ubuntu-vanilla-kernel.html
- https://embetronicx.com/tutorials/linux/device-drivers/ioctl-tutorial-in-linux/
- https://www.kernel.org/doc/html/latest/process/development-process.html
- https://www.kernel.org/doc/html/latest/process/submitting-patches.html
