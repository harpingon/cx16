;
; initialise the orders list and allow a new order to be appended to the list
;
initlist:
	pha
	phy
	lda #<.actions		; address the action list
	sta mkll
	lda #>.actions
	sta mklh 
	ldy #0
	sty mkly		; store zero in mkly so list addition begins at the start
	lda #255		; store end of list FF in three bytes
	sta (mkll),y
	iny
	sta (mkll),y
	iny
	sta (mkll),y
	ply
	pla
	rts

storeaction:
	pha
	phy
	phx
	ldy mkly		; pick up list index
	lda sc			; character to store
	sta (mkll),y
	iny
	cmp #0 			; rolled over?
	beq storeinc1	        ; yes! inc the high addr
storecharx:
	lda sx			; x position to set char
	sta (mkll),y
	iny
	cmp #0 			; rolled over?           
	beq storeinc2	        ; yes! inc the high addr
storechary:
	lda sy
	sta (mkll),y
	iny
	cmp #0			; rolled over?
	beq storeinc3		; yes! inc the high addr
storechardone:
	sty mkly		; store away the index for the next addition
	plx
	ply
	pla
	rts			
storeinc1:
	lda mklh
	inc 
	sta mklh
	jmp storecharx
storeinc2:
	lda mklh
	inc 
	sta mklh
	jmp storechary
storeinc3:
	lda mklh
	inc 
	sta mklh
	jmp storechardone
