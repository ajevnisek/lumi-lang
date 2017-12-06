#ifndef MR_MAINFILE
#define MR_MAINFILE "syntax-tree/type.c"
#define DEPTH 5
#include "mr.3.h"
#else

#if MR_STAGE == MR_TYPEDEFS
static char* _mr_file23_name = "syntax-tree/type.3.mr";
#endif
#define MR_FILE_NAME _mr_file23_name

/* MR4 compiler - Syntax tree type */

/* Type node in the syntax tree  */
#if MR_STAGE == MR_TYPEDEFS
typedef struct TypeData TypeData;
#elif MR_STAGE == MR_TYPES(3)
struct TypeData {
  SyntaxTreeNamespace _base;
  String* name;
  String* base_type_name;
  TypeData* base_type;
  NameMap* dynamic_base_methods;
  SyntaxTreeConstructor* constructor;
  Bool is_primitive;
  Bool is_dynamic;
  Bool is_ordered;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_parse_new(TypeData* self, Bool is_dynamic, Char* end, TypeData** new_node);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_parse_new = "TypeData.parse-new";
#define MR_FUNC_NAME _func_name_TypeData_parse_new
Returncode TypeData_parse_new(TypeData* self, Bool is_dynamic, Char* end, TypeData** new_node) {
  (*new_node) = malloc(sizeof(TypeData));
  if ((*new_node) == NULL) RAISE(16)
  *(*new_node) = (TypeData){TypeData__dtl, NULL, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, false, false, false};
  (*new_node)->_base._base._base._dtl = TypeData__dtl;
  CHECK(17, TypeData_parse((*new_node), is_dynamic, &((*end))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_parse(TypeData* self, Bool is_dynamic, Char* end);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_parse = "TypeData.parse";
#define MR_FUNC_NAME _func_name_TypeData_parse
Returncode TypeData_parse(TypeData* self, Bool is_dynamic, Char* end) {
  self->is_dynamic = is_dynamic;
  CHECK(21, SyntaxTreeNode_set_location(&(self->_base._base._base)) )
  CHECK(22, read_new(&(String){2, 1, "("}, &(self->name), &((*end))) )
  Bool _Bool109;
  CHECK(23, f_is_legal_name(self->name, true, &(_Bool109)) )
  if (!_Bool109) {
    CHECK(24, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){18, 17, "illegal type name"}, self->name) )
  }
  TypeData* _TypeData110;
  CHECK(25, NameMap_find(glob->type_map, self->name, (void**)&(_TypeData110)) )
  if (NULL != _TypeData110) {
    CHECK(26, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){21, 20, "redefinition of type"}, self->name) )
  }
  CHECK(27, Global_add_type(glob, self) )
  if ((*end) == '(') {
    CHECK(29, read_new(&(String){2, 1, ")"}, &(self->base_type_name), &((*end))) )
    if ((*end) != ')') {
      CHECK(31, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base._base), &(String){34, 33, "expected \")\" after base type, got"}, (*end)) )
    }
    CHECK(33, read_c(&((*end))) )
  }
  self->_base._base.indentation_spaces = 2;
  CHECK(35, SyntaxTreeBranch_parse_block_children(&(self->_base._base), self, NULL, &((*end))) )
  self->_base._base.indentation_spaces = 0;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_parse_child(TypeData* self, String* keyword, Char* end);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_parse_child = "TypeData.parse-child";
