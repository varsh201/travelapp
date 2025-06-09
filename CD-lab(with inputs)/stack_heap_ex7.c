#include <stdio.h>
#include <stdlib.h>

void simulateStackHeapCollision() {
    int heapPointer = 1;    // Simulated heap grows upward
    int stackPointer = 1022; // Simulated stack grows downward
    int collisionAddress = 512;

    printf("Simulating Stack and Heap Growth\n\n");

    while (heapPointer < collisionAddress && stackPointer > collisionAddress) {
        printf("Heap Pointer: %d, Stack Pointer: %d\n", heapPointer, stackPointer);
        
        heapPointer++;
        stackPointer--;

        // Fast-forward near collision point for brevity
        if (heapPointer == 20) {
            heapPointer = 498;
            stackPointer = 525;
        }
    }

    // Print the collision point
    printf("\nHeap Pointer: %d, Stack Pointer: %d\n", heapPointer, stackPointer);
    printf("\nSimulated Collision Detected at address %d!\n", collisionAddress);
    printf("\nSimulation complete.\n");
}

int main() {
    simulateStackHeapCollision();
    return 0;
}