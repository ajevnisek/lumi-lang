
typedef struct Test Test;
typedef struct Ta Ta;
typedef struct Ta_Dynamic Ta_Dynamic;
typedef struct Tb Tb;
typedef struct Tb_Dynamic Tb_Dynamic;
typedef struct Tc Tc;
typedef struct Tc_Dynamic Tc_Dynamic;
struct Test {
  Int num;
  Test* t;
  RefManager* t_Refman;
  Returncode (*fun)(void);
};
struct Ta {
  Test _base;
  Int numa;
};
struct Ta_Dynamic {
  Returncode (*dyn)(Ta* self, RefManager* self_Refman, Ta_Dynamic* self_Dynamic);
};
struct Tb {
  Ta _base;
  Int numb;
};
struct Tb_Dynamic {
  Ta_Dynamic _base;
};
struct Tc {
  Tb _base;
  Int numc;
};
struct Tc_Dynamic {
  Tb_Dynamic _base;
};
Returncode Test_new(Test* self, RefManager* self_Refman, Int num);
Returncode Test_meth(Test* self, RefManager* self_Refman);
Returncode Ta_metha(Ta* self, RefManager* self_Refman, Ta_Dynamic* self_Dynamic);
Returncode Ta_dyn(Ta* self, RefManager* self_Refman, Ta_Dynamic* self_Dynamic);
Returncode Tb_methb(Tb* self, RefManager* self_Refman, Tb_Dynamic* self_Dynamic);
Returncode Tb_dyn(Tb* self, RefManager* self_Refman, Tb_Dynamic* self_Dynamic);
Returncode Tc_methc(Tc* self, RefManager* self_Refman, Tc_Dynamic* self_Dynamic);
Returncode Tc_dyn(Tc* self, RefManager* self_Refman, Tc_Dynamic* self_Dynamic);
Ta_Dynamic Ta_dynamic = {Ta_dyn};
Tb_Dynamic Tb_dynamic = {{(Func)Tb_dyn}};
Tc_Dynamic Tc_dynamic = {{{(Func)Tc_dyn}}};
Returncode fun0(void);
Returncode fun1(Int x, String* s, RefManager* s_Refman, String* o, RefManager* o_Refman);
Returncode fun2(String** s, RefManager** s_Refman, Int* x);
Returncode fun3(Int x, String** s, RefManager** s_Refman);
Returncode fun4(Int x);
Returncode fun5(Int x, Int* y);
Returncode fun6(Int x, Int y, Int* n, Int* m);
Returncode fun7(Tb** tb, RefManager** tb_Refman, Tb_Dynamic** tb_Dynamic);
Returncode mock(Int i, Char c, Bool b, String* str, RefManager* str_Refman, Array* arr, RefManager* arr_Refman, File* fobj, RefManager* fobj_Refman, Test* t, RefManager* t_Refman, Ta* ta, RefManager* ta_Refman, Ta_Dynamic* ta_Dynamic, Tb* tb, RefManager* tb_Refman, Tb_Dynamic* tb_Dynamic, Tc* tc, RefManager* tc_Refman, Tc_Dynamic* tc_Dynamic, String** so, RefManager** so_Refman, Int* io, Test** to, RefManager** to_Refman, Tc** tco, RefManager** tco_Refman, Tc_Dynamic** tco_Dynamic);
Returncode Test_new(Test* self, RefManager* self_Refman, Int num) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode Test_meth(Test* self, RefManager* self_Refman) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode Ta_metha(Ta* self, RefManager* self_Refman, Ta_Dynamic* self_Dynamic) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode Ta_dyn(Ta* self, RefManager* self_Refman, Ta_Dynamic* self_Dynamic) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode Tb_methb(Tb* self, RefManager* self_Refman, Tb_Dynamic* self_Dynamic) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode Tb_dyn(Tb* self, RefManager* self_Refman, Tb_Dynamic* self_Dynamic) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode Tc_methc(Tc* self, RefManager* self_Refman, Tc_Dynamic* self_Dynamic) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode Tc_dyn(Tc* self, RefManager* self_Refman, Tc_Dynamic* self_Dynamic) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode fun0(void) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode fun1(Int x, String* s, RefManager* s_Refman, String* o, RefManager* o_Refman) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode fun2(String** s, RefManager** s_Refman, Int* x) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode fun3(Int x, String** s, RefManager** s_Refman) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode fun4(Int x) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode fun5(Int x, Int* y) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode fun6(Int x, Int y, Int* n, Int* m) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode fun7(Tb** tb, RefManager** tb_Refman, Tb_Dynamic** tb_Dynamic) {
  Returncode MR_err = OK;
MR_cleanup:
  return MR_err;
}
Returncode mock(Int i, Char c, Bool b, String* str, RefManager* str_Refman, Array* arr, RefManager* arr_Refman, File* fobj, RefManager* fobj_Refman, Test* t, RefManager* t_Refman, Ta* ta, RefManager* ta_Refman, Ta_Dynamic* ta_Dynamic, Tb* tb, RefManager* tb_Refman, Tb_Dynamic* tb_Dynamic, Tc* tc, RefManager* tc_Refman, Tc_Dynamic* tc_Dynamic, String** so, RefManager** so_Refman, Int* io, Test** to, RefManager** to_Refman, Tc** tco, RefManager** tco_Refman, Tc_Dynamic** tco_Dynamic) {
  Returncode MR_err = OK;
  