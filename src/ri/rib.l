%{
// Saves information about a rib file
typedef struct TRibFile {
	int				ribLineno;
	const char		*ribFile;
	YY_BUFFER_STATE	ribState;
	TRibFile		*next;
} TRibFile;

static	TRibFile	*ribStack	=	NULL;

// Tell flex how to define yylex for pure parser
#undef YY_DECL
#define YY_DECL int yylex( YYSTYPE *yylval )

#ifdef HAVE_ZLIB

// Overwrite the YYinput so that it uses libz
#undef YY_INPUT
#define YY_INPUT(buf, retval, maxlen)	if ( (retval = gzread(ribin,buf,maxlen)) < 0) 			\
											YY_FATAL_ERROR( "input in flex scanner failed" );

#endif

%}
%option never-interactive
%option noyywrap 
%%
Declare												return RIB_DECLARE;
FrameBegin											return RIB_FRAME_BEGIN;
FrameEnd											return RIB_FRAME_END;
WorldBegin											return RIB_WORLD_BEGIN;
WorldEnd											return RIB_WORLD_END;
Format												return RIB_FORMAT;
FrameAspectRatio									return RIB_FRAME_ASPECT_RATIO;
ScreenWindow										return RIB_SCREEN_WINDOW;
CropWindow											return RIB_CROP_WINDOW;
Projection											return RIB_PROJECTION;
Clipping											return RIB_CLIPPING;
ClippingPlane										return RIB_CLIPPING_PLANE;
DepthOfField										return RIB_DEPTH_OF_FIELD;
Shutter												return RIB_SHUTTER;
PixelVariance										return RIB_PIXEL_VARIANCE;
PixelSamples										return RIB_PIXEL_SAMPLES;
PixelFilter											return RIB_PIXEL_FILTER;
Exposure											return RIB_EXPOSURE;
Imager												return RIB_IMAGER;
Quantize											return RIB_QUANTIZE;
Display												return RIB_DISPLAY;
DisplayChannel										return RIB_DISPLAYCHANNEL;
Hider												return RIB_HIDER;
ColorSamples										return RIB_COLOR_SAMPLES;
RelativeDetail										return RIB_RELATIVE_DETAIL;
Option												return RIB_OPTION;

AttributeBegin										return RIB_ATTRIBUTE_BEGIN;
AttributeEnd										return RIB_ATTRIBUTE_END;
Color												return RIB_COLOR;
Opacity												return RIB_OPACITY;
TextureCoordinates									return RIB_TEXTURE_COORDINATES;
LightSource											return RIB_LIGHT_SOURCE;
AreaLightSource										return RIB_AREA_LIGHT_SOURCE;
Illuminate											return RIB_ILLUMINATE;
Surface												return RIB_SURFACE;
Atmosphere											return RIB_ATMOSPHERE;
Interior											return RIB_INTERIOR;
Exterior											return RIB_EXTERIOR;
ShadingRate											return RIB_SHADING_RATE;
ShadingInterpolation								return RIB_SHADING_INTERPOLATION;
Matte												return RIB_MATTE;
Bound												return RIB_BOUND;
Detail												return RIB_DETAIL;
DetailRange											return RIB_DETAIL_RANGE;
GeometricApproximation								return RIB_GEOMETRIC_APPROXIMATION;
GeometricRepresentation								return RIB_GEOMETRIC_REPRESENTATION;
Orientation											return RIB_ORIENTATION;
ReverseOrientation									return RIB_REVERSE_ORIENTATION;
Sides												return RIB_SIDES;

Identity											return RIB_IDENTITY;
Transform											return RIB_TRANSFORM;
ConcatTransform										return RIB_CONCAT_TRANSFORM;
Perspective											return RIB_PERSPECTIVE;
Translate											return RIB_TRANSLATE;
Rotate												return RIB_ROTATE;
Scale												return RIB_SCALE;
Skew												return RIB_SKEW;
Deformation											return RIB_DEFORMATION;
Displacement										return RIB_DISPLACEMENT;
CoordinateSystem									return RIB_COORDINATE_SYSTEM;
CoordSysTransform									return RIB_COORDINATE_SYS_TRANSFORM;

TransformBegin										return RIB_TRANSFORM_BEGIN;
TransformEnd										return RIB_TRANSFORM_END;

Attribute											return RIB_ATTRIBUTE;

Polygon												return RIB_POLYGON;
GeneralPolygon										return RIB_GENERAL_POLYGON;
PointsPolygons										return RIB_POINTS_POLYGONS;
PointsGeneralPolygons								return RIB_POINTS_GENERAL_POLYGONS;
Basis												return RIB_BASIS;
Patch												return RIB_PATCH;
PatchMesh											return RIB_PATCH_MESH;
NuPatch												return RIB_NU_PATCH;
TrimCurve											return RIB_TRIM_CURVE;

Sphere												return RIB_SPHERE;
Cone												return RIB_CONE;
Cylinder											return RIB_CYLINDER;
Hyperboloid											return RIB_HYPERBOLOID;
Paraboloid											return RIB_PARABOLOID;
Disk												return RIB_DISK;
Torus												return RIB_TORUS;
Curves												return RIB_CURVES;
Points												return RIB_POINTS;
SubdivisionMesh										return RIB_SUBDIVISION_MESH;
Blobby												return RIB_BLOBBY;
Geometry											return RIB_GEOMETRY;

Procedural											return RIB_PROCEDURAL;

