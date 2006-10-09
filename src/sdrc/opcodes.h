//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.berkeley.edu
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
//  File				:	opcodes.h
//  Classes				:
//  Description			:	The opcode definitions
//
////////////////////////////////////////////////////////////////////////
#ifndef OPCODES_H
#define	OPCODES_H



////////////////////////////////////////////////////////////////////////////////////////////////
// The opcode definitions
////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////
// Conditional execution
extern	char	*opcodeIf						;
extern	char	*opcodeElse						;
extern	char	*opcodeEndif					;
extern	char	*opcodeGatherHeader				;
extern	char	*opcodeGather					;
extern	char	*opcodeGatherElse				;
extern	char	*opcodeGatherEnd				;
extern	char	*opcodeFor						;
extern	char	*opcodeBeginfor					;
extern	char	*opcodeEndfor					;
extern	char	*opcodeIlluminance				;
extern	char	*opcodeEndIlluminance			;
extern	char	*opcodeSolar					;
extern	char	*opcodeEndSolar					;
extern	char	*opcodeIlluminate				;
extern	char	*opcodeEndIlluminate			;
extern	char	*opcodeBreak					;
extern	char	*opcodeContinue					;
extern	char	*opcodeReturn					;


/////////////////////////////////////////////////
// Relations

// Equal
extern char 	*opcodeFloatEqual				;
extern char 	*opcodeVectorEqual				;
extern char 	*opcodeStringEqual				;
extern char 	*opcodeMatrixEqual				;

// Not Equal
extern char 	*opcodeFloatNotEqual			;
extern char 	*opcodeVectorNotEqual			;
extern char 	*opcodeStringNotEqual			;
extern char 	*opcodeMatrixNotEqual			;

// Less than or equal
extern char 	*opcodeFloatELess				;
extern char 	*opcodeVectorELess				;

// Less than
extern char 	*opcodeFloatLess				;
extern char 	*opcodeVectorLess				;

// Greater than or equal
extern char 	*opcodeFloatEGreater			;
extern char 	*opcodeVectorEGreater			;

// Greater than
extern char 	*opcodeFloatGreater				;
extern char 	*opcodeVectorGreater			;

/////////////////////////////////////////////////
// Conversions
extern char 	*opcodeMatrixFromFloat			;
extern char 	*opcodeVectorFromFloat			;
extern char 	*opcodeMatrixFromVector			;

// System conversion
extern	char	*opcodeVectorFrom				;
extern	char	*opcodeColorFrom				;
extern	char	*opcodePointFrom				;
extern	char	*opcodeMatrixFrom				;


/////////////////////////////////////////////////
// Boolean operations
extern char 	*opcodeAnd						;
extern char 	*opcodeOr						;
extern char 	*opcodeXor						;
extern char 	*opcodeNXor						;
extern char 	*opcodeNot						;

/////////////////////////////////////////////////
// Unary operations
extern char 	*opcodeNegFloat					;
extern char 	*opcodeNegVector				;
extern char 	*opcodeNegMatrix				;

/////////////////////////////////////////////////
// Binary operations

// Dot and cross products
extern char 	*opcodeDotProduct				;
extern char 	*opcodeCrossProduct				;

// Division
extern char 	*opcodeDivFloatFloat			;
extern char 	*opcodeDivVectorVector			;
extern char 	*opcodeDivMatrixMatrix			;

// Multipication
extern char 	*opcodeMulFloatFloat			;
extern char 	*opcodeMulVectorVector			;
extern char 	*opcodeMulMatrixMatrix			;
extern char 	*opcodeMulMatrixPoint			;
extern char 	*opcodeMulMatrixNormal			;
extern char 	*opcodeMulMatrixVector			;
extern char 	*opcodeMulPointMatrix			;
extern char 	*opcodeMulNormalMatrix			;
extern char 	*opcodeMulVectorMatrix			;

// Addition
extern char 	*opcodeAddFloatFloat			;
extern char 	*opcodeAddVectorVector			;
extern char 	*opcodeAddMatrixMatrix			;

// Subtraction
extern char 	*opcodeSubFloatFloat			;
extern char 	*opcodeSubVectorVector			;
extern char 	*opcodeSubMatrixMatrix			;


/////////////////////////////////////////////////
// Data movement operations
extern char 	*opcodeVUFloat					;
extern char 	*opcodeVUVector					;
extern char 	*opcodeVUMatrix					;
extern char 	*opcodeVUString					;
extern char 	*opcodeVUBoolean				;

extern char 	*opcodeMoveFloatFloat			;
extern char 	*opcodeMoveVectorVector			;
extern char 	*opcodeMoveStringString			;
extern char 	*opcodeMoveMatrixMatrix			;
extern char 	*opcodeMoveAFloatFloat			;
extern char 	*opcodeMoveAVectorVector		;
extern char 	*opcodeMoveAStringString		;
extern char 	*opcodeMoveAMatrixMatrix		;
extern char		*opcodeFFromArray				;
extern char		*opcodeFToArray					;
extern char		*opcodeVFromArray				;
extern char		*opcodeVToArray					;
extern char		*opcodeMFromArray				;
extern char		*opcodeMToArray					;
extern char		*opcodeSFromArray				;
extern char		*opcodeSToArray					;
extern char		*opcodeUFFromArray				;
extern char		*opcodeUVFromArray				;
extern char		*opcodeUMFromArray				;
extern char		*opcodeUSFromArray				;

/////////////////////////////////////////////////
// Misc constants
extern char		*constantLoopName				;
extern char		*constantBlockName				;
extern char		*constantShaderMain				;
extern char		*constantReturnValue			;
extern char		*constantBug					;

#endif



