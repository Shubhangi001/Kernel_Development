# Kernel_Development
This GitHub repository contains codes that I wrote during my internship at Microsoft. The codes are related to kernels, device drivers, and tracepoints, and are intended to serve as a reference for anyone interested in learning low-level programming.

## Project Structure

- **Makefile**: Contains the compilation instructions for the kernel module.
- **first_kernel_module.c**: A sample kernel module printing hello world to the kernel logs.
- **misc_driver.c**: A kernel module that handles miscellaneous driver registration and implements the read, write, and ioctl operations..
- **test.c**: A sample user space test program to interact with the kernel module.
- **trace_header.h**: Header file defining tracepoints used in the module.

## Usage

1. Build and install the kernel source tree before proceeding to anything.
2. Compile the first_kernel_module using the provided Makefile by giving the command `make`


## References

- https://lwn.net/Kernel/LDD3/
- https://www.kernel.org/doc/html/latest/trace/
- https://www.kernel.org/doc/html/latest/trace/tracepoints.html
- https://veithen.io/2013/12/19/ubuntu-vanilla-kernel.html
- https://embetronicx.com/tutorials/linux/device-drivers/ioctl-tutorial-in-linux/
- https://www.kernel.org/doc/html/latest/process/development-process.html
- https://www.kernel.org/doc/html/latest/process/submitting-patches.html
