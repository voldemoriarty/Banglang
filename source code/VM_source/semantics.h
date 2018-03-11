#pragma once
#ifndef SEMANTICS_H
#define SEMANTICS_H

#define comment_char ';'

#include <vector>
#include <string>
#include <map>



enum class keyws_t {
	/*Store all the keywords here*/
	stloc_n,//
	ldloc_n,//
	stloc_s,//
	ldloc_s,//

	add,//
	sub,//
	mul,//
	div,//
	exp,//
	rem,//

	label,//
	gonna,//

	jmp,//
	jeq,//
	jle,//
	jge,//
	jne,//
	jl,//
	jg,//
	jeq_str,//

	out_s,//
	in_s,//
	out_n,//
	in_n,//

	num,//
	str,//

	func,//
	call,//
	ret,//
	end,//

	ceq,//
	cne,//
	cle,//
	cg,//
	cl,//
	cge,//
	ceq_str,//

	wait, //

	nl,//

	exit,//

	Count	//This is used to keep track of enum items, make sure it is last
};
//fill the keyws here in the same order as in the enum


#endif