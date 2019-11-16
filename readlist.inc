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
	iny			; is there a better way than iny/beq four times 
	beq pageinc1		; to check for the end of the actions list?
ret1:
	lda (ach),y
	sta verahi
	iny
	beq pageinc2
ret2:
	lda (ach),y
	sta veramid
	iny
	beq pageinc3
ret3:
	lda (ach),y
	sta veralo
	lda Character
	sta veradat
	iny
	beq pageinc4
ret4:
	jmp readloop

pageinc1:
	lda ach
	inc 
	sta ach
	jmp ret1
pageinc2:
	lda ach
	inc 
	sta ach
	jmp ret2
pageinc3:
	lda ach
	inc 
	sta ach
	jmp ret3
pageinc4:
	lda ach
	inc 
	sta ach
	jmp ret4
