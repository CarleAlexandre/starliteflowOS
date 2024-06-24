.section .text
.global enable_fpu
.global disable_fpu

enable_fpu:
    #; Clear EM and TS bits in CR0
    mov %cr0, %rax
    and $0xFFFFFFFFFFFFFFF7, %rax#; Clear TS (bit 3)
    and $0xFFFFFFFFFFFFFFFB, %rax#; Clear EM (bit 2)
    mov %rax, %cr0

    #; Set OSFXSR and OSXMMEXCPT bits in CR4
    mov %cr4, %rax
    or $0x0000000000000600, %rax#; Set OSFXSR (bit 9) and OSXMMEXCPT (bit 10)
    mov %rax, %cr4

    ret

disable_fpu:
    #; Set EM bit in CR0
    mov %cr0, %rax
    or $0x0000000000000004, %rax#; Set EM (bit 2)
    mov %rax, %cr0

    #; Optionally, clear OSFXSR and OSXMMEXCPT bits in CR4
    mov %cr4, %rax
    and $0xFFFFFFFFFFFFF9FF, %rax#; Clear OSFXSR (bit 9) and OSXMMEXCPT (bit 10)
    mov %rax, %cr4

    ret

