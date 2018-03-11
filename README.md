# BangLang OOP project Spring 2017

Update Log
==========
	1/6/17 	- Bang lang has gone case agnostic. Beware though, variables names are case agnostic too. Strings,
		  on the other hand, remain unaffected.
	1/6/17 	- Do while is incorporated. This is still at a Nightly Stage of Testing. Any bug-find is appreciated.
	31/5/17 - Critical Bug handeled in processing empty lines.
	29/5/17 - Comments included.
	29/5/17 - Statically Compiled dll independent release issued.
	28/5/17 - New methods 
	24/5/17 - String Comparison included.
	22/5/17 - First Pre-Alpha.

A Word from Authors:
===================
	Bang-Lang framework incorporates exception handling at both Compilation and VM-Runtime Stages. But as with
all organically developed, complex softwares; Bang has its quirks and is still in a passive development stage. While
it has been our attempt to keep it bug free, and while no known critical bugs are still in the code; it is a due
acknowledgement that our code is not perfect. There may exist bugs unbeknownst to developers.

That said, there are some fundamental idiosyncrasies in our nascent project that, when they became apparent,
were deemed to be too deeply rooted to fix in a surgical manner. One of them is the negative number mathematics.
Another notable case is logic handling. Yet another is the lack of an elegant support for else-if.
Owing to our limited experience and vocational training in compiler writing, we could not make a model robust
enough to handle changes long past the initial stages of development. But, as luck has had it, none of these
problems are seriously hindering and there exist mildly-elegant workarounds to achieve the intended results.

The authors have agreed upon regarding these "idiosyncrasies" as language features - as opposed to language
flaws. They are compared to the quirks of haskell, that, for one, will make the programmer think in novel ways.

To part, we state that Bang-Lang is, above all, simple. With a ridiculously small set of statement types it can
be learnt in about 10 minutes. A good documentation is still due. However, the examples provided with this text
are sufficiently expressive in teaching the entirity of the language. Ofcourse, the statement set will be appended
with this text to aid the reader.

It has been an immense pleasure and a privileged experience to work as a team on this project. We hope that Bang
turns out to be a source of learning for you, as it has been to us delightfully.

-Saad
-Asad
-Saif

Statement Set:
=============
// Comments, also by the keyword COM
PRINTL 	-- Prints a line
PRINT 	-- Prints without returning carriage.
INPUT 	-- Takes input
IF	-- The traditional if, works with ELSE and ENDIF
WHILE   -- The traditional while loop
DOWHILE	-- The traditional do-while loop
DIM	-- Declare in memory. Works with NUMBER and STRING
SET 	-- Assign a value to the variable.

Caution:
========
Declare negative numbers with preceding zeros i.e.
	Set x as 0-55
instead of
	set x as -55