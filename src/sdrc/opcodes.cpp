//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
//
//	This library is free software; you can redistribute it and/or
//	modify it under the terms of the GNU Lesser General Public
//	License as published by the Free Software Foundation; either
//	version 2.1 of the License, or (at your option) any later version.
//
//	This library is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//	Lesser General Public License for more details.
//
//	You should have received a copy of the GNU Lesser General Public
//	License along with this library; if not, write to the Free Software
//	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
const char	*opcodeIf						=			"\tif                ";
const char	*opcodeElse						=			"\telse              ";
const char	*opcodeEndif					=			"\tendif             ";
const char	*opcodeGatherHeader				=			"\tgatherHeader      ";
const char	*opcodeGather					=			"\tgather            ";
const char	*opcodeGatherElse				=			"\tgatherElse        ";
const char	*opcodeGatherEnd				=			"\tgatherEnd         ";
const char	*opcodeFor						=			"\tfor               ";
const char	*opcodeBeginfor					=			"\tforbegin          ";
const char	*opcodeEndfor					=			"\tforend            ";
const char	*opcodeIlluminance				=			"\tilluminance       ";
const char	*opcodeBeginIlluminance			=			"\tbeginilluminance  ";
const char	*opcodeEndIlluminance			=			"\tendilluminance    ";
const char	*opcodeSolar					=			"\tsolar             ";
const char	*opcodeEndSolar					=			"\tendsolar          ";
const char	*opcodeIlluminate				=			"\tilluminate        ";
const char	*opcodeEndIlluminate			=			"\tendilluminate     ";
const char	*opcodeBreak					=			"\tbreak             ";
const char	*opcodeContinue					=			"\tcontinue          ";
const char	*opcodeReturn					=			"\treturn            ";


////////////////////////////////////////////////////////////////////////
//	Relations

// Equal
const char	*opcodeFloatEqual				=			"\tfeql              ";
const char	*opcodeVectorEqual				=			"\tveql              ";
const char	*opcodeStringEqual				=			"\tseql              ";
const char	*opcodeMatrixEqual				=			"\tmeql              ";

// Not Equal
const char	*opcodeFloatNotEqual			=			"\tfneql             ";
const char	*opcodeVectorNotEqual			=			"\tvneql             ";
const char	*opcodeStringNotEqual			=			"\tsneql             ";
const char	*opcodeMatrixNotEqual			=			"\tmneql             ";

// Less than or equal
const char	*opcodeFloatELess				=			"\tfelt              ";
const char	*opcodeVectorELess				=			"\tvelt              ";

// Less than
const char	*opcodeFloatLess				=			"\tflt               ";
const char	*opcodeVectorLess				=			"\tvlt               ";

// Greater than or equal
const char	*opcodeFloatEGreater			=			"\tfegt              ";
const char	*opcodeVectorEGreater			=			"\tvegt              ";

// Greater than
const char	*opcodeFloatGreater				=			"\tfgt               ";
const char	*opcodeVectorGreater			=			"\tvgt               ";

////////////////////////////////////////////////////////////////////////
//	Conversions
const char	*opcodeMatrixFromFloat			=			"\tmfromf            ";
const char	*opcodeVectorFromFloat			=			"\tvfromf            ";
const char	*opcodeMatrixFromVector			=			"\tmfromv            ";

// System conversion
const char	*opcodeVectorFrom				=			"\tvfrom             ";
const char	*opcodeColorFrom				=			"\tcfrom             ";
const char	*opcodePointFrom				=			"\tpfrom             ";
const char	*opcodeMatrixFrom				=			"\tmfrom             ";

////////////////////////////////////////////////////////////////////////
//	Boolean operations
const char	*opcodeAnd						=			"\tand               ";
const char	*opcodeOr						=			"\tor                ";
const char	*opcodeXor						=			"\txor               ";
const char	*opcodeNXor						=			"\tnxor              ";
const char	*opcodeNot						=			"\tnot               ";


////////////////////////////////////////////////////////////////////////
//	Unary operations

