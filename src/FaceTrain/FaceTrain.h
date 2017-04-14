
#if !defined(AFX_FACETRAIN_H__1F47DC80_0539_460B_A98D_2089E71E5974__INCLUDED_)
#define AFX_FACETRAIN_H__1F47DC80_0539_460B_A98D_2089E71E5974__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"


#endif // !defined(AFX_FACETRAIN_H__1F47DC80_0539_460B_A98D_2089E71E5974__INCLUDED_)


// For Face Recog
#include<set>
#include<string>
#define USERNAME_LENGTH 20
extern std::set<std::string> usernames;

// For bpnn

// Change BPNN_TYPE for Task1 or Task2
// BPNN_TYPE 0 Task1
// BPNN_TYPE 1 Task2

#define BPNN_TYPE 1

#if BPNN_TYPE

#define BPNN_N_OUT 5
#define BPNN_N_HIDDEN 6
#define BPNN_ETA 0.2
#define BPNN_MOMENTUM 0.2
#define BPNN_EPOCHS 20
#define BPNN_SEED 940823

#else

#define BPNN_N_OUT 2
#define BPNN_N_HIDDEN 8
#define BPNN_ETA 0.2
#define BPNN_MOMENTUM 0.2
#define BPNN_EPOCHS 100
#define BPNN_SEED 940823

#endif