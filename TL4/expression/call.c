#ifndef LUMI_MAINFILE
#define LUMI_MAINFILE "expression/call.c"
#define DEPTH 5
#include "lumi.3.h"
#else

#if LUMI_STAGE == LUMI_TYPEDEFS
static char* _lumi_file10_name = "expression/call.3.lm";
#endif
#define LUMI_FILE_NAME _lumi_file10_name

/* TL4 compiler - Call expression */

/* Function call expression */
#if LUMI_STAGE == LUMI_TYPEDEFS
typedef struct CallExpression CallExpression;
#elif LUMI_STAGE == LUMI_TYPES(2)
struct CallExpression {
  Expression _base;
  Expression* function;
  FunctionArguments* arguments;
  Expression* output;
  Bool is_function_object;
};
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallExpression_parse_new(CallExpression* self, String* ends, SyntaxTreeCode* code_node, Expression** expression, Char* end);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallExpression_parse_new = "CallExpression.parse-new";
#define LUMI_FUNC_NAME _func_name_CallExpression_parse_new
Returncode CallExpression_parse_new(CallExpression* self, String* ends, SyntaxTreeCode* code_node, Expression** expression, Char* end) {
  CallExpression* call_expression = malloc(sizeof(CallExpression));
  if (call_expression == NULL) RAISE(12)
  *call_expression = (CallExpression){CallExpression__dtl, NULL, 0, NULL, NULL, 0, false, false, false, false, false, false, NULL, NULL, NULL, false};
  call_expression->_base._base._dtl = CallExpression__dtl;
  CHECK(13, CallExpression_parse(call_expression, (*expression), code_node, &((*end))) )
  (*expression) = &(call_expression->_base);
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallExpression_parse(CallExpression* self, Expression* function, SyntaxTreeCode* code_node, Char* end);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallExpression_parse = "CallExpression.parse";
#define LUMI_FUNC_NAME _func_name_CallExpression_parse
Returncode CallExpression_parse(CallExpression* self, Expression* function, SyntaxTreeCode* code_node, Char* end) {
  self->function = function;
  self->_base.code_node = code_node;
  CHECK(20, SyntaxTreeNode_set_location(&(self->_base._base)) )
  self->arguments = malloc(sizeof(FunctionArguments));
  if (self->arguments == NULL) RAISE(21)
  *self->arguments = (FunctionArguments){FunctionArguments__dtl, NULL, 0, NULL, NULL};
  self->arguments->_base._dtl = FunctionArguments__dtl;
  CallArgumentFactory* argument_factory = &(CallArgumentFactory){CallArgumentFactory__dtl};
  argument_factory->_base._dtl = CallArgumentFactory__dtl;
  CHECK(23, FunctionArguments_parse(self->arguments, &(argument_factory->_base), false, code_node, &((*end))) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallExpression_analyze(CallExpression* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallExpression_analyze = "CallExpression.analyze";
#define LUMI_FUNC_NAME _func_name_CallExpression_analyze
Returncode CallExpression_analyze(CallExpression* self) {
  CHECK(27, (self->function)->_base._dtl[2](self->function) )
  CHECK(28, (self->arguments)->_base._dtl[2](self->arguments) )
  if (!(NULL != self->function->result_type)) {
    CHECK(30, SyntaxTreeNode_m_syntax_error_msg(&(self->_base._base), &(String){32, 31, "void expression is not callable"}) )
  }
  if (self->function->result_type->type_data != glob->type_func) {
    CHECK(32, SyntaxTreeNode_m_syntax_error(&(self->_base._base), &(String){18, 17, "non callable type"}, self->function->result_type->type_data->name) )
  }
  FunctionArguments* declaration = self->function->result_type->arguments;
  TypeInstance* instance_type = NULL;
  Int bases = 0;
  CHECK(38, (self->function)->_base._dtl[7](self->function, self->arguments, &(instance_type), &(bases), &(self->is_function_object)) )
  TypeInstance* result_type = NULL;
  CHECK(41, FunctionArguments_get_result_type(declaration, &(self->_base.access), &(result_type)) )
  if (!self->_base.is_statement) {
    CHECK(43, TypeInstance_f_new_replace_params(result_type, instance_type, bases, &(self->_base.result_type)) )
    result_type = self->_base.result_type;
  }
  Bool _Bool28;
  CHECK(46, FunctionArguments_check_same_as(self->arguments, declaration, instance_type, bases, &(_Bool28)) )
  if (_Bool28) {
    /* add omitted output */
    CallArgument* output = malloc(sizeof(CallArgument));
    if (output == NULL) RAISE(49)
    *output = (CallArgument){CallArgument__dtl, NULL, 0, 0, false, false, NULL, NULL, NULL, false, false, false};
    output->_base._base._dtl = CallArgument__dtl;
    CHECK(50, SyntaxTreeNode_set_location(&(output->_base._base)) )
    output->_base.is_output = true;
    output->_base.is_native = ((Argument*)(declaration->outputs->last->item))->is_native;
    TypeInstance* _TypeInstance29;
    CHECK(53, (((Argument*)(declaration->outputs->last->item)))->_base._dtl[7](((Argument*)(declaration->outputs->last->item)), &(_TypeInstance29)) )
    output->is_generic = _TypeInstance29->type_data == glob->type_generic;
    output->_base.access = ((Argument*)(declaration->outputs->last->item))->access;
    SymbolExpression* _SymbolExpression30;
    CHECK(57, Expression_add_aux_variable(&(self->_base), ((Argument*)(declaration->outputs->last->item))->access, false, result_type, &(_SymbolExpression30)) )
    output->value = &(_SymbolExpression30->_base);
    self->output = output->value;
    CHECK(62, List_add(self->arguments->outputs, &(output->_base)) )
  }
  else {
    if (NULL != self->_base.result_type) {
      CHECK(64, FunctionArguments_get_output(self->arguments, &(self->output)) )
    }
  }
  self->_base.assignable =  NULL !=  self->_base.result_type;
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallExpression_write_preactions(CallExpression* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallExpression_write_preactions = "CallExpression.write-preactions";
#define LUMI_FUNC_NAME _func_name_CallExpression_write_preactions
Returncode CallExpression_write_preactions(CallExpression* self) {
  CHECK(68, (self->function)->_base._dtl[9](self->function) )
  if (self->is_function_object) {
    CHECK(70, write(&(String){5, 4, "if ("}) )
    CHECK(71, Expression_write_as_top(self->function) )
    CHECK(72, write(&(String){11, 10, " == NULL) "}) )
    CHECK(73, SyntaxTreeNode_write_raise(&(self->_base._base), &(String){22, 21, "empty function called"}) )
    CHECK(74, SyntaxTreeCode_write_spaces(self->_base.code_node) )
  }
  CHECK(75, FunctionArguments_write_preactions(self->arguments) )
  if (!self->_base.is_statement) {
    CHECK(77, CallExpression_write_func_call(self) )
    CHECK(78, SyntaxTreeCode_write_spaces(self->_base.code_node) )
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallExpression_write(CallExpression* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallExpression_write = "CallExpression.write";
#define LUMI_FUNC_NAME _func_name_CallExpression_write
Returncode CallExpression_write(CallExpression* self) {
  if (self->_base.is_statement) {
    CHECK(82, CallExpression_write_func_call(self) )
  }
  else {
    if (NULL != self->output) {
      CHECK(84, (self->output)->_base._dtl[4](self->output) )
    }
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallExpression_write_func_call(CallExpression* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallExpression_write_func_call = "CallExpression.write-func-call";
#define LUMI_FUNC_NAME _func_name_CallExpression_write_func_call
Returncode CallExpression_write_func_call(CallExpression* self) {
  CHECK(87, SyntaxTreeNode_write_call(&(self->_base._base)) )
  CHECK(88, (self->function)->_base._dtl[4](self->function) )
  CHECK(89, (self->arguments)->_base._dtl[5](self->arguments) )
  CHECK(90, write(&(String){4, 3, " )\n"}) )
  CHECK(91, FunctionArguments_write_postactions(self->arguments) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
extern Func CallExpression__dtl[];
#endif
#if LUMI_STAGE == LUMI_FUNCTIONS
Func CallExpression__dtl[] = {(void*)Expression_get_parent_type, (void*)SyntaxTreeNode_link_types, (void*)CallExpression_analyze, (void*)SyntaxTreeNode_m_order_constants, (void*)CallExpression_write, (void*)Expression_write_dynamic, (void*)Expression_write_refman, (void*)Expression_analyze_call, (void*)Expression_analyze_mock, (void*)CallExpression_write_preactions};
#endif


/* Function argument call */
#if LUMI_STAGE == LUMI_TYPEDEFS
typedef struct CallArgument CallArgument;
#elif LUMI_STAGE == LUMI_TYPES(2)
struct CallArgument {
  Argument _base;
  Expression* value;
  Expression* assignee;
  SyntaxTreeCode* code_node;
  Bool is_down_cast;
  Bool is_dynamic;
  Bool is_generic;
};
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallArgument_parse_value(CallArgument* self, SyntaxTreeCode* code_node, Char* end);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallArgument_parse_value = "CallArgument.parse-value";
#define LUMI_FUNC_NAME _func_name_CallArgument_parse_value
Returncode CallArgument_parse_value(CallArgument* self, SyntaxTreeCode* code_node, Char* end) {
  self->code_node = code_node;
  CHECK(105, parse_new_expression(&(String){3, 2, ",)"}, code_node, &(self->value), &((*end))) )
  if ((*end) != ',' && (*end) != ')') {
    CHECK(108, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base), &(String){25, 24, "expected \",\" or \")\", got"}, (*end)) )
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallArgument_analyze(CallArgument* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallArgument_analyze = "CallArgument.analyze";
#define LUMI_FUNC_NAME _func_name_CallArgument_analyze
Returncode CallArgument_analyze(CallArgument* self) {
  CHECK(111, (self->value)->_base._dtl[2](self->value) )
  if (self->_base.is_output &&  ! self->value->assignable) {
    CHECK(113, SyntaxTreeNode_m_syntax_error_msg(&(self->_base._base), &(String){27, 26, "non assignable call output"}) )
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallArgument_check_same_type_as(CallArgument* self, TypeInstance* type_instance, TypeInstance* instance_type, Int bases);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallArgument_check_same_type_as = "CallArgument.check-same-type-as";
#define LUMI_FUNC_NAME _func_name_CallArgument_check_same_type_as
Returncode CallArgument_check_same_type_as(CallArgument* self, TypeInstance* type_instance, TypeInstance* instance_type, Int bases) {
  if (self->_base.access == ACCESS_OWNER && self->value->access != ACCESS_OWNER) {
    if ((self->value->access) < 0 || (self->value->access) >= (glob->access_names)->length) RAISE(120)
    CHECK(120, SyntaxTreeNode_m_syntax_error(&(self->_base._base), &(String){43, 42, "assigning into an owner a non-owner access"}, (&(((String*)((glob->access_names)->values))[self->value->access]))) )
  }
  if (self->_base.is_output && self->_base.access != self->value->access) {
    if ((self->_base.access) < 0 || (self->_base.access) >= (glob->access_names)->length) RAISE(124)
    if ((self->value->access) < 0 || (self->value->access) >= (glob->access_names)->length) RAISE(124)
    CHECK(124, SyntaxTreeNode_m_syntax_error2(&(self->_base._base), &(String){22, 21, "assigning into access"}, (&(((String*)((glob->access_names)->values))[self->_base.access])), &(String){15, 14, "invalid access"}, (&(((String*)((glob->access_names)->values))[self->value->access]))) )
  }
  
  TypeInstance* real_type = NULL;
  CHECK(131, TypeInstance_f_new_replace_params(type_instance, instance_type, bases, &(real_type)) )
  if (self->_base.is_output) {
    Int _Int31;
    CHECK(134, TypeInstance_check_assign_to(real_type, self->_base.access, self->value->result_type, self->value->access, &(self->_base._base), &(_Int31)) )
    self->is_down_cast = _Int31 > 0;
  }
  else {
    CHECK(140, TypeInstance_check_assign_from(real_type, self->_base.access, &(self->_base._base), &(self->value), &(self->assignee)) )
  }
  self->is_dynamic = real_type->type_data->is_dynamic;
  self->is_generic = type_instance->type_data == glob->type_generic;
  free(real_type);
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallArgument_get_output(CallArgument* self, Expression** output);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallArgument_get_output = "CallArgument.get-output";
#define LUMI_FUNC_NAME _func_name_CallArgument_get_output
Returncode CallArgument_get_output(CallArgument* self, Expression** output) {
  (*output) = self->value;
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallArgument_write_preactions(CallArgument* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallArgument_write_preactions = "CallArgument.write-preactions";
#define LUMI_FUNC_NAME _func_name_CallArgument_write_preactions
Returncode CallArgument_write_preactions(CallArgument* self) {
  CHECK(150, (self->value)->_base._dtl[9](self->value) )
  if (self->is_down_cast) {
    /* if (`value` != NULL) RAISE(`line-num`) */
    CHECK(153, write(&(String){5, 4, "if ("}) )
    CHECK(154, (self->value)->_base._dtl[4](self->value) )
    CHECK(155, write(&(String){11, 10, " != NULL) "}) )
    CHECK(156, SyntaxTreeNode_write_raise(&(self->_base._base), &(String){46, 45, "non empty base class given as output argument"}) )
    CHECK(157, SyntaxTreeCode_write_spaces(self->code_node) )
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallArgument_write(CallArgument* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallArgument_write = "CallArgument.write";
#define LUMI_FUNC_NAME _func_name_CallArgument_write
Returncode CallArgument_write(CallArgument* self) {
  /* [&(]`value`[)][, [&(]`value`_Refman[)]][, [&(]`value`_Dynamic[)]] */
  if (self->_base.is_output) {
    if (self->is_down_cast || self->is_generic) {
      CHECK(163, write(&(String){8, 7, "(void*)"}) )
    }
    CHECK(164, write(&(String){3, 2, "&("}) )
  }
  CHECK(165, (self->value)->_base._dtl[4](self->value) )
  if (self->_base.is_output) {
    CHECK(167, write(&(String){2, 1, ")"}) )
  }
  
  if (!self->value->result_type->type_data->is_primitive &&  ! self->_base.is_native) {
    CHECK(170, write(&(String){3, 2, ", "}) )
    if (self->_base.is_output) {
      CHECK(172, write(&(String){3, 2, "&("}) )
    }
    CHECK(173, (self->value)->_base._dtl[6](self->value) )
    if (self->_base.is_output) {
      CHECK(175, write(&(String){2, 1, ")"}) )
    }
  }
  
  if (self->is_dynamic &&  ! self->_base.is_native) {
    CHECK(178, write(&(String){3, 2, ", "}) )
    if ((self->_base.is_output && self->is_down_cast) || self->is_generic) {
      CHECK(180, write(&(String){8, 7, "(void*)"}) )
    }
    if (self->_base.is_output) {
      CHECK(182, write(&(String){3, 2, "&("}) )
    }
    CHECK(183, (self->value)->_base._dtl[5](self->value) )
    if (self->_base.is_output) {
      CHECK(185, write(&(String){2, 1, ")"}) )
    }
  }
  else {
    if (self->is_generic) {
      CHECK(187, write(&(String){3, 2, ", "}) )
      if (self->_base.is_output) {
        CHECK(189, write(&(String){14, 13, "&dynamic_Void"}) )
      }
      else {
        if (self->value->result_type->type_data == glob->type_empty) {
          CHECK(191, write(&(String){5, 4, "NULL"}) )
        }
        else {
          CHECK(193, write(&(String){2, 1, "&"}) )
          CHECK(194, TypeData_write_cname(self->value->result_type->type_data) )
          CHECK(195, write(&(String){9, 8, "_dynamic"}) )
        }
      }
    }
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallArgument_write_postactions(CallArgument* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallArgument_write_postactions = "CallArgument.write-postactions";
#define LUMI_FUNC_NAME _func_name_CallArgument_write_postactions
Returncode CallArgument_write_postactions(CallArgument* self) {
  if (self->_base.access == ACCESS_OWNER &&  ! self->_base.is_output && self->value->result_type->type_data != glob->type_empty) {
    CHECK(200, Expression_write_assign_null(self->assignee) )
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
extern Func CallArgument__dtl[];
#endif
#if LUMI_STAGE == LUMI_FUNCTIONS
Func CallArgument__dtl[] = {(void*)SyntaxTreeNode_get_parent_type, (void*)SyntaxTreeNode_link_types, (void*)CallArgument_analyze, (void*)SyntaxTreeNode_m_order_constants, (void*)CallArgument_write, (void*)Argument_copy_new, (void*)CallArgument_parse_value, (void*)Argument_get_type_instance, (void*)CallArgument_check_same_type_as, (void*)Argument_get_variable, (void*)CallArgument_get_output, (void*)CallArgument_write_preactions, (void*)CallArgument_write_postactions};
#endif


#if LUMI_STAGE == LUMI_TYPEDEFS
typedef struct CallArgumentFactory CallArgumentFactory;
#elif LUMI_STAGE == LUMI_TYPES(1)
struct CallArgumentFactory {
  ArgumentFactory _base;
};
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode CallArgumentFactory_m_new_argument(CallArgumentFactory* self, Argument** new_argument);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_CallArgumentFactory_m_new_argument = "CallArgumentFactory.m-new-argument";
#define LUMI_FUNC_NAME _func_name_CallArgumentFactory_m_new_argument
Returncode CallArgumentFactory_m_new_argument(CallArgumentFactory* self, Argument** new_argument) {
  CallArgument* _CallArgument32 = malloc(sizeof(CallArgument));
  if (_CallArgument32 == NULL) RAISE(205)
  *_CallArgument32 = (CallArgument){CallArgument__dtl, NULL, 0, 0, false, false, NULL, NULL, NULL, false, false, false};
  _CallArgument32->_base._base._dtl = CallArgument__dtl;
  (*new_argument) = &(_CallArgument32->_base);
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
extern Func CallArgumentFactory__dtl[];
#endif
#if LUMI_STAGE == LUMI_FUNCTIONS
Func CallArgumentFactory__dtl[] = {(void*)CallArgumentFactory_m_new_argument};
#endif

#undef LUMI_FILE_NAME

#ifndef LUMI_INCLUDES
#define LUMI_INCLUDES
#include "tl4-compiler.c"
#include "global/argument.c"
#include "global/common.c"
#include "global/file-io.c"
#include "global/global.c"
#include "global/list.c"
#include "global/map.c"
#include "global/type-instance.c"
#include "expression/base-type.c"
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
#include "syntax-tree/node.c"
#include "syntax-tree/root.c"
#include "statement/enum.c"
#include "statement/error.c"
#include "statement/for.c"
#include "statement/function.c"
#include "statement/native.c"
#include "statement/test.c"
#include "statement/type.c"
#include "statement/variable.c"
#if LUMI_STAGE == LUMI_TYPES(1)
#undef LUMI_STAGE
#define LUMI_STAGE LUMI_TYPES(2)
#elif LUMI_STAGE == LUMI_TYPES(2)
#undef LUMI_STAGE
#define LUMI_STAGE LUMI_TYPES(3)
#elif LUMI_STAGE == LUMI_TYPES(3)
#undef LUMI_STAGE
#define LUMI_STAGE LUMI_TYPES(4)
#elif LUMI_STAGE == LUMI_TYPES(4)
#undef LUMI_STAGE
#define LUMI_STAGE LUMI_TYPES(5)
#endif
#undef LUMI_INCLUDES
#endif

#endif
