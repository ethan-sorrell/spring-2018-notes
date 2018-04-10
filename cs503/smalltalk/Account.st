Object subclass: #Account.
Account instanceVariableNames: 'balance income outgo'.
Account addClassVarName: 'Total'.
Account class instanceVariableNames: 'Subtotal'.

Account extend [
        open: b [
                balance:=b. 
                Total:=Total+b. 
                self class addSubtotal: b.
                income := Dictionary new.
                outgo := Dictionary new
        ]
        getBalance [^balance]
        display [
                Transcript display: 'Balance='; display: balance; cr
        ]
        deposit: amount from: source [
                balance := balance+amount.
                income at: source put: (amount + (self totalReceivedFrom: source)).
                Total:=Total+amount. 
                self class addSubtotal: amount
        ]
        withdraw: amount for: reason [
                balance := balance-amount.
                outgo at: reason put: (amount + (self totalSpentFor: reason)).
                Total:=Total-amount. 
                self class addSubtotal: 0-amount
        ]
        totalReceivedFrom: source [
                ^(income includesKey: source)
                        ifTrue:  [ income at: source ]
                        ifFalse: [ 0 ]
        ]
        totalSpentFor: reason [
                ^(outgo includesKey: reason)
                        ifTrue:  [ outgo at: reason ]
                        ifFalse: [ 0 ]
        ]
]

Account class extend [
        new [ 
                Total isNil ifTrue: [Total:=0].
                Subtotal isNil ifTrue: [Subtotal:=0].
                ^super new
        ]
        addSubtotal: b [Subtotal:=Subtotal+b]
        getTotal [^Total]
        getSubtotal [^Subtotal]
]

Account subclass: #CheckingAccount.
CheckingAccount instanceVariableNames: 'checksUsed checksLeft'.

CheckingAccount extend [
        open: b [
                super open: b.
                checksUsed := 0.
                checksLeft := 0
        ]
        display [
                super display.
                Transcript display: 'Checks used='; display: checksUsed; cr.
                Transcript display: 'Checks left='; display: checksLeft; cr
        ]
        newChecks: number [
                checksLeft := checksLeft+number
        ]
        writeCheck: amount for: reason [
                checksUsed := checksUsed+1.
                checksLeft := checksLeft-1.
                self withdraw: amount for: reason
        ]
]

Account subclass: #SavingsAccount.
SavingsAccount instanceVariableNames: 'interestRate'.

SavingsAccount extend [
        open: b [
                super open: b.
                interestRate := 0
        ]
        display [
                super display.
                Transcript display: 'Interest rate='; display: interestRate; cr.
                Transcript display: 'Total interest='; display: (self totalReceivedFrom: 'interest'); cr
        ]
        setRate: percentage [
                interestRate := percentage
        ]
        earnInterest [
                | temp |
                temp := (balance*interestRate/100).
                self deposit: temp from: 'interest'
        ]
]

a1 := Account new open: 100.
a2 := Account new open: 200.
c1 := CheckingAccount new open: 400.
c2 := CheckingAccount new open: 500.
s1 := SavingsAccount new open: 700.
s2 := SavingsAccount new open: 800.

a1 getBalance printNl.
a2 getBalance printNl.
c1 getBalance printNl.
c2 getBalance printNl.
s1 getBalance printNl.
s2 getBalance printNl.

Transcript cr.

Account getTotal printNl.
Account getSubtotal printNl.
CheckingAccount getTotal printNl.
CheckingAccount getSubtotal printNl.
SavingsAccount getTotal printNl.
SavingsAccount getSubtotal printNl.

Transcript cr.

a1 deposit: 1000 from: 'dad'.
a1 withdraw: 400 for: 'car'.
a1 deposit: 800 from: 'mom'.
a1 withdraw: 100 for: 'party'.
a1 deposit: 700 from: 'dad'.
a1 withdraw: 200 for: 'car'.
Transcript display: 'Total from dad='; display: (a1 totalReceivedFrom: 'dad'); cr.
Transcript display: 'Total for car='; display: (a1 totalSpentFor: 'car'); cr.
a1 display.

Transcript cr.

c1 deposit: 3000 from: 'inheritance'.
c1 newChecks: 100.
c1 writeCheck: 800 for: 'vacation'.
c1 writeCheck: 400 for: 'vacation'.
c1 display.

Transcript cr.

s1 setRate: 2.00.
s1 deposit: 2000 from: 'paycheck'.
s1 earnInterest.
s1 deposit: 300 from: 'cash'.
s1 earnInterest.
s1 display.

Transcript cr.

a1 getBalance printNl.
a2 getBalance printNl.
c1 getBalance printNl.
c2 getBalance printNl.
s1 getBalance printNl.
s2 getBalance printNl.

Transcript cr.

Account getTotal printNl.
Account getSubtotal printNl.
CheckingAccount getTotal printNl.
CheckingAccount getSubtotal printNl.
SavingsAccount getTotal printNl.
SavingsAccount getSubtotal printNl.
