/* File : example.i */
%module RVO3DSimulator

namespace RVO
{
%{
#include "RVOSimulator.h"
%}
}
/* Let's just grab the original header file here */
%include "RVOSimulator.h"



