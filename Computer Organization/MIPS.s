# p1.s
 
  .text
  
  .globl __start
  
__start:
  
main:

  # Load array
  
   addi $sp, $sp, -76
   addi $s0, $0, 0   #Positive Integer Count
   addi $s1, $0, 0   #Zero Count
   addi $s2, $0, 0   #Negative Integer Count
   addi $t1, $0, 14  #iterator

  # Store the current address
   sw $ra, 72($sp)
   sw $s0, 68($sp)
   sw $s1, 64($sp)
   sw $s2, 60($sp)
   sw $t1, 56($sp)
   
   addi $t0, $0, -24
   sw $t0, 52($sp)
   addi $t0, $0, 7
   sw $t0, 48($sp)
   addi $t0, $0, 8
   sw $t0, 44($sp)
   addi $t0, $0, 0
   sw $t0, 40($sp)
   addi $t0, $0, 0
   sw $t0, 36($sp)
   addi $t0, $0, 7
   sw $t0, 32($sp)
   addi $t0, $0, 3
   sw $t0, 28($sp)
   addi $t0, $0, -67
   sw $t0, 24($sp)
   addi $t0, $0, -46
   sw $t0, 20($sp)
   addi $t0, $0, 0
   sw $t0, 16($sp)
   addi $t0, $0, 2
   sw $t0, 12($sp)
   addi $t0, $0, 5
   sw $t0, 8($sp)
   addi $t0, $0, -3
   sw $t0, 4($sp)
   addi $t0, $0, 57
   sw $t0, 0($sp)  

Countarray:
   beq $t1, $0, Exit   # Countarray iteration
   addi $t1, $t1, -1
   lw $t2, 0($sp)      # Load the element of array to compare
   addi $t7, $0, 0     # Waiting load word to be executed
   addi $t7, $0, 0     
   addi $t7, $0, 0     
   beq $0, $t2, Equ    
   slt $s3, $t2, $0
   addi $t7, $0, 0     # Waiting load word to be executed
   addi $t7, $0, 0     
   addi $t7, $0, 0  
   bne $s3, $0, Neg
   slt $s3, $0, $t2
   addi $t7, $0, 0     # Waiting load word to be executed
   addi $t7, $0, 0     
   addi $t7, $0, 0  
   bne $s3, $0, Pos
                       
Finish:                   
   addi $t7, $0, 0     # Waiting load word to be executed
   addi $t7, $0, 0     
   addi $t7, $0, 0  
   addi $sp, $sp, 4 
   addi $t7, $0, 0     # Waiting load word to be executed
   addi $t7, $0, 0     
   addi $t7, $0, 0  
   j Countarray        
 
Pos: addi $t7, $0, 0     # Waiting load word to be executed
     addi $t7, $0, 0     
     addi $t7, $0, 0  
     addi $s0, $s0 ,1    #if the number is equal to 0
     j Finish
   

Neg: addi $t7, $0, 0     # Waiting load word to be executed
     addi $t7, $0, 0     
     addi $t7, $0, 0  
     addi $s2, $s2 ,1    #if the number is equal to 0
     j Finish
   

Equ: 
     addi $t7, $0, 0     # Waiting load word to be executed
     addi $t7, $0, 0     
     addi $t7, $0, 0  
     addi $s1, $s1 ,1    #if the number is equal to 0
     j Finish

# Exit

Exit:
   lw $ra, 16($sp)
   addi $sp, $sp, 20
   jr $ra

   addiu $v0, $0, 10      # Prepare to exit (system call 10)

   syscall                # Exit











