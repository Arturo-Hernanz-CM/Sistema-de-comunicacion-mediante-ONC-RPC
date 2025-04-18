struct coord {
  int x;
  int y;
};

struct peticion {
  int key;
  string value1<256>;
  int N_value2;
  double value2[32];
  struct coord value3;
  int operacion;
};

program TUPLAS {
  version TUPLASVER {
    int DESTROY(void) = 0;
    int SETVALUE(peticion p) = 1;
    peticion GETVALUE(int) = 2;
    int MODIFYVALUE(peticion p) = 3;
    int DELETEKEY(int) = 4;
    int EXIST(int) = 5;
  } = 1;
} = 99;