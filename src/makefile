# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -g -fPIC -pthread

# Librerías para el linker
LDLIBS = -lpthread -ldl

CPPFLAGS += -D_REENTRANT


# Detectar sistema operativo
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	CFLAGS += -I/usr/include/tirpc
	LDLIBS += -ltirpc
	LDLIBS += -lnsl
endif

ifeq ($(UNAME_S),Darwin)
	CFLAGS += -I/opt/homebrew/Cellar/libtirpc/1.3.6/include
	LDLIBS += -L/opt/homebrew/Cellar/libtirpc/1.3.6/lib -ltirpc
endif

# Archivos fuente RPC generados
RPC_X = tuplas.x
RPC_GEN_SRCS = tuplas_clnt.c tuplas_svc.c tuplas_xdr.c
RPC_GEN_HDR = tuplas.h

# Archivos fuente
SRCS_SERVER = servidor-rpc.c claves.c tuplas_svc.c tuplas_xdr.c
SRCS_PROXY = proxy-rpc.c tuplas_clnt.c tuplas_xdr.c
SRCS_CLIENT0 = clientes/app-cliente-0.c
SRCS_CLIENT1 = clientes/app-cliente-1.c
SRCS_CLIENT2 = clientes/app-cliente-2.c
SRCS_CLIENT3 = clientes/app-cliente-3.c
SRCS_CLIENT4 = clientes/app-cliente-4.c
SRCS_CLIENT5 = clientes/app-cliente-5.c
SRCS_CLIENT6 = clientes/app-cliente-6.c

# Archivos objeto
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_PROXY = $(SRCS_PROXY:.c=.o)


servidor-rpc.o: tuplas_svc.h
# Librería compartida
LIB_NAME = libclaves.so

# Ejecutables
TARGET_SERVER = servidor
TARGET_CLIENTS = app-cliente-0 app-cliente-1 app-cliente-2 app-cliente-3 app-cliente-4 app-cliente-5 app-cliente-6

# Regla por defecto
all: $(RPC_GEN_SRCS) $(TARGET_SERVER) $(LIB_NAME) $(TARGET_CLIENTS)

# Compilar el servidor
$(TARGET_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# Crear la librería compartida
$(LIB_NAME): $(OBJS_PROXY)
	$(CC) -shared -o $@ $^

# Compilar clientes
$(TARGET_CLIENTS): %: clientes/%.c $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $< -L. -lclaves $(LDLIBS)

# Regla para compilar .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar todo
clean: rpcgen-clean
	rm -f $(OBJS_SERVER) $(OBJS_PROXY) $(TARGET_SERVER) $(TARGET_CLIENTS) $(LIB_NAME)