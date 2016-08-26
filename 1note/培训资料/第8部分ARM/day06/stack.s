
    .data 
    .code 32

    .global irq_stack
    .global irq_stack_end
irq_stack:
     .space   256
irq_stack_end:

     .global fiq_stack
     .global fiq_stack_end
fiq_stack:
     .space   256
fiq_stack_end:


    .end
