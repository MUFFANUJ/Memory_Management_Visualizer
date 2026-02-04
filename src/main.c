/*
================================================================================
FILE: main.c
PURPOSE: Main program - Text-based memory allocation visualizer
DESCRIPTION: 
    - Interactive menu system
    - Demonstrates First Fit, Best Fit, Worst Fit algorithms
    - Text-based visualization (works on all systems)
    - Complete memory management simulation
================================================================================
*/

// Include necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/memory_manager.h"

/*
================================================================================
FUNCTION: printMenu
================================================================================
PURPOSE: Display the main menu to the user

CREATES A NICE-LOOKING MENU:
╔════════════════════════════════════════╗
║  MEMORY ALLOCATION VISUALIZER          ║
╠════════════════════════════════════════╣
║  1. Allocate Memory (First Fit)        ║
║  2. Allocate Memory (Best Fit)         ║
... etc ...
*/

void printMenu() {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║  MEMORY ALLOCATION VISUALIZER          ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║  1. Allocate Memory (First Fit)        ║\n");
    printf("║  2. Allocate Memory (Best Fit)         ║\n");
    printf("║  3. Allocate Memory (Worst Fit)        ║\n");
    printf("║  4. Deallocate Process                 ║\n");
    printf("║  5. Display Memory State               ║\n");
    printf("║  6. Show Fragmentation Analysis        ║\n");
    printf("║  7. Compare All Algorithms             ║\n");
    printf("║  8. Reset Memory                       ║\n");
    printf("║  9. Exit                               ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("Enter choice: ");
}


/*
================================================================================
FUNCTION: printWelcome
================================================================================
PURPOSE: Display welcome banner when program starts
*/

void printWelcome() {
    printf("\n\n");
    printf("╔═══════════════════════════════════════════════╗\n");
    printf("║                                               ║\n");
    printf("║    MEMORY ALLOCATION VISUALIZER               ║\n");
    printf("║    Dynamic Partitioning Simulator            ║\n");
    printf("║                                               ║\n");
    printf("║    Demonstrates:                              ║\n");
    printf("║    • First Fit Algorithm                      ║\n");
    printf("║    • Best Fit Algorithm                       ║\n");
    printf("║    • Worst Fit Algorithm                      ║\n");
    printf("║    • External Fragmentation                   ║\n");
    printf("║                                               ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
    printf("\n");
}


/*
================================================================================
FUNCTION: drawMemoryVisualization
================================================================================
PURPOSE: Create a visual ASCII representation of memory

EXAMPLE OUTPUT:
Memory Visualization:
[OS ][P1 ][==][P2      ][====]
0   256 356 456      656  1023

Legend: [Process] [==Hole==]
*/

void drawMemoryVisualization(MemoryManager *mm) {
    
    printf("\n");
    printf("┌─────────────────────────────────────────────────────────┐\n");
    printf("│              MEMORY VISUALIZATION                       │\n");
    printf("└─────────────────────────────────────────────────────────┘\n");
    
    // Print memory blocks as ASCII bar
    printf("Memory: ");
    
    // Print OS
    printf("[OS]");
    
    // Print user memory blocks
    MemoryBlock *current = mm->head;
    while (current != NULL) {
        if (current->isHole) {
            // Print hole
            // Size determines how many = signs
            int numSigns = (current->size / 50) + 1;  // 1 sign per 50KB
            if (numSigns > 10) numSigns = 10;  // Max 10 signs
            
            printf("[");
            for (int i = 0; i < numSigns; i++) {
                printf("=");
            }
            printf("]");
        } else {
            // Print process
            printf("[P%d]", current->processID);
        }
        current = current->next;
    }
    printf("\n");
    
    // Print legend
    printf("\nLegend: [Pn]=Process  [==]=Hole(Free Space)\n");
}


/*
================================================================================
FUNCTION: compareAlgorithms
================================================================================
PURPOSE: Run all three algorithms with same test data and compare results

WHAT IT DOES:
1. Creates identical test scenarios
2. Runs First Fit, Best Fit, Worst Fit
3. Shows fragmentation for each
4. Displays comparison table
*/

void compareAlgorithms(MemoryManager *mm) {
    
    printf("\n");
    printf("╔═══════════════════════════════════════════════╗\n");
    printf("║        ALGORITHM COMPARISON TEST              ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
    printf("\nThis will test all algorithms with identical input.\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();  // Clear input buffer
    
    // Test scenario: 5 processes of different sizes
    int testSizes[] = {100, 200, 150, 50, 300};
    int numTests = 5;
    
    printf("\nTest Scenario:\n");
    printf("Allocating 5 processes: 100KB, 200KB, 150KB, 50KB, 300KB\n");
    printf("\n");
    
    // ============ TEST 1: FIRST FIT ============
    printf("═══════════════════════════════════════════════\n");
    printf("        TEST 1: FIRST FIT ALGORITHM\n");
    printf("═══════════════════════════════════════════════\n");
    
    MemoryManager mm1;
    initializeMemory(&mm1, 1024, 256);
    
    for (int i = 0; i < numTests; i++) {
        int result = allocateMemory(&mm1, i + 1, testSizes[i], FIRST_FIT);
        if (result != -1) {
            printf("✓ Process P%d (%d KB) allocated at address %d\n", 
                   i + 1, testSizes[i], result);
        } else {
            printf("✗ Process P%d (%d KB) allocation FAILED\n", 
                   i + 1, testSizes[i]);
        }
    }
    
    displayMemory(&mm1);
    drawMemoryVisualization(&mm1);
    float frag1 = calculateFragmentation(&mm1);
    printf("\nFirst Fit Fragmentation: %.2f%%\n", frag1);
    
    printf("\nPress Enter to continue to Best Fit test...");
    getchar();
    
    
    // ============ TEST 2: BEST FIT ============
    printf("\n\n═══════════════════════════════════════════════\n");
    printf("        TEST 2: BEST FIT ALGORITHM\n");
    printf("═══════════════════════════════════════════════\n");
    
    MemoryManager mm2;
    initializeMemory(&mm2, 1024, 256);
    
    for (int i = 0; i < numTests; i++) {
        int result = allocateMemory(&mm2, i + 1, testSizes[i], BEST_FIT);
        if (result != -1) {
            printf("✓ Process P%d (%d KB) allocated at address %d\n", 
                   i + 1, testSizes[i], result);
        } else {
            printf("✗ Process P%d (%d KB) allocation FAILED\n", 
                   i + 1, testSizes[i]);
        }
    }
    
    displayMemory(&mm2);
    drawMemoryVisualization(&mm2);
    float frag2 = calculateFragmentation(&mm2);
    printf("\nBest Fit Fragmentation: %.2f%%\n", frag2);
    
    printf("\nPress Enter to continue to Worst Fit test...");
    getchar();
    
    
    // ============ TEST 3: WORST FIT ============
    printf("\n\n═══════════════════════════════════════════════\n");
    printf("        TEST 3: WORST FIT ALGORITHM\n");
    printf("═══════════════════════════════════════════════\n");
    
    MemoryManager mm3;
    initializeMemory(&mm3, 1024, 256);
    
    for (int i = 0; i < numTests; i++) {
        int result = allocateMemory(&mm3, i + 1, testSizes[i], WORST_FIT);
        if (result != -1) {
            printf("✓ Process P%d (%d KB) allocated at address %d\n", 
                   i + 1, testSizes[i], result);
        } else {
            printf("✗ Process P%d (%d KB) allocation FAILED\n", 
                   i + 1, testSizes[i]);
        }
    }
    
    displayMemory(&mm3);
    drawMemoryVisualization(&mm3);
    float frag3 = calculateFragmentation(&mm3);
    printf("\nWorst Fit Fragmentation: %.2f%%\n", frag3);
    
    
    // ============ COMPARISON SUMMARY ============
    printf("\n\n");
    printf("╔═══════════════════════════════════════════════╗\n");
    printf("║          COMPARISON SUMMARY                   ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
    printf("\n");
    printf("┌──────────────┬────────────────┬────────────┐\n");
    printf("│  Algorithm   │  Fragmentation │   Speed    │\n");
    printf("├──────────────┼────────────────┼────────────┤\n");
    printf("│  First Fit   │     %.2f%%     │   Fastest  │\n", frag1);
    printf("│  Best Fit    │     %.2f%%     │   Slowest  │\n", frag2);
    printf("│  Worst Fit   │     %.2f%%     │   Slow     │\n", frag3);
    printf("└──────────────┴────────────────┴────────────┘\n");
    
    // Analysis
    printf("\nAnalysis:\n");
    if (frag1 < frag2 && frag1 < frag3) {
        printf("• First Fit had the LEAST fragmentation for this workload\n");
    } else if (frag2 < frag1 && frag2 < frag3) {
        printf("• Best Fit had the LEAST fragmentation for this workload\n");
    } else if (frag3 < frag1 && frag3 < frag2) {
        printf("• Worst Fit had the LEAST fragmentation for this workload\n");
    }
    
    printf("• First Fit is fastest (stops at first match)\n");
    printf("• Best Fit and Worst Fit are slower (check all holes)\n");
    printf("• Results vary depending on process arrival patterns\n");
    
    // Cleanup
    freeMemoryManager(&mm1);
    freeMemoryManager(&mm2);
    freeMemoryManager(&mm3);
    
    printf("\nPress Enter to return to main menu...");
    getchar();
}


/*
================================================================================
FUNCTION: main
================================================================================
PURPOSE: Main program entry point

WHAT IT DOES:
1. Shows welcome message
2. Initializes memory
3. Shows menu in a loop
4. Processes user choices
5. Calls appropriate functions
6. Continues until user exits
*/

int main() {
    
    // Variables
    MemoryManager mm;           // Memory manager structure
    int choice;                 // User menu choice
    int processID;              // Process ID for allocation/deallocation
    int size;                   // Process size
    int result;                 // Result of operations
    int nextProcessID = 1;      // Next available process ID
    char algoName[20] = "NONE"; // Current algorithm name
    
    // Display welcome banner
    printWelcome();
    
    // Initialize memory
    // Total: 1024 KB, OS: 256 KB, User: 768 KB
    initializeMemory(&mm, 1024, 256);
    
    printf("Memory initialized successfully!\n");
    printf("Press Enter to start...");
    getchar();  // Wait for user to press Enter
    
    // Main program loop
    while (1) {
        
        // Display menu
        printMenu();
        
        // Get user choice
        if (scanf("%d", &choice) != 1) {
            // Invalid input (not a number)
            printf("Invalid input! Please enter a number.\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }
        
        // Process user choice
        switch (choice) {
            
            // ========== CASE 1: FIRST FIT ==========
            case 1:
                printf("\n--- FIRST FIT ALLOCATION ---\n");
                printf("Enter process size (KB): ");
                scanf("%d", &size);
                
                result = allocateMemory(&mm, nextProcessID, size, FIRST_FIT);
                
                if (result != -1) {
                    printf("\n✓ SUCCESS!\n");
                    printf("Process P%d (%d KB) allocated at address %d\n", 
                           nextProcessID, size, result);
                    printf("Algorithm: First Fit\n");
                    strcpy(algoName, "FIRST FIT");
                    nextProcessID++;
                    
                    // Show updated memory
                    displayMemory(&mm);
                    drawMemoryVisualization(&mm);
                } else {
                    printf("\n✗ ALLOCATION FAILED!\n");
                    printf("Not enough contiguous memory available.\n");
                    printf("Requested: %d KB, Free: %d KB\n", size, mm.freeMemory);
                }
                break;
            
            
            // ========== CASE 2: BEST FIT ==========
            case 2:
                printf("\n--- BEST FIT ALLOCATION ---\n");
                printf("Enter process size (KB): ");
                scanf("%d", &size);
                
                result = allocateMemory(&mm, nextProcessID, size, BEST_FIT);
                
                if (result != -1) {
                    printf("\n✓ SUCCESS!\n");
                    printf("Process P%d (%d KB) allocated at address %d\n", 
                           nextProcessID, size, result);
                    printf("Algorithm: Best Fit\n");
                    strcpy(algoName, "BEST FIT");
                    nextProcessID++;
                    
                    displayMemory(&mm);
                    drawMemoryVisualization(&mm);
                } else {
                    printf("\n✗ ALLOCATION FAILED!\n");
                    printf("Not enough contiguous memory available.\n");
                    printf("Requested: %d KB, Free: %d KB\n", size, mm.freeMemory);
                }
                break;
            
            
            // ========== CASE 3: WORST FIT ==========
            case 3:
                printf("\n--- WORST FIT ALLOCATION ---\n");
                printf("Enter process size (KB): ");
                scanf("%d", &size);
                
                result = allocateMemory(&mm, nextProcessID, size, WORST_FIT);
                
                if (result != -1) {
                    printf("\n✓ SUCCESS!\n");
                    printf("Process P%d (%d KB) allocated at address %d\n", 
                           nextProcessID, size, result);
                    printf("Algorithm: Worst Fit\n");
                    strcpy(algoName, "WORST FIT");
                    nextProcessID++;
                    
                    displayMemory(&mm);
                    drawMemoryVisualization(&mm);
                } else {
                    printf("\n✗ ALLOCATION FAILED!\n");
                    printf("Not enough contiguous memory available.\n");
                    printf("Requested: %d KB, Free: %d KB\n", size, mm.freeMemory);
                }
                break;
            
            
            // ========== CASE 4: DEALLOCATE ==========
            case 4:
                printf("\n--- DEALLOCATE PROCESS ---\n");
                
                // Show current processes
                printf("Current processes in memory:\n");
                MemoryBlock *current = mm.head;
                int hasProcesses = 0;
                while (current != NULL) {
                    if (!current->isHole) {
                        printf("  P%d (%d KB at address %d)\n", 
                               current->processID, current->size, 
                               current->startAddress);
                        hasProcesses = 1;
                    }
                    current = current->next;
                }
                
                if (!hasProcesses) {
                    printf("  No processes in memory.\n");
                    break;
                }
                
                printf("\nEnter process ID to deallocate: ");
                scanf("%d", &processID);
                
                result = deallocateMemory(&mm, processID);
                
                if (result) {
                    printf("\n✓ SUCCESS!\n");
                    printf("Process P%d has been deallocated\n", processID);
                    printf("Memory freed and holes merged (if adjacent)\n");
                    
                    displayMemory(&mm);
                    drawMemoryVisualization(&mm);
                } else {
                    printf("\n✗ DEALLOCATION FAILED!\n");
                    printf("Process P%d not found in memory.\n", processID);
                }
                break;
            
            
            // ========== CASE 5: DISPLAY MEMORY ==========
            case 5:
                printf("\n--- CURRENT MEMORY STATE ---\n");
                printf("Current Algorithm: %s\n", algoName);
                displayMemory(&mm);
                drawMemoryVisualization(&mm);
                break;
            
            
            // ========== CASE 6: FRAGMENTATION ==========
            case 6:
                {
                    float frag = calculateFragmentation(&mm);
                    
                    printf("\n");
                    printf("╔═══════════════════════════════════════╗\n");
                    printf("║    FRAGMENTATION ANALYSIS             ║\n");
                    printf("╚═══════════════════════════════════════╝\n");
                    printf("\n");
                    printf("External Fragmentation: %.2f%%\n", frag);
                    printf("Total Holes: %d\n", mm.numHoles);
                    printf("Total Free Memory: %d KB\n", mm.freeMemory);
                    printf("Used Memory: %d KB\n", mm.userMemory - mm.freeMemory);
                    printf("Memory Utilization: %.2f%%\n", 
                           ((float)(mm.userMemory - mm.freeMemory) / mm.userMemory) * 100);
                    
                    printf("\nWhat is fragmentation?\n");
                    printf("Fragmentation occurs when free memory is scattered\n");
                    printf("in small holes that cannot be used effectively.\n");
                    
                    if (frag < 10) {
                        printf("\n✓ Low fragmentation - Memory is well utilized\n");
                    } else if (frag < 30) {
                        printf("\n⚠ Moderate fragmentation - Some memory waste\n");
                    } else {
                        printf("\n✗ High fragmentation - Consider compaction\n");
                    }
                }
                break;
            
            
            // ========== CASE 7: COMPARE ALGORITHMS ==========
            case 7:
                compareAlgorithms(&mm);
                break;
            
            
            // ========== CASE 8: RESET MEMORY ==========
            case 8:
                printf("\n--- RESET MEMORY ---\n");
                printf("Are you sure? This will remove all processes. (y/n): ");
                char confirm;
                scanf(" %c", &confirm);
                
                if (confirm == 'y' || confirm == 'Y') {
                    freeMemoryManager(&mm);
                    initializeMemory(&mm, 1024, 256);
                    nextProcessID = 1;
                    strcpy(algoName, "NONE");
                    printf("\n✓ Memory reset successfully!\n");
                    displayMemory(&mm);
                } else {
                    printf("\nReset cancelled.\n");
                }
                break;
            
            
            // ========== CASE 9: EXIT ==========
            case 9:
                printf("\n");
                printf("╔═══════════════════════════════════════╗\n");
                printf("║  Thank you for using                  ║\n");
                printf("║  MEMORY ALLOCATION VISUALIZER         ║\n");
                printf("╚═══════════════════════════════════════╝\n");
                printf("\n");
                
                // Cleanup
                freeMemoryManager(&mm);
                
                printf("Goodbye!\n\n");
                return 0;
            
            
            // ========== DEFAULT: INVALID CHOICE ==========
            default:
                printf("\n✗ Invalid choice! Please enter 1-9.\n");
        }
        
        // Pause before showing menu again
        printf("\nPress Enter to continue...");
        getchar();  // Clear newline from previous input
        getchar();  // Wait for Enter
    }
    
    return 0;
}


/*
================================================================================
END OF FILE: main.c
================================================================================

WHAT WE IMPLEMENTED:
1. printMenu() - Display interactive menu
2. printWelcome() - Welcome banner
3. drawMemoryVisualization() - ASCII art memory representation
4. compareAlgorithms() - Test and compare all three algorithms
5. main() - Main program loop with full menu system

FEATURES:
✓ Interactive menu (9 options)
✓ All three allocation algorithms
✓ Deallocation with hole merging
✓ Memory visualization (text-based)
✓ Fragmentation analysis
✓ Algorithm comparison
✓ Memory reset
✓ Input validation
✓ Error handling
✓ Professional output formatting

COMPLETE PROJECT - READY TO COMPILE AND RUN!
================================================================================
*/
