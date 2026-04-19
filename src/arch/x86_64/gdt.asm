global gdt_load
gdt_load:
    lgdt [rdi]

    ; Reload the segment registers
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    ; Reload CS via far return
    pop rdi
    push 0x08
    push rdi
    retfq

    jmp $       ; If nothing happens, halt indefinitely
