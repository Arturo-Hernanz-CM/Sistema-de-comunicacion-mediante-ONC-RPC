#ifndef TUPLAS_SVC_H
#define TUPLAS_SVC_H

#include "tuplas.h"     // Este sí es generado por rpcgen y contiene struct peticion, etc.
#include <rpc/rpc.h>    // Necesario para tipos como SVCXPRT y svc_req

void tuplas_1(struct svc_req *, SVCXPRT *);

#endif