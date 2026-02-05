# Memory Allocation Visualizer

A text-based interactive simulator demonstrating dynamic contiguous memory allocation algorithms in Operating Systems.

## 🎯 Overview

The Memory Allocation Visualizer is an Operating Systems–oriented project that simulates how memory is allocated and managed using dynamic partitioning.
It helps users understand how different allocation strategies affect memory utilization, fragmentation, and allocation success.

This project focuses on concept clarity, correctness, and explainability.

## 🎯 Objectives

- Simulate dynamic memory allocation in operating systems
- Implement and compare:
  - First Fit
  - Best Fit
  - Worst Fit algorithms
- Demonstrate external fragmentation
- Visualize memory layout in a clear, textual form
- Provide an interactive environment for experimentation

## ✨ Features

- ✅ **Three Allocation Algorithms:**
  - First Fit
  - Best Fit
  - Worst Fit

- ✅ **Interactive Operations:**
  - Allocate memory to processes
  - Deallocate processes with hole merging
  - Display current memory layout
  - Calculate external fragmentation
  - Compare algorithms under identical conditions
  - Reset memory state

- ✅ **Visual Feedback:**
  - Text-based memory visualization
  - ASCII art representation
  - Detailed statistics (free memory, holes, utilization)

## 🛠️ Technical Specifications

### Technologies Used
- **Language:** C
- **Compiler:** GCC (GNU Compiler Collection)
- **Platform:** Cross-platform (Mac, Linux, Windows)
- **Architecture:** Modular design with header files

### Project Structure
```
MemoryAllocationVisualizer/
├── include/
│   ├── memory_structures.h    # Data structure definitions
│   └── memory_manager.h       # Function declarations
├── src/
│   ├── memory_structures.c    # Structure implementations
│   ├── memory_manager.c       # Algorithm implementations
│   └── main.c                 # Main program
├── build/
│   └── memory_visualizer      # Compiled executable
├── docs/
│   └── project_report.pdf     # Documentation
└── README.md                  # This file
```

## 📦 Installation & Compilation

### Prerequisites
- GCC compiler installed
- Terminal/Command Line access

### Compilation Steps

1. **Clone the project:**
```bash
cd /path/to/MemoryAllocationVisualizer
```

2. **Compile the project:**
```bash
gcc -o build/memory_visualizer src/main.c src/memory_manager.c src/memory_structures.c -I include
```

3. **Run the program:**
```bash
./build/memory_visualizer
```

### Alternative Compilation (Windows)
```cmd
gcc -o build\memory_visualizer.exe src\main.c src\memory_manager.c src\memory_structures.c -I include
build\memory_visualizer.exe
```

## 🎮 How to Use

### Main Menu Options

1. **Allocate Memory (First Fit)** - Uses first suitable hole
2. **Allocate Memory (Best Fit)** - Uses smallest suitable hole
3. **Allocate Memory (Worst Fit)** - Uses largest hole
4. **Deallocate Process** - Free memory and merge holes
5. **Display Memory State** - Show current memory layout
6. **Show Fragmentation Analysis** - Calculate fragmentation percentage
7. **Compare All Algorithms** - Run all algorithms with test data
8. **Reset Memory** - Clear all processes and restart
9. **Exit** - Quit the program

### Example Usage
```
Enter choice: 1
Enter process size (KB): 200
✓ Process P1 (200 KB) allocated at address 256

Memory: [OS][P1][==========]
```

## 🧮 Algorithms Implemented

### 1. First Fit Algorithm
- **Strategy:** Allocate to first hole that fits
- **Advantage:** Fastest
- **Disadvantage:** Can cause fragmentation near the beginning of memory

### 2. Best Fit Algorithm
- **Strategy:** Allocate to smallest hole that fits
- **Advantage:** Minimizes wasted space
- **Disadvantage:** Creates many tiny unusable holes

### 3. Worst Fit Algorithm
- **Strategy:** Allocate to largest available hole
- **Advantage:** Leaves larger reusable holes
- **Disadvantage:** Wastes largest holes first

## 📊 Key Concepts Demonstrated

### Dynamic Partitioning
Memory is allocated in variable-sized blocks based on process requirements.

### External Fragmentation
Free memory scattered in small non-contiguous blocks that cannot be effectively used.

**Formula:**
```
Fragmentation % = (Total Free Memory - Largest Hole) / User Memory × 100
```

### Hole Merging
When adjacent holes are merged into one larger hole during deallocation to prevent fragmentation.

## 🐛 Known Issues

- Comparison mode uses simple workloads (single-hole scenarios)
- Input validation can be further strengthened
- Maximum memory size is fixed at 1024 KB (can be modified in code)

## 🔮 Future Enhancements (Phase 2)

- [ ] Graphical UI (Web or Desktop)
- [ ] Step-by-step animated allocation
- [ ] Compaction support
- [ ] Fragmentation graphs over time
- [ ] Realistic workload simulation
- [ ] Export results (CSV / JSON)
- [ ] Paging and segmentation support