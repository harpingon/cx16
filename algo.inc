;
; game of life algorithm. Shall the cell be born, survive or die 
;
queryscreen:
	lda #79
	sta CursorX
	lda #59
	sta CursorY
queryleft:
	jsr querycolumn
	dec CursorX
	bne queryleft
	jsr querycolumn ; make sure to do the last X column (0)
	lda #255	; terminate the list
	sta sx
	sta sy
	sta sc
	jsr storeaction
	rts		; Return to caller

querycolumn:
	jsr veraquery
	jsr neighbors
	dec CursorY
	bne querycolumn
	jsr veraquery
	jsr neighbors	; make sure to do the final character
	lda #59
	sta CursorY
	rts
	
neighbors:
	pha
	phy
	phx
	stz nn		; start with zero neighbors
	lda qc
	sta kc		; keep the current cell state in kc
	lda CursorX	
	sta kx		; keep our current pos X
	lda CursorY
	sta ky		; keep our current pos Y

	dec CursorX	; start on the upper left
	dec CursorY
	lda #255
	cmp CursorX	; did it wrap?
	bne nc1		; nope
	lda #79		; wrap to right edge
	sta CursorX	
nc1:
	lda #255
	cmp CursorY	; did it wrap?
	bne nc2		; nope
	lda #59
	sta CursorY
nc2:
	jsr veraquery 	; top left
	jsr addif	
	inc CursorX	; top middle
	lda #80
	cmp CursorX	; did it wrap?
	bne nc3		; nope
	lda #0
	sta CursorX	; wrap to left edge
nc3:
	jsr veraquery	; top middle
	jsr addif
	inc CursorX	; top right
	lda #80
	cmp CursorX	; did it wrap?
	bne nc4		; nope
	lda #0
	sta CursorX	; wrap to left edge
nc4:
	jsr veraquery	; top right
	jsr addif

	lda kx		; reset to middle
	sta CursorX
	lda ky
	sta CursorY

	dec CursorX	; middle left
	lda #255
	cmp CursorX	; did it wrap?
	bne nc5		; nope
	lda #79		; wrap to right edge
	sta CursorX
nc5:
	jsr veraquery	; middle left
	jsr addif

	lda kx
	sta CursorX
	inc CursorX	; middle right
	lda #80
	cmp CursorX	; did it wrap?
	bne nc6		; nope
	lda #0
	sta CursorX	; wrap to left edge
nc6:
	jsr veraquery
	jsr addif
	
	lda kx		; reset to middle
	sta CursorX
	lda ky
	sta CursorY
	
	inc CursorY	; lower left
	lda #60
	cmp CursorY	; did it wrap?
	bne nc7		; nope
	lda #0
	sta CursorY	; wrap to top
nc7:
	dec CursorX
	lda #255
	cmp CursorX	; did it wrap?
	bne nc8		; nope
	lda #79
	sta CursorX	; wrap to right edge
nc8:
	jsr veraquery 	; lower left
	jsr addif

	inc CursorX	; bottom middle
	lda #80
	cmp CursorX	; did it wrap?
	bne nc9		; nope
	lda #0		; wrap to left
	sta CursorX
nc9:
	jsr veraquery	; bottom middle
	jsr addif

	inc CursorX	; bottom right
	lda #80
	cmp CursorX	; did it wrap?
	bne nc10	; nope 
	lda #0		; wrap to left
nc10:
	jsr veraquery
	jsr addif

	; that should be all the neighbors added, find
	; out if we live or die

	lda #$2A
	cmp kc		; is the existing cell living or dead
	beq living
	lda #3		; only thing a dead cell can do is be born on 3 count
	cmp nn
	beq born
	jmp eol
born:
	lda #$2A	; make cell live
	sta sc
	lda kx
	sta sx
	lda ky
	sta sy
	jsr storeaction
	jmp eol

living:
	lda #2
	cmp nn
	beq eol		; this one survived
	lda #3
	cmp nn
	beq eol		; as did this one   
	lda #32		; make cell die
	sta sc
	lda kx
	sta sx
	lda ky
	sta sy
	jsr storeaction	;unlucky 



	;;;

eol:
	lda kx		; restore CursorX and CursorY 
	sta CursorX	; to continue reading screen loop
	lda ky
	sta CursorY
	plx
	ply
	pla
	rts

addif:
	lda #$2A
	cmp qc
	bne addifreturn
	inc nn		; add neighbor
addifreturn:
	rts