SolidBegin											return RIB_SOLID_BEGIN;
SolidEnd											return RIB_SOLID_END;

ObjectBegin											return RIB_OBJECT_BEGIN;
ObjectEnd											return RIB_OBJECT_END;

ObjectInstance										return RIB_OBJECT_INSTANCE;

MotionBegin											return RIB_MOTION_BEGIN;
MotionEnd											return RIB_MOTION_END;

MakeTexture											return RIB_MAKE_TEXTURE;
MakeBrickMap										return RIB_MAKE_BRICKMAP;
MakeBump											return RIB_MAKE_BUMP;
MakeLatLongEnvironment								return RIB_MAKE_LAT_LONG_ENVIRONMENT;
MakeCubeFaceEnvironment								return RIB_MAKE_CUBE_FACE_ENVIRONMENT;
MakeShadow											return RIB_MAKE_SHADOW;

ArchiveRecord										return RIB_ARCHIVE_RECORD;

ArchiveBegin										return RIB_ARCHIVE_BEGIN;
ArchiveEnd											return RIB_ARCHIVE_END;

Resource											return RIB_RESOURCE;
ResourceBegin										return RIB_RESOURCE_BEGIN;
ResourceEnd											return RIB_RESOURCE_END;

IfBegin												return RIB_IFBEGIN;
IfEnd												return RIB_IFEND;
ElseIf												return RIB_ELSEIF;
Else												return RIB_ELSE;


ReadArchive[ \t]*\"[^\"]*\"							{
														char			fileName[256];
														char			*start	=	strchr(ribtext,'\"');
														char			location[OS_MAX_PATH_LENGTH];
														COptions		*options;

														assert(start != NULL);

														strcpy(fileName,start+1);

														fileName[strlen(fileName)-1]	=	'\0';

														options		=	CRenderer::context->getOptions();

														if (CRenderer::locateFile(location,fileName,options->archivePath) == TRUE) {
															FILE	*in;

															info(CODE_RESOLUTION,"\"%s\" -> \"%s\"\n",fileName,location);

#ifdef HAVE_ZLIB
															in = (FILE *) gzopen( location, "r" );
#else
															in = fopen( location, "r" );
#endif

															if (in != NULL) {
																TRibFile	*newFile	=	new TRibFile;

																newFile->ribLineno		=	ribLineno;
																newFile->ribState		=	YY_CURRENT_BUFFER;
																newFile->ribFile		=	ribFile;
																newFile->next			=	ribStack;
																ribStack				=	newFile;

																ribFile					=	strdup(fileName);
																ribLineno				=	1;																
																ribin					=	in;
																rib_switch_to_buffer(rib_create_buffer( ribin, YY_BUF_SIZE ) );
																BEGIN(INITIAL);
															} else {
																error(CODE_NOFILE,"Failed to open \"%s\"\n",location);
															}
														} else {
															error(CODE_NOFILE,"Failed to find \"%s(.rib)\"\n",fileName);
														}
													}

ErrorHandler										return RIB_ERROR_HANDLER;

version												return RIB_VERSION;
[0-9]+\.[0-9]+\.[0-9]+								return RIB_VERSION_STRING;

\[													return RIB_ARRAY_BEGIN;
\]													return RIB_ARRAY_END;

\"[^\"]*\"											{   riblval->string	=	rstrdup(ribtext+1,CRenderer::globalMemory);	riblval->string[strlen(riblval->string)-1] = '\0'; return RIB_TEXT;}
[+-]?([0-9]+|([0-9]*(\.[0-9]+)?)([eE][+-]?[0-9]+)?)	{	/*sscanf(ribtext,"%f",&riblval->real);*/ riblval->real = (float) atof(ribtext); return RIB_FLOAT; }
[+-]?([0-9]+|([0-9]+(\.[0-9]*)?)([eE][+-]?[0-9]+)?)	{	/*sscanf(ribtext,"%f",&riblval->real);*/ riblval->real = (float) atof(ribtext); return RIB_FLOAT; }

[\t ]												;
#\!.*												{	riblval->string	=	rstrdup(ribtext+2,CRenderer::globalMemory);	return RIB_STRUCTURE_COMMENT;	}
#.*													;
\n													{	ribLineno++; }
<<EOF>>												{
														if (ribStack == NULL) {
															yyterminate();
														} else 	{
															TRibFile	*nextFile	=	ribStack->next;
															rib_delete_buffer( YY_CURRENT_BUFFER );
#ifdef HAVE_ZLIB
															gzclose(ribin);
#else
															fclose(ribin);
#endif
															free((char *) ribFile);
															rib_switch_to_buffer(ribStack->ribState);
															ribLineno	=	ribStack->ribLineno;
															ribFile		=	ribStack->ribFile;
															delete ribStack;
															ribStack	=	nextFile;
														}
													}
\377												{	// Terminate parsing for a runprogram
														if (ribStack == NULL) {
															yyterminate();
														} else 	{
															TRibFile	*nextFile	=	ribStack->next;
															rib_delete_buffer( YY_CURRENT_BUFFER );
															
#ifdef HAVE_ZLIB
															gzclose(ribin);
#else
															fclose(ribin);
#endif

															free((char *) ribFile);
															rib_switch_to_buffer(ribStack->ribState);
															ribLineno	=	ribStack->ribLineno;
															ribFile		=	ribStack->ribFile;
															delete ribStack;
															ribStack	=	nextFile;
														}
													}
%%

