; a hma xy routine for storing grids in HMA instead of VERA
;
; jsr to hmxy to set hma addr for the co-ordinate
;
; recommended to set for Y=row , X=0 
;
; in that way, can index indirect following for all X
;
; but will calc an addr anyway

hmxy:
	lda CursorY
	tax
	sta scratchpad
	lda #1
	and scratchpad
	beq even
odd:
	txa
	lsr
	clc
	adc #$B0
	sta mklh
	lda #$50
	sta mkll
	lda CursorX
	adc mkll
	sta mkll
	jmp hmxyend
even:
	txa
	lsr
	clc
	adc #$B0
	sta mklh
	lda #00
	adc CursorX
	sta mkll
hmxyend:
	rts


hmstore:
	phx
	phy
	pha
	jsr hmxy
	tya 
	ldy #0
	sta (mkll),y
	pla
	ply
	plx
	rts

hmget:
	phx
	phy
	pha
	jsr hmxy
	ldy #0
	lda (mkll),y
	sta qc
	pla
	ply
	plx
	rts