//	Negetion
const char	*opcodeNegFloat					=			"\tnegf              ";
const char	*opcodeNegVector				=			"\tnegv              ";
const char	*opcodeNegMatrix				=			"\tnegm              ";

////////////////////////////////////////////////////////////////////////
//	Binary operations

// Dot and cross products
const char	*opcodeDotProduct				=			"\tdot               ";
const char	*opcodeCrossProduct				=			"\tcross             ";

// Division
const char	*opcodeDivFloatFloat			=			"\tdivff             ";
const char	*opcodeDivVectorVector			=			"\tdivvv             ";
const char	*opcodeDivMatrixMatrix			=			"\tdivmm             ";

// Multipication
const char	*opcodeMulFloatFloat			=			"\tmulff             ";
const char	*opcodeMulVectorVector			=			"\tmulvv             ";
const char	*opcodeMulMatrixMatrix			=			"\tmulmm             ";
const char	*opcodeMulMatrixPoint			=			"\tmulmp             ";
const char	*opcodeMulMatrixNormal			=			"\tmulmn             ";
const char	*opcodeMulMatrixVector			=			"\tmulmv             ";
const char	*opcodeMulPointMatrix			=			"\tmulpm             ";
const char	*opcodeMulNormalMatrix			=			"\tmulnm             ";
const char	*opcodeMulVectorMatrix			=			"\tmulvm             ";

// Addition
const char	*opcodeAddFloatFloat			=			"\taddff             ";
const char	*opcodeAddVectorVector			=			"\taddvv             ";
const char	*opcodeAddMatrixMatrix			=			"\taddmm             ";

// Subtraction
const char	*opcodeSubFloatFloat			=			"\tsubff             ";
const char	*opcodeSubVectorVector			=			"\tsubvv             ";
const char	*opcodeSubMatrixMatrix			=			"\tsubmm             ";

////////////////////////////////////////////////////////////////////////
//	Data movement operations

// Uniform to varying assignment
const char 	*opcodeVUFloat					=			"\tvufloat           ";
const char 	*opcodeVUVector					=			"\tvuvector          ";
const char 	*opcodeVUMatrix					=			"\tvumatrix          ";
const char 	*opcodeVUString					=			"\tvustring          ";

//	Move
const char	*opcodeMoveFloatFloat			=			"\tmoveff            ";
const char	*opcodeMoveVectorVector			=			"\tmovevv            ";
const char	*opcodeMoveStringString			=			"\tmovess            ";
const char	*opcodeMoveMatrixMatrix			=			"\tmovemm            ";
const char	*opcodeMoveAFloatFloat			=			"\tmoveaff           ";
const char	*opcodeMoveAVectorVector		=			"\tmoveavv           ";
const char	*opcodeMoveAStringString		=			"\tmoveass           ";
const char	*opcodeMoveAMatrixMatrix		=			"\tmoveamm           ";
const char	*opcodeFFromArray				=			"\tffroma            ";
const char	*opcodeFToArray					=			"\tftoa              ";
const char	*opcodeVFromArray				=			"\tvfroma            ";
const char	*opcodeVToArray					=			"\tvtoa              ";
const char	*opcodeMFromArray				=			"\tmfroma            ";
const char	*opcodeMToArray					=			"\tmtoa              ";
const char	*opcodeSFromArray				=			"\tsfroma            ";
const char	*opcodeSToArray					=			"\tstoa              ";
const char	*opcodeUFFromArray				=			"\tuffroma           ";
const char	*opcodeUVFromArray				=			"\tuvfroma           ";
const char	*opcodeUMFromArray				=			"\tumfroma           ";
const char	*opcodeUSFromArray				=			"\tusfroma           ";



////////////////////////////////////////////////////////////////////////
//	Constants

const char	*constantLoopName				=			"1__$$__$$__$$__loop";
const char	*constantBlockName				=			"1__$$__$$__$$__block";
const char	*constantShaderMain				=			"1__$$__$$__$$__main";
const char	*constantReturnValue			=			"__ReturnValue__";
const char	*constantBug					=			"Compiler bug, please report";

