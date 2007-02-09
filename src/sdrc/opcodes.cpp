//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//	
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//
//  File				:	opcodes.cpp
//  Classes				:
//  Description			:	All the string definitions
//
////////////////////////////////////////////////////////////////////////
#include	"opcodes.h"


////////////////////////////////////////////////////////////////////////
//	Conditionals
char	*opcodeIf						=			"\tif                ";
char	*opcodeElse						=			"\telse              ";
char	*opcodeEndif					=			"\tendif             ";
char	*opcodeGatherHeader				=			"\tgatherHeader      ";
char	*opcodeGather					=			"\tgather            ";
char	*opcodeGatherElse				=			"\tgatherElse        ";
char	*opcodeGatherEnd				=			"\tgatherEnd         ";
char	*opcodeFor						=			"\tfor               ";
char	*opcodeBeginfor					=			"\tforbegin          ";
char	*opcodeEndfor					=			"\tforend            ";
char	*opcodeIlluminance				=			"\tilluminance       ";
char	*opcodeBeginIlluminance			=			"\tbeginilluminance  ";
char	*opcodeEndIlluminance			=			"\tendilluminance    ";
char	*opcodeSolar					=			"\tsolar             ";
char	*opcodeEndSolar					=			"\tendsolar          ";
char	*opcodeIlluminate				=			"\tilluminate        ";
char	*opcodeEndIlluminate			=			"\tendilluminate     ";
char	*opcodeBreak					=			"\tbreak             ";
char	*opcodeContinue					=			"\tcontinue          ";
char	*opcodeReturn					=			"\treturn            ";


////////////////////////////////////////////////////////////////////////
//	Relations

// Equal
char	*opcodeFloatEqual				=			"\tfeql              ";
char	*opcodeVectorEqual				=			"\tveql              ";
char	*opcodeStringEqual				=			"\tseql              ";
char	*opcodeMatrixEqual				=			"\tmeql              ";

// Not Equal
char	*opcodeFloatNotEqual			=			"\tfneql             ";
char	*opcodeVectorNotEqual			=			"\tvneql             ";
char	*opcodeStringNotEqual			=			"\tsneql             ";
char	*opcodeMatrixNotEqual			=			"\tmneql             ";

// Less than or equal
char	*opcodeFloatELess				=			"\tfelt              ";
char	*opcodeVectorELess				=			"\tvelt              ";

// Less than
char	*opcodeFloatLess				=			"\tflt               ";
char	*opcodeVectorLess				=			"\tvlt               ";

// Greater than or equal
char	*opcodeFloatEGreater			=			"\tfegt              ";
char	*opcodeVectorEGreater			=			"\tvegt              ";

// Greater than
char	*opcodeFloatGreater				=			"\tfgt               ";
char	*opcodeVectorGreater			=			"\tvgt               ";

////////////////////////////////////////////////////////////////////////
//	Conversions
char	*opcodeMatrixFromFloat			=			"\tmfromf            ";
char	*opcodeVectorFromFloat			=			"\tvfromf            ";
char	*opcodeMatrixFromVector			=			"\tmfromv            ";

// System conversion
char	*opcodeVectorFrom				=			"\tvfrom             ";
char	*opcodeColorFrom				=			"\tcfrom             ";
char	*opcodePointFrom				=			"\tpfrom             ";
char	*opcodeMatrixFrom				=			"\tmfrom             ";

////////////////////////////////////////////////////////////////////////
//	Boolean operations
char	*opcodeAnd						=			"\tand               ";
char	*opcodeOr						=			"\tor                ";
char	*opcodeXor						=			"\txor               ";
char	*opcodeNXor						=			"\tnxor              ";
char	*opcodeNot						=			"\tnot               ";


////////////////////////////////////////////////////////////////////////
//	Unary operations

//	Negetion
char	*opcodeNegFloat					=			"\tnegf              ";
char	*opcodeNegVector				=			"\tnegv              ";
char	*opcodeNegMatrix				=			"\tnegm              ";

////////////////////////////////////////////////////////////////////////
//	Binary operations

// Dot and cross products
char	*opcodeDotProduct				=			"\tdot               ";
char	*opcodeCrossProduct				=			"\tcross             ";

// Division
char	*opcodeDivFloatFloat			=			"\tdivff             ";
char	*opcodeDivVectorVector			=			"\tdivvv             ";
char	*opcodeDivMatrixMatrix			=			"\tdivmm             ";

// Multipication
char	*opcodeMulFloatFloat			=			"\tmulff             ";
char	*opcodeMulVectorVector			=			"\tmulvv             ";
char	*opcodeMulMatrixMatrix			=			"\tmulmm             ";
char	*opcodeMulMatrixPoint			=			"\tmulmp             ";
char	*opcodeMulMatrixNormal			=			"\tmulmn             ";
char	*opcodeMulMatrixVector			=			"\tmulmv             ";
char	*opcodeMulPointMatrix			=			"\tmulpm             ";
char	*opcodeMulNormalMatrix			=			"\tmulnm             ";
char	*opcodeMulVectorMatrix			=			"\tmulvm             ";

// Addition
char	*opcodeAddFloatFloat			=			"\taddff             ";
char	*opcodeAddVectorVector			=			"\taddvv             ";
char	*opcodeAddMatrixMatrix			=			"\taddmm             ";

// Subtraction
char	*opcodeSubFloatFloat			=			"\tsubff             ";
char	*opcodeSubVectorVector			=			"\tsubvv             ";
char	*opcodeSubMatrixMatrix			=			"\tsubmm             ";

////////////////////////////////////////////////////////////////////////
//	Data movement operations

// Uniform to varying assignment
char 	*opcodeVUFloat					=			"\tvufloat           ";
char 	*opcodeVUVector					=			"\tvuvector          ";
char 	*opcodeVUMatrix					=			"\tvumatrix          ";
char 	*opcodeVUString					=			"\tvustring          ";
char 	*opcodeVUBoolean				=			"\tvuboolean         ";

//	Move
char	*opcodeMoveFloatFloat			=			"\tmoveff            ";
char	*opcodeMoveVectorVector			=			"\tmovevv            ";
char	*opcodeMoveStringString			=			"\tmovess            ";
char	*opcodeMoveMatrixMatrix			=			"\tmovemm            ";
char	*opcodeMoveAFloatFloat			=			"\tmoveaff           ";
char	*opcodeMoveAVectorVector		=			"\tmoveavv           ";
char	*opcodeMoveAStringString		=			"\tmoveass           ";
char	*opcodeMoveAMatrixMatrix		=			"\tmoveamm           ";
char	*opcodeFFromArray				=			"\tffroma            ";
char	*opcodeFToArray					=			"\tftoa              ";
char	*opcodeVFromArray				=			"\tvfroma            ";
char	*opcodeVToArray					=			"\tvtoa              ";
char	*opcodeMFromArray				=			"\tmfroma            ";
char	*opcodeMToArray					=			"\tmtoa              ";
char	*opcodeSFromArray				=			"\tsfroma            ";
char	*opcodeSToArray					=			"\tstoa              ";
char	*opcodeUFFromArray				=			"\tuffroma           ";
char	*opcodeUVFromArray				=			"\tuvfroma           ";
char	*opcodeUMFromArray				=			"\tumfroma           ";
char	*opcodeUSFromArray				=			"\tusfroma           ";



////////////////////////////////////////////////////////////////////////
//	Constants

char	*constantLoopName				=			"1__$$__$$__$$__loop";
char	*constantBlockName				=			"1__$$__$$__$$__block";
char	*constantShaderMain				=			"1__$$__$$__$$__main";
char	*constantReturnValue			=			"__ReturnValue__";
char	*constantBug					=			"Compiler bug, please report";
