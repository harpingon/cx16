readlist:
	lda #<.actions		; address the action list
	sta ach
	ldx #>.actions
	stx ach+1
	ldy #0
readloop:
	lda (ach),y
	cmp #255 		; is this the last action
	bne outputaction        ; no - update vera
	rts

outputaction:
	sta Character
	iny			; is there a better way than iny/beq four times 
	beq pageinc1		; to check for the end of the actions list?
ret1:
	lda (ach),y
	sta CursorX
	iny
	beq pageinc2
ret2:
	lda (ach),y
	sta CursorY
	iny
	beq pageinc3
ret3:
	jsr veraprint
	jmp readloop
pageinc1:
	inc ach+1
	jmp ret1
pageinc2:
	inc ach+1
	jmp ret2
pageinc3:
	inc ach+1
	jmp ret3
