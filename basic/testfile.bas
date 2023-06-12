0    REM YES
5    SPC 5
10   INPUT "User input: "; var::INT
20   PRINT $var

30   PRINT "Before subroutine"
40   GOSUB 70

50   PRINT "After subroutine"
55   LIST
60   END

70   PRINT "In subroutine"
71   GOSUB 900
80   RETURN

900  PRINT "Variable test"
910  LET A::INT = 1
920  PRINT "A "; $A
930  LET B::INT = $A
940  PRINT "B "; $B
950  TYPE $B; C
960  PRINT "C "; $C
970  CLR C
980  REM 980 PRINT $C
1000 RETURN