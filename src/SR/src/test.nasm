; Exports
global testSR2

SECTION .text

; int testSR2()
testSR2:
	push ebp
	mov ebp, esp
	mov eax, 420d
	pop ebp
	ret
