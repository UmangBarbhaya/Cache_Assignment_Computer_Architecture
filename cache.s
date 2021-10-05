.data
a: .word 2048

.text
li a0,1024 #size=1024
li x21,2 #step=2
li x20,4 #reps=10
li x22,1 #option=1

jal store

li a0,10
ecall

store:

la x2,a
add x3,x2,a0
slli x5,x21,2

go1:
beq x22,x0,go
lb x6,0(x2)
addi x6,x6,1
sb x6,0(x2)

j go2
go:
sb x0,0(x2)
go2:
add x2,x2,x5
blt x2,x3,go1
addi x20,x20,-1
bgtz x20, store
jr ra