#define MR_FUNC_NAME _func_name_TypeData_parse_child
Returncode TypeData_parse_child(TypeData* self, String* keyword, Char* end) {
  Bool _Bool111;
  CHECK(39, SyntaxTreeNamespace_parse_if_function(&(self->_base), keyword, self, &((*end)), &(_Bool111)) )
  if (_Bool111) {
    return OK;
  }
  
  Bool _Bool112;
  CHECK(42, String_equal(keyword, &(String){4, 3, "new"}, &(_Bool112)) )
  if (_Bool112) {
    if ((*end) != '(') {
      CHECK(44, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base._base), &(String){30, 29, "expected \"(\" after \"new\", got"}, (*end)) )
    }
    if (NULL != self->constructor) {
      CHECK(47, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){37, 36, "constructor already defined for type"}, self->name) )
    }
    SyntaxTreeConstructor* constructor = NULL;
    CHECK(50, SyntaxTreeConstructor_parse_new(NULL, self, &((*end)), &(constructor)) )
    self->constructor = constructor;
    CHECK(52, List_add(self->_base.functions, &(constructor->_base)) )
    
  }
  else {
    CHECK(55, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){16, 15, "unknown keyword"}, keyword) )
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_m_is_same(TypeData* self, TypeData* other, Bool* is_same);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_m_is_same = "TypeData.m-is-same";
#define MR_FUNC_NAME _func_name_TypeData_m_is_same
Returncode TypeData_m_is_same(TypeData* self, TypeData* other, Bool* is_same) {
  (*is_same) = self == other || ((self == &(glob->type_int->_base) || self == &(glob->type_char->_base)) && (other == &(glob->type_int->_base) || other == &(glob->type_char->_base)));
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_m_new_type_instance(TypeData* self, TypeInstance** type_instance);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_m_new_type_instance = "TypeData.m-new-type-instance";
#define MR_FUNC_NAME _func_name_TypeData_m_new_type_instance
Returncode TypeData_m_new_type_instance(TypeData* self, TypeInstance** type_instance) {
  (*type_instance) = malloc(sizeof(TypeInstance));
  if ((*type_instance) == NULL) RAISE(63)
  *(*type_instance) = (TypeInstance){NULL, NULL, NULL, NULL, NULL, NULL};
  (*type_instance)->type_data = self;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_find_field(TypeData* self, String* name, SyntaxTreeVariable** field, Int* bases);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_find_field = "TypeData.find-field";
#define MR_FUNC_NAME _func_name_TypeData_find_field
Returncode TypeData_find_field(TypeData* self, String* name, SyntaxTreeVariable** field, Int* bases) {
  TypeData* type_data = self;
  (*bases) = 0;
  while (true) {
    if (!(NULL != type_data)) break;
    ListNode* child = type_data->_base._base.variables->first;
    while (true) {
      if (!(NULL != child)) break;
      Bool _Bool113;
      CHECK(75, String_equal(((SyntaxTreeVariable*)(child->item))->name, name, &(_Bool113)) )
      if (_Bool113) {
        (*field) = ((SyntaxTreeVariable*)(child->item));
        return OK;
      }
      child = child->next;
    }
    type_data = type_data->base_type;
    (*bases) += 1;
  }
  (*field) = NULL;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_find_meth(TypeData* self, String* name, SyntaxTreeFunction** method, Int* bases);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_find_meth = "TypeData.find-meth";
#define MR_FUNC_NAME _func_name_TypeData_find_meth
Returncode TypeData_find_meth(TypeData* self, String* name, SyntaxTreeFunction** method, Int* bases) {
  TypeData* type_data = self;
  (*bases) = 0;
  while (true) {
    if (!(NULL != type_data)) break;
    ListNode* child = type_data->_base.functions->first;
    while (true) {
      if (!(NULL != child)) break;
      Bool _Bool114;
      CHECK(92, String_equal(((SyntaxTreeFunction*)(child->item))->name, name, &(_Bool114)) )
      if (_Bool114) {
        (*method) = ((SyntaxTreeFunction*)(child->item));
        return OK;
      }
      child = child->next;
    }
    type_data = type_data->base_type;
    (*bases) += 1;
  }
  (*method) = NULL;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_m_order_bases(TypeData* self, List* ordered_list);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_m_order_bases = "TypeData.m-order-bases";
#define MR_FUNC_NAME _func_name_TypeData_m_order_bases
Returncode TypeData_m_order_bases(TypeData* self, List* ordered_list) {
  if (self->is_ordered) {
    return OK;
  }
  /* init `self.base-type` */
  if (NULL != self->base_type_name) {
    CHECK(105, SyntaxTreeNode_find_type(&(self->_base._base._base), self->base_type_name, &(self->base_type)) )
    CHECK(106, TypeData_m_order_bases(self->base_type, ordered_list) )
  }
  CHECK(107, List_add(ordered_list, self) )
  /* init `self.dynamic-base-methods` and test override methods */
  if (self->is_dynamic) {
    self->dynamic_base_methods = malloc(sizeof(NameMap));
    if (self->dynamic_base_methods == NULL) RAISE(110)
    *self->dynamic_base_methods = (NameMap){NULL, NULL};
  }
  ListNode* child = self->_base.functions->first;
  while (true) {
    if (!(NULL != child)) break;
    SyntaxTreeFunction* method = NULL;
    Int bases = 0;
    CHECK(116, TypeData_find_meth(self->base_type, ((SyntaxTreeFunction*)(child->item))->name, &(method), &(bases)) )
    if (NULL != method) {
      CHECK(118, SyntaxTreeFunction_m_compare(((SyntaxTreeFunction*)(child->item)), method) )
      if (((SyntaxTreeFunction*)(child->item))->is_dynamic) {
        ((SyntaxTreeFunction*)(child->item))->dynamic_base_method = method->dynamic_base_method;
        ((SyntaxTreeFunction*)(child->item))->dynamic_base_count = method->dynamic_base_count + bases + 1;
      }
    }
    else {
      if (((SyntaxTreeFunction*)(child->item))->is_dynamic) {
        ((SyntaxTreeFunction*)(child->item))->dynamic_base_method = ((SyntaxTreeFunction*)(child->item));
        CHECK(124, NameMap_add(self->dynamic_base_methods, ((SyntaxTreeFunction*)(child->item))->name, child->item) )
      }
    }
    child = child->next;
  }
  self->is_ordered = true;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_analyze(TypeData* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_analyze = "TypeData.analyze";
#define MR_FUNC_NAME _func_name_TypeData_analyze
Returncode TypeData_analyze(TypeData* self) {
  Bool _Bool115;
  CHECK(129, List_m_is_empty(self->_base._base.variables, &(_Bool115)) )
  if (!(NULL != self->base_type) && _Bool115) {
    CHECK(130, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){20, 19, "type with no fields"}, self->name) )
  }
  if (self->is_dynamic &&  ! (NULL != self->base_type && self->base_type->is_dynamic)) {
    ListNode* node = self->_base.functions->first;
    while (true) {
      if (!(NULL != node)) {
        CHECK(135, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){30, 29, "class with no dynamic methods"}, self->name) )
      }
      if (!(!((SyntaxTreeFunction*)(node->item))->is_dynamic)) break;
      node = node->next;
    }
  }
  CHECK(139, SyntaxTreeNamespace_analyze(&(self->_base)) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_write_declaration(TypeData* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_write_declaration = "TypeData.write-declaration";
#define MR_FUNC_NAME _func_name_TypeData_write_declaration
Returncode TypeData_write_declaration(TypeData* self) {
  /* typedef struct `name` `name`; */
  /* typedef struct `name`_Dynamic `name`_Dynamic; */
  CHECK(144, write(&(String){17, 16, "\ntypedef struct "}) )
  CHECK(145, write_cname(self->name) )
  CHECK(146, write(&(String){2, 1, " "}) )
  CHECK(147, write_cname(self->name) )
  CHECK(148, write(&(String){3, 2, ";\n"}) )
  if (self->is_dynamic) {
    CHECK(150, write(&(String){17, 16, "\ntypedef struct "}) )
    CHECK(151, write_cname(self->name) )
    CHECK(152, write(&(String){10, 9, "_Dynamic "}) )
    CHECK(153, write_cname(self->name) )
    CHECK(154, write(&(String){11, 10, "_Dynamic;\n"}) )
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_write(TypeData* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_write = "TypeData.write";
#define MR_FUNC_NAME _func_name_TypeData_write
Returncode TypeData_write(TypeData* self) {
  /* struct `name` { */
  /*   `variables...` */
  /* }; */
  /* struct `name`_Dynamic { */
  /*   `dynamic-function-pointers...` */
  /* }; */
  CHECK(163, write(&(String){9, 8, "\nstruct "}) )
  CHECK(164, write_cname(self->name) )
  CHECK(165, write(&(String){4, 3, " {\n"}) )
  self->_base._base.indentation_spaces = 2;
  if (NULL != self->base_type) {
    CHECK(168, SyntaxTreeBranch_write_spaces(&(self->_base._base)) )
    CHECK(169, write_cname(self->base_type->name) )
    CHECK(170, write(&(String){9, 8, " _base;\n"}) )
  }
  CHECK(171, SyntaxTreeNode_write_children(&(self->_base._base._base), self->_base._base.variables) )
  CHECK(172, write(&(String){4, 3, "};\n"}) )
  if (self->is_dynamic) {
    CHECK(174, write(&(String){9, 8, "\nstruct "}) )
    CHECK(175, write_cname(self->name) )
    CHECK(176, write(&(String){12, 11, "_Dynamic {\n"}) )
    if (NULL != self->base_type && self->base_type->is_dynamic) {
      CHECK(178, SyntaxTreeBranch_write_spaces(&(self->_base._base)) )
      CHECK(179, write_cname(self->base_type->name) )
      CHECK(180, write(&(String){17, 16, "_Dynamic _base;\n"}) )
    }
    NameMapNode* child = self->dynamic_base_methods->first;
    while (true) {
      if (!(NULL != child)) break;
      CHECK(184, SyntaxTreeBranch_write_spaces(&(self->_base._base)) )
      CHECK(185, SyntaxTreeFunction_write_pointer(((SyntaxTreeFunction*)(child->value))) )
      CHECK(186, write(&(String){3, 2, ";\n"}) )
      child = child->next;
    }
    CHECK(188, write(&(String){4, 3, "};\n"}) )
  }
  self->_base._base.indentation_spaces = 0;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_write_methods_declaration(TypeData* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_write_methods_declaration = "TypeData.write-methods-declaration";
#define MR_FUNC_NAME _func_name_TypeData_write_methods_declaration
Returncode TypeData_write_methods_declaration(TypeData* self) {
  CHECK(192, SyntaxTreeNamespace_write_functions_declaration(&(self->_base)) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_write_global(TypeData* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_write_global = "TypeData.write-global";
#define MR_FUNC_NAME _func_name_TypeData_write_global
Returncode TypeData_write_global(TypeData* self) {
  /* `name`_Dynamic `name`_dynamic = {`dynamic-functions...`}; */
  if (self->is_dynamic) {
    CHECK(197, write(&(String){2, 1, "\n"}) )
    CHECK(198, write_cname(self->name) )
    CHECK(199, write(&(String){10, 9, "_Dynamic "}) )
    CHECK(200, write_cname(self->name) )
    CHECK(201, write(&(String){12, 11, "_dynamic = "}) )
    CHECK(202, TypeData_write_dynamic_init(self, self) )
    CHECK(203, write(&(String){3, 2, ";\n"}) )
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_write_dynamic_init(TypeData* self, TypeData* type_data);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_write_dynamic_init = "TypeData.write-dynamic-init";
#define MR_FUNC_NAME _func_name_TypeData_write_dynamic_init
Returncode TypeData_write_dynamic_init(TypeData* self, TypeData* type_data) {
  CHECK(206, write(&(String){2, 1, "{"}) )
  Bool not_first = NULL != type_data->base_type && type_data->base_type->is_dynamic;
  if (not_first) {
    CHECK(209, TypeData_write_dynamic_init(self, type_data->base_type) )
  }
  NameMapNode* child = type_data->dynamic_base_methods->first;
  while (true) {
    if (!(NULL != child)) break;
    SyntaxTreeFunction* method = NULL;
    Int _Int116;
    CHECK(214, TypeData_find_meth(self, ((SyntaxTreeFunction*)(child->value))->name, &(method), &(_Int116)) )
    if (not_first) {
      CHECK(216, write(&(String){3, 2, ", "}) )
    }
    if (method != ((SyntaxTreeFunction*)(child->value))) {
      CHECK(218, write(&(String){7, 6, "(Func)"}) )
    }
    CHECK(219, write_cname(method->parent_type->name) )
    CHECK(220, write(&(String){2, 1, "_"}) )
    CHECK(221, write_cname(method->name) )
    not_first = true;
    child = child->next;
  }
  CHECK(224, write(&(String){2, 1, "}"}) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_write_methods_body(TypeData* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_write_methods_body = "TypeData.write-methods-body";
#define MR_FUNC_NAME _func_name_TypeData_write_methods_body
Returncode TypeData_write_methods_body(TypeData* self) {
  CHECK(227, SyntaxTreeNode_write_children(&(self->_base._base._base), self->_base.functions) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeData_write_me(TypeData* self, TypeWriter* type_writer);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeData_write_me = "TypeData.write-me";
#define MR_FUNC_NAME _func_name_TypeData_write_me
Returncode TypeData_write_me(TypeData* self, TypeWriter* type_writer) {
  CHECK(230, (type_writer)->_dtl[0](type_writer, self) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func TypeData__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func TypeData__dtl[] = {(void*)SyntaxTreeNamespace_link_types, (void*)TypeData_analyze, (void*)TypeData_write, (void*)TypeData_parse_child, (void*)SyntaxTreeBranch_find_variable, (void*)TypeData_write_me};
#endif


#if MR_STAGE == MR_TYPEDEFS
typedef struct TypeWriter TypeWriter;
#elif MR_STAGE == MR_TYPES(0)
struct TypeWriter {
  Func* _dtl;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeWriter_write(TypeWriter* self, TypeData* type_data);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeWriter_write = "TypeWriter.write";
#define MR_FUNC_NAME _func_name_TypeWriter_write
Returncode TypeWriter_write(TypeWriter* self, TypeData* type_data) {
  RAISE(235)
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func TypeWriter__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func TypeWriter__dtl[] = {(void*)TypeWriter_write};
#endif

#if MR_STAGE == MR_TYPEDEFS
typedef struct TypeDeclarationWriter TypeDeclarationWriter;
#elif MR_STAGE == MR_TYPES(1)
struct TypeDeclarationWriter {
  TypeWriter _base;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeDeclarationWriter_write(TypeDeclarationWriter* self, TypeData* type_data);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeDeclarationWriter_write = "TypeDeclarationWriter.write";
#define MR_FUNC_NAME _func_name_TypeDeclarationWriter_write
Returncode TypeDeclarationWriter_write(TypeDeclarationWriter* self, TypeData* type_data) {
  CHECK(239, TypeData_write_declaration(type_data) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func TypeDeclarationWriter__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func TypeDeclarationWriter__dtl[] = {(void*)TypeDeclarationWriter_write};
#endif

#if MR_STAGE == MR_TYPEDEFS
typedef struct TypeMethodsDeclarationWriter TypeMethodsDeclarationWriter;
#elif MR_STAGE == MR_TYPES(1)
struct TypeMethodsDeclarationWriter {
  TypeWriter _base;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeMethodsDeclarationWriter_write(TypeMethodsDeclarationWriter* self, TypeData* type_data);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeMethodsDeclarationWriter_write = "TypeMethodsDeclarationWriter.write";
#define MR_FUNC_NAME _func_name_TypeMethodsDeclarationWriter_write
Returncode TypeMethodsDeclarationWriter_write(TypeMethodsDeclarationWriter* self, TypeData* type_data) {
  CHECK(243, TypeData_write_methods_declaration(type_data) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func TypeMethodsDeclarationWriter__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func TypeMethodsDeclarationWriter__dtl[] = {(void*)TypeMethodsDeclarationWriter_write};
#endif

#if MR_STAGE == MR_TYPEDEFS
typedef struct TypeGlobalWriter TypeGlobalWriter;
#elif MR_STAGE == MR_TYPES(1)
struct TypeGlobalWriter {
  TypeWriter _base;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeGlobalWriter_write(TypeGlobalWriter* self, TypeData* type_data);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeGlobalWriter_write = "TypeGlobalWriter.write";
#define MR_FUNC_NAME _func_name_TypeGlobalWriter_write
Returncode TypeGlobalWriter_write(TypeGlobalWriter* self, TypeData* type_data) {
  CHECK(247, TypeData_write_global(type_data) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func TypeGlobalWriter__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func TypeGlobalWriter__dtl[] = {(void*)TypeGlobalWriter_write};
#endif

#if MR_STAGE == MR_TYPEDEFS
typedef struct TypeMethodsBodyWriter TypeMethodsBodyWriter;
#elif MR_STAGE == MR_TYPES(1)
struct TypeMethodsBodyWriter {
  TypeWriter _base;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TypeMethodsBodyWriter_write(TypeMethodsBodyWriter* self, TypeData* type_data);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TypeMethodsBodyWriter_write = "TypeMethodsBodyWriter.write";
#define MR_FUNC_NAME _func_name_TypeMethodsBodyWriter_write
Returncode TypeMethodsBodyWriter_write(TypeMethodsBodyWriter* self, TypeData* type_data) {
  CHECK(251, TypeData_write_methods_body(type_data) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func TypeMethodsBodyWriter__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func TypeMethodsBodyWriter__dtl[] = {(void*)TypeMethodsBodyWriter_write};
#endif

#undef MR_FILE_NAME

#ifndef MR_INCLUDES
#define MR_INCLUDES
#include "global/argument.c"
#include "global/common.c"
#include "global/file-io.c"
#include "global/global.c"
#include "global/list.c"
#include "global/map.c"
#include "expression/base-type.c"
#include "expression/call.c"
#include "expression/constant.c"
#include "expression/container.c"
#include "expression/expression.c"
#include "expression/initialize.c"
#include "expression/slice.c"
#include "expression/symbol.c"
#include "syntax-tree/block.c"
#include "syntax-tree/branch.c"
#include "syntax-tree/code.c"
#include "syntax-tree/code-flow.c"
#include "syntax-tree/function.c"
#include "syntax-tree/node.c"
#include "syntax-tree/root.c"
#include "syntax-tree/test.c"
#include "syntax-tree/type-instance.c"
#include "syntax-tree/variable.c"
#include "mr4-compiler.c"
#if MR_STAGE == MR_TYPES(1)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(2)
#elif MR_STAGE == MR_TYPES(2)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(3)
#elif MR_STAGE == MR_TYPES(3)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(4)
#elif MR_STAGE == MR_TYPES(4)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(5)
#endif
#undef MR_INCLUDES
#endif

#endif