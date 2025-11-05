// ------------------------------------------------------------
// Knight Rider LED scanner for C64 User Port (PB0..PB7)
// CIA2 Port B ($DD01), DDRB ($DD03)
// Single LED sweeps back and forth
// ------------------------------------------------------------

.var CIA2_PORTB = $DD01
.var CIA2_DDRB  = $DD03

// zero page vars
.label pattern = $FB   // current LED bit pattern
.label dir     = $FA   // direction flag: 1=right, 0=left

// BASIC autostart header for SYS2064
*=$0801
    .word nextline
    .word 10
    .byte $9e
    .text "2064"
    .byte 0
nextline:
    .word 0

// ------------------------------------------------------------
// program starts here
// ------------------------------------------------------------
*=$0810
start:
    sei                 // disable interrupts
    lda #$ff
    sta CIA2_DDRB       // set all Port B lines as outputs

    lda #$01
    sta pattern         // start with LED 0
    lda #$01
    sta dir             // moving right

mainloop:
    lda pattern
    sta CIA2_PORTB      // output to user port
    jsr delay           // wait a bit

    lda dir
    cmp #$01
    beq move_right

    // ---- move left ----
    lda pattern
    cmp #$01
    beq flip_to_right
    lsr                 // shift right (accumulator)
    sta pattern
    jmp mainloop

move_right:
    lda pattern
    cmp #$80
    beq flip_to_left
    asl                 // shift left (accumulator)
    sta pattern
    jmp mainloop

flip_to_left:
    lda #$40            // next step after $80
    sta pattern
    lda #$00
    sta dir             // now move left
    jmp mainloop

flip_to_right:
    lda #$02            // next step after $01
    sta pattern
    lda #$01
    sta dir             // now move right
    jmp mainloop

// ------------------------------------------------------------
// simple software delay (adjust X/Y loops for speed)
// ------------------------------------------------------------
delay:
    ldx #$ff
d1: ldy #$ff
d2: dey
    bne d2
    dex
    bne d1
    rts
