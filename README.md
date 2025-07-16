# 🧠 BasicFreeRTOS

Inspired by the [Build Your Own Real-Time OS (RTOS) From Ground Up™ on ARM 1 & 2](https://www.udemy.com/course/rtos-building-from-ground-up-on-arm-processors/) course, I decided to dive deeper by rebuilding the core concepts of FreeRTOS from scratch.

This project reimplements essential FreeRTOS features, based on its logic but with my own implementation.

---

## 📁 Project Structure

BasicRTOS/
├── inc/
├── src/
├── stmf411re/
├── tests/
├── .github/workflows/
├── .gitignore
├── CMakeLists.txt
└── README.md

---

## 🚀 Objectives

- [x] Implementation of the linked list  
- [x] Implementation of the heap  
- [ ] Add tests for linked list and heap
- [ ] Integration of FreeRTOS context switching code (PendSV-based) into my implementation for ARM Cortex-M4 (GCC toolchain)
- [ ] Implement tasks with preemptive scheduling logic, including task delay and priority management
- [ ] Testing on STM32F411RE
- [ ] Add CI/CD pipeline
- [ ] Add mutexes and semaphores