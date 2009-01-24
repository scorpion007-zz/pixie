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
extern	const char	*opcodeIf						;
extern	const char	*opcodeElse						;
extern	const char	*opcodeEndif					;
extern	const char	*opcodeGatherHeader				;
extern	const char	*opcodeGather					;
extern	const char	*opcodeGatherElse				;
extern	const char	*opcodeGatherEnd				;
extern	const char	*opcodeFor						;
extern	const char	*opcodeBeginfor					;
extern	const char	*opcodeEndfor					;
extern	const char	*opcodeIlluminance				;
extern	const char	*opcodeEndIlluminance			;
extern	const char	*opcodeSolar					;
extern	const char	*opcodeEndSolar					;
extern	const char	*opcodeIlluminate				;
extern	const char	*opcodeEndIlluminate			;
extern	const char	*opcodeBreak					;
extern	const char	*opcodeContinue					;
extern	const char	*opcodeReturn					;


/////////////////////////////////////////////////
// Relations

// Equal
extern const char 	*opcodeFloatEqual				;
extern const char 	*opcodeVectorEqual				;
extern const char 	*opcodeStringEqual				;
extern const char 	*opcodeMatrixEqual				;

// Not Equal
extern const char 	*opcodeFloatNotEqual			;
extern const char 	*opcodeVectorNotEqual			;
extern const char 	*opcodeStringNotEqual			;
extern const char 	*opcodeMatrixNotEqual			;

// Less than or equal
extern const char 	*opcodeFloatELess				;
extern const char 	*opcodeVectorELess				;

// Less than
extern const char 	*opcodeFloatLess				;
extern const char 	*opcodeVectorLess				;

// Greater than or equal
extern const char 	*opcodeFloatEGreater			;
extern const char 	*opcodeVectorEGreater			;

// Greater than
extern const char 	*opcodeFloatGreater				;
extern const char 	*opcodeVectorGreater			;

/////////////////////////////////////////////////
// Conversions
extern const char 	*opcodeMatrixFromFloat			;
extern const char 	*opcodeVectorFromFloat			;
extern const char 	*opcodeMatrixFromVector			;

// System conversion
extern const char	*opcodeVectorFrom				;
extern const char	*opcodeColorFrom				;
extern const char	*opcodePointFrom				;
extern const char	*opcodeMatrixFrom				;


/////////////////////////////////////////////////
// Boolean operations
extern const char 	*opcodeAnd						;
extern const char 	*opcodeOr						;
extern const char 	*opcodeXor						;
extern const char 	*opcodeNXor						;
extern const char 	*opcodeNot						;

/////////////////////////////////////////////////
// Unary operations
extern const char 	*opcodeNegFloat					;
extern const char 	*opcodeNegVector				;
extern const char 	*opcodeNegMatrix				;

/////////////////////////////////////////////////
// Binary operations

// Dot and cross products
extern const char 	*opcodeDotProduct				;
extern const char 	*opcodeCrossProduct				;

// Division
extern const char 	*opcodeDivFloatFloat			;
extern const char 	*opcodeDivVectorVector			;
extern const char 	*opcodeDivMatrixMatrix			;

// Multipication
extern const char 	*opcodeMulFloatFloat			;
extern const char 	*opcodeMulVectorVector			;
extern const char 	*opcodeMulMatrixMatrix			;
extern const char 	*opcodeMulMatrixPoint			;
extern const char 	*opcodeMulMatrixNormal			;
extern const char 	*opcodeMulMatrixVector			;
extern const char 	*opcodeMulPointMatrix			;
extern const char 	*opcodeMulNormalMatrix			;
extern const char 	*opcodeMulVectorMatrix			;

// Addition
extern const char 	*opcodeAddFloatFloat			;
extern const char 	*opcodeAddVectorVector			;
extern const char 	*opcodeAddMatrixMatrix			;

// Subtraction
extern const char 	*opcodeSubFloatFloat			;
extern const char 	*opcodeSubVectorVector			;
extern const char 	*opcodeSubMatrixMatrix			;


/////////////////////////////////////////////////
// Data movement operations
extern const char 	*opcodeVUFloat					;
extern const char 	*opcodeVUVector					;
extern const char 	*opcodeVUMatrix					;
extern const char 	*opcodeVUString					;
extern const char 	*opcodeVUBoolean				;

extern const char 	*opcodeMoveFloatFloat			;
extern const char 	*opcodeMoveVectorVector			;
extern const char 	*opcodeMoveStringString			;
extern const char 	*opcodeMoveMatrixMatrix			;
extern const char 	*opcodeMoveAFloatFloat			;
extern const char 	*opcodeMoveAVectorVector		;
extern const char 	*opcodeMoveAStringString		;
extern const char 	*opcodeMoveAMatrixMatrix		;
extern const char	*opcodeFFromArray				;
extern const char	*opcodeFToArray					;
extern const char	*opcodeVFromArray				;
extern const char	*opcodeVToArray					;
extern const char	*opcodeMFromArray				;
extern const char	*opcodeMToArray					;
extern const char	*opcodeSFromArray				;
extern const char	*opcodeSToArray					;
extern const char	*opcodeUFFromArray				;
extern const char	*opcodeUVFromArray				;
extern const char	*opcodeUMFromArray				;
extern const char	*opcodeUSFromArray				;

/////////////////////////////////////////////////
// Misc constants
extern const char		*constantLoopName				;
extern const char		*constantBlockName				;
extern const char		*constantShaderMain				;
extern const char		*constantReturnValue			;
extern const char		*constantBug					;

#endif

