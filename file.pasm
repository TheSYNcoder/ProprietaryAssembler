MOV DX string
MOV DX string
MOV AH 09H
INT 21H
MOV AH 4CH
INT 21H
MOV AX label 
string: DB 10
label: DB "hello"


