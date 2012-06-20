#pragma once

struct CPosition
{
    float X, Y, Z;
};

struct CColor
{
    float Red, Green, Blue;
};

struct CVertex
{
    // Position - position of this vertex.
    //
    CPosition* Position;

    // Color - color of this vertex.
    //
    CColor* Color;

    // Opacity - opacity of this vertex.
    //
    CColor* Opacity;
};

struct CQuad
{
    // Vertices - vertices that make up the quad.
    //
    CVertex Vertices[4];
};

struct CMovingQuad
{
    // NumSamples - number of motion samples.
    //
    int NumSamples;

    // Samples - quad snapshots in time along motion trajectory.
    //
    CQuad* QuadSamples;
};