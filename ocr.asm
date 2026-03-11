; ocr.asm
; int match_digit(const unsigned char *img, const unsigned char *tmpl, int size)
; Arguments (cdecl, 32-bit):
;   [esp+4] -> img
;   [esp+8] -> tmpl
;   [esp+12] -> size
; Return: int score (#mismatched pixels)

global match_digit
section .data
msg db ">> Inside Assembly match_digit!", 10, 0

section .text
extern printf

match_digit:
; Print debug message
    push msg
    call printf
    add esp, 4
    push ebp
    mov ebp, esp
    push esi
    push edi
    push ecx
    push ebx

    mov esi, [ebp+8]     ; esi = img pointer
    mov edi, [ebp+12]    ; edi = tmpl pointer
    mov ecx, [ebp+16]    ; ecx = size (counter)
    xor eax, eax         ; eax = mismatch counter (score = return value)

    
.loop:
    cmp ecx, 0
    je .done

    ; Load image pixel
    mov bl, [esi]
    cmp bl, 128
    jb .img_zero
    mov bl, 255
    jmp .img_done
.img_zero:
    xor bl, bl
.img_done:

    ; Load template pixel
    mov dl, [edi]
    cmp dl, 128
    jb .tmpl_zero
    mov dl, 255
    jmp .tmpl_done
.tmpl_zero:
    xor dl, dl
.tmpl_done:

    ; Compare
    cmp bl, dl
    je .same
    inc eax             ; mismatch count++
.same:

    inc esi
    inc edi
    dec ecx
    jmp .loop

.done:
    pop ebx
    pop ecx
    pop edi
    pop esi
    pop ebp
    ret
