#ifndef LUMI_MAINFILE
#define LUMI_MAINFILE "expression/initialize.c"
#define DEPTH 5
#include "lumi.3.h"
#else

#if LUMI_STAGE == LUMI_TYPEDEFS
static char* _lumi_file14_name = "expression/initialize.3.lm";
#endif
#define LUMI_FILE_NAME _lumi_file14_name

/* TL4 compiler - Initialization expression */

#if LUMI_STAGE == LUMI_TYPEDEFS
typedef struct InitExpression InitExpression;
#elif LUMI_STAGE == LUMI_TYPES(3)
struct InitExpression {
  ModuleTypeExpression _base;
  FunctionArguments* arguments;
  SymbolExpression* symbol;
  SyntaxTreeFunction* constructor;
  Expression* value;
};
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode InitExpression_parse(InitExpression* self, TypeInstance* result_type, Expression* module_expression, SyntaxTreeCode* code_node, Char* end);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_InitExpression_parse = "InitExpression.parse";
#define LUMI_FUNC_NAME _func_name_InitExpression_parse
Returncode InitExpression_parse(InitExpression* self, TypeInstance* result_type, Expression* module_expression, SyntaxTreeCode* code_node, Char* end) {
  self->_base._base.code_node = code_node;
  self->_base._base.result_type = result_type;
  CHECK(16, SyntaxTreeNode_set_location(&(self->_base._base._base)) )
  self->_base.module_expression = module_expression;
  self->arguments = malloc(sizeof(FunctionArguments));
  if (self->arguments == NULL) RAISE(18)
  *self->arguments = (FunctionArguments){FunctionArguments__dtl, NULL, 0, NULL, NULL};
  self->arguments->_base._dtl = FunctionArguments__dtl;
  if ((*end) == '(') {
    CallArgumentFactory* argument_factory = &(CallArgumentFactory){CallArgumentFactory__dtl};
    argument_factory->_base._dtl = CallArgumentFactory__dtl;
    CHECK(21, FunctionArguments_parse(self->arguments, &(argument_factory->_base), false, code_node, &((*end))) )
  }
  else {
    CHECK(24, FunctionArguments_init(self->arguments) )
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode InitExpression_analyze(InitExpression* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_InitExpression_analyze = "InitExpression.analyze";
#define LUMI_FUNC_NAME _func_name_InitExpression_analyze
Returncode InitExpression_analyze(InitExpression* self) {
  CHECK(27, ModuleTypeExpression_analyze_type_instance(&(self->_base), self->_base._base.result_type) )
  
  CHECK(29, (self->arguments)->_base._dtl[2](self->arguments) )
  if (NULL != self->symbol) {
    CHECK(31, TypeInstance_analyze(self->symbol->_base.result_type, &(self->_base._base._base)) )
  }
  else {
    CHECK(33, Expression_add_aux_variable(&(self->_base._base), ACCESS_OWNER, true, self->_base._base.result_type, &(self->symbol)) )
  }
  self->_base._base.access = self->symbol->_base.access;
  
  if (self->symbol->variable->access == ACCESS_OWNER && self->symbol->variable->is_create && self->_base._base.result_type->type_data->is_primitive) {
    CHECK(41, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){37, 36, "dynamic allocation of primitive type"}, self->_base._base.result_type->type_data->name) )
  }
  
  if (!self->_base._base.result_type->type_data->is_primitive && self->symbol->variable->is_create) {
    CHECK(47, TypeInstance_check_sequence(self->_base._base.result_type, &(self->_base._base._base)) )
    if (self->_base._base.result_type->type_data == glob->type_array && ((TypeInstance*)(self->_base._base.result_type->parameters->first->item))->type_data == glob->type_generic) {
      CHECK(50, SyntaxTreeNode_m_syntax_error_msg(&(self->_base._base._base), &(String){28, 27, "cannot create generic array"}) )
    }
    Int _Int50;
    CHECK(51, TypeData_find_meth(self->_base._base.result_type->type_data, &(String){4, 3, "new"}, &(self->constructor), &(_Int50)) )
    if (!(NULL != self->arguments->parameters->first) &&  ! (NULL != self->arguments->outputs->first) && (!(NULL != self->constructor) || self->_base._base.result_type->type_data == glob->type_string)) {
      self->constructor = NULL;
    }
    else {
      if (NULL != self->constructor) {
        CallArgument* self_param = malloc(sizeof(CallArgument));
        if (self_param == NULL) RAISE(57)
        *self_param = (CallArgument){CallArgument__dtl, NULL, 0, 0, false, false, NULL, NULL, NULL, false, false, false};
        self_param->_base._base._dtl = CallArgument__dtl;
        CHECK(58, SyntaxTreeNode_set_location(&(self_param->_base._base)) )
        self_param->_base.access = ((Argument*)(self->constructor->arguments->parameters->first->item))->access;
        self_param->code_node = self->_base._base.code_node;
        self_param->value = &(self->symbol->_base);
        CHECK(63, List_prepend(self->arguments->parameters, &(self_param->_base)) )
        Bool _Bool51;
        CHECK(64, FunctionArguments_check_same_as(self->arguments, self->constructor->arguments, self->_base._base.result_type, 0, &(_Bool51)) )
      }
      else {
        CHECK(67, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){23, 22, "no contructor for type"}, self->_base._base.result_type->type_data->name) )
      }
    }
    
  }
  else {
    if (NULL != self->arguments->parameters->first) {
      if (NULL != self->arguments->parameters->first->next ||  NULL !=  self->arguments->outputs->first) {
        CHECK(73, SyntaxTreeNode_m_syntax_error_msg(&(self->_base._base._base), &(String){43, 42, "only one initialization parameter expected"}) )
      }
      Argument* param = self->arguments->parameters->first->item;
      CHECK(76, (param)->_base._dtl[8](param, self->_base._base.result_type, NULL, 0) )
      if (self->_base._base.result_type->type_data->is_primitive && param->access != ACCESS_COPY) {
        if ((param->access) < 0 || (param->access) >= (glob->access_names)->length) RAISE(78)
        CHECK(78, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){49, 48, "access should be \"copy\" for primitive types, got"}, (&(((String*)((glob->access_names)->values))[param->access]))) )
      }
      else {
        if (!self->_base._base.result_type->type_data->is_primitive && self->_base._base.access != param->access) {
          if ((self->_base._base.access) < 0 || (self->_base._base.access) >= (glob->access_names)->length) RAISE(83)
          if ((param->access) < 0 || (param->access) >= (glob->access_names)->length) RAISE(83)
          CHECK(83, SyntaxTreeNode_m_syntax_error2(&(self->_base._base._base), &(String){22, 21, "assigning into access"}, (&(((String*)((glob->access_names)->values))[self->_base._base.access])), &(String){15, 14, "invalid access"}, (&(((String*)((glob->access_names)->values))[param->access]))) )
        }
      }
    }
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode InitExpression_write_allocation(InitExpression* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_InitExpression_write_allocation = "InitExpression.write-allocation";
#define LUMI_FUNC_NAME _func_name_InitExpression_write_allocation
Returncode InitExpression_write_allocation(InitExpression* self) {
  CHECK(90, FunctionArguments_write_preactions(self->arguments) )
  if (self->_base._base.result_type->type_data == glob->type_array || self->_base._base.result_type->type_data == glob->type_string) {
    CHECK(93, (self->_base._base.result_type->length)->_base._dtl[9](self->_base._base.result_type->length) )
  }
  if (self->_base._base.result_type->type_data == glob->type_array && ((TypeInstance*)(self->_base._base.result_type->parameters->first->item))->type_data == glob->type_string) {
    CHECK(96, (((TypeInstance*)(self->_base._base.result_type->parameters->first->item))->length)->_base._dtl[9](((TypeInstance*)(self->_base._base.result_type->parameters->first->item))->length) )
  }
  
  if (self->symbol->variable->access == ACCESS_VAR) {
    CHECK(99, InitExpression_write_var_init(self) )
  }
  else {
    CHECK(101, InitExpression_write_new_init(self) )
  }
  
  CHECK(103, Expression_write_refman_init(&(self->_base._base), self->symbol) )
  
  if (NULL != self->constructor) {
    CHECK(106, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
    CHECK(107, write(&(String){12, 11, "LUMI_err = "}) )
    CHECK(108, SyntaxTreeFunction_write_cname(self->constructor) )
    CHECK(109, SyntaxTreeCode_write_call(self->_base._base.code_node, self->arguments) )
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode InitExpression_write_var_init(InitExpression* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_InitExpression_write_var_init = "InitExpression.write-var-init";
#define LUMI_FUNC_NAME _func_name_InitExpression_write_var_init
Returncode InitExpression_write_var_init(InitExpression* self) {
  CHECK(112, Expression_write_init_var_ref(&(self->_base._base), self->symbol) )
  
  if (self->_base._base.result_type->type_data == glob->type_array || self->_base._base.result_type->type_data == glob->type_string) {
    /* `symbol`_Var.values = `symbol`_Values; */
    CHECK(117, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
    CHECK(118, (self->symbol)->_base._base._dtl[4](self->symbol) )
    CHECK(119, write(&(String){15, 14, "_Var.values = "}) )
    CHECK(120, (self->symbol)->_base._base._dtl[4](self->symbol) )
    CHECK(121, write(&(String){10, 9, "_Values;\n"}) )
    if (self->_base._base.result_type->type_data == glob->type_array && ((TypeInstance*)(self->_base._base.result_type->parameters->first->item))->type_data == glob->type_string) {
      /* LUMI_set_var_string_array( */
      /*    `array-length`, `string-length`, `name`, `name`_Chars); */
      CHECK(126, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
      CHECK(127, write(&(String){27, 26, "LUMI_set_var_string_array("}) )
      CHECK(128, (self->_base._base.result_type->length)->_base._dtl[4](self->_base._base.result_type->length) )
      CHECK(129, write(&(String){3, 2, ", "}) )
      CHECK(130, (((TypeInstance*)(self->_base._base.result_type->parameters->first->item))->length)->_base._dtl[4](((TypeInstance*)(self->_base._base.result_type->parameters->first->item))->length) )
      CHECK(131, write(&(String){3, 2, ", "}) )
      CHECK(132, (self->symbol)->_base._base._dtl[4](self->symbol) )
      CHECK(133, write(&(String){3, 2, ", "}) )
      CHECK(134, (self->symbol)->_base._base._dtl[4](self->symbol) )
      CHECK(135, write(&(String){10, 9, "_Chars);\n"}) )
    }
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode InitExpression_write_new_init(InitExpression* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_InitExpression_write_new_init = "InitExpression.write-new-init";
#define LUMI_FUNC_NAME _func_name_InitExpression_write_new_init
Returncode InitExpression_write_new_init(InitExpression* self) {
  /* `symbol` = ... */
  CHECK(139, (self->symbol)->_base._base._dtl[4](self->symbol) )
  CHECK(140, write(&(String){4, 3, " = "}) )
  
  if (self->_base._base.result_type->type_data == glob->type_array) {
    if (((TypeInstance*)(self->_base._base.result_type->parameters->first->item))->type_data == glob->type_string) {
      /* LUMI_new_string_array(`length`, `string-length`); */
      CHECK(145, write(&(String){23, 22, "LUMI_new_string_array("}) )
      CHECK(146, (self->_base._base.result_type->length)->_base._dtl[4](self->_base._base.result_type->length) )
      CHECK(147, write(&(String){3, 2, ", "}) )
      CHECK(148, (((TypeInstance*)(self->_base._base.result_type->parameters->first->item))->length)->_base._dtl[4](((TypeInstance*)(self->_base._base.result_type->parameters->first->item))->length) )
      
    }
    else {
      /* LUMI_new_array(`length`, sizeof(`SubType`)); */
      CHECK(152, write(&(String){16, 15, "LUMI_new_array("}) )
      CHECK(153, (self->_base._base.result_type->length)->_base._dtl[4](self->_base._base.result_type->length) )
      CHECK(154, write(&(String){10, 9, ", sizeof("}) )
      CHECK(155, TypeData_write_cname(((TypeInstance*)(self->_base._base.result_type->parameters->first->item))->type_data) )
      CHECK(156, write(&(String){2, 1, ")"}) )
      
    }
  }
  else {
    if (self->_base._base.result_type->type_data == glob->type_string) {
      /* LUMI_new_string(`length`); */
      CHECK(160, write(&(String){17, 16, "LUMI_new_string("}) )
      CHECK(161, (self->_base._base.result_type->length)->_base._dtl[4](self->_base._base.result_type->length) )
      
    }
    else {
      /* LUMI_alloc(sizeof(`type`)); */
      CHECK(165, write(&(String){19, 18, "LUMI_alloc(sizeof("}) )
      CHECK(166, TypeData_write_cname(self->_base._base.result_type->type_data) )
      CHECK(167, write(&(String){2, 1, ")"}) )
    }
  }
  
  CHECK(169, write(&(String){4, 3, ");\n"}) )
  
  /* if (`symbol` == NULL) raise(`line-num`) */
  CHECK(172, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
  CHECK(173, write(&(String){5, 4, "if ("}) )
  CHECK(174, (self->symbol)->_base._base._dtl[4](self->symbol) )
  CHECK(175, write(&(String){11, 10, " == NULL) "}) )
  CHECK(176, SyntaxTreeNode_write_raise(&(self->_base._base._base), &(String){50, 49, "insufficient memory for object dynamic allocation"}) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode InitExpression_write_assign(InitExpression* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_InitExpression_write_assign = "InitExpression.write-assign";
#define LUMI_FUNC_NAME _func_name_InitExpression_write_assign
Returncode InitExpression_write_assign(InitExpression* self) {
  /* `name` = `value`; */
  Expression* value = NULL;
  CHECK(181, (((Argument*)(self->arguments->parameters->first->item)))->_base._dtl[10](((Argument*)(self->arguments->parameters->first->item)), &(value)) )
  CHECK(182, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
  CHECK(183, (value)->_base._dtl[9](value) )
  CHECK(184, (self->symbol)->_base._base._dtl[4](self->symbol) )
  CHECK(185, write(&(String){4, 3, " = "}) )
  CHECK(186, (value)->_base._dtl[4](value) )
  CHECK(187, write(&(String){3, 2, ";\n"}) )
  
  if (!self->_base._base.result_type->type_data->is_primitive) {
    /* `name`_Refman = `value`_Refman; */
    /* LUMI_inc_ref(`name`_Refman); */
    CHECK(192, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
    CHECK(193, (self->symbol)->_base._base._dtl[4](self->symbol) )
    CHECK(194, write(&(String){11, 10, "_Refman = "}) )
    CHECK(195, (value)->_base._dtl[6](value) )
    CHECK(196, write(&(String){3, 2, ";\n"}) )
    if (self->_base._base.access != ACCESS_OWNER) {
      CHECK(198, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
      CHECK(199, write(&(String){14, 13, "LUMI_inc_ref("}) )
      CHECK(200, (self->symbol)->_base._base._dtl[4](self->symbol) )
      CHECK(201, write(&(String){11, 10, "_Refman);\n"}) )
    }
  }
  
  if (self->_base._base.result_type->type_data->is_dynamic) {
    /* `name`_Dynamic = `Type`_Dynamic; */
    CHECK(205, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
    CHECK(206, (self->symbol)->_base._base._dtl[4](self->symbol) )
    CHECK(207, write(&(String){12, 11, "_Dynamic = "}) )
    if (value->is_generic_cast) {
      value->top = false;
    }
    CHECK(210, (value)->_base._dtl[5](value) )
    value->top = true;
    CHECK(212, write(&(String){3, 2, ";\n"}) )
  }
  
  CHECK(214, FunctionArguments_write_postactions(self->arguments) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode InitExpression_write_preactions(InitExpression* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_InitExpression_write_preactions = "InitExpression.write-preactions";
#define LUMI_FUNC_NAME _func_name_InitExpression_write_preactions
Returncode InitExpression_write_preactions(InitExpression* self) {
  CHECK(217, InitExpression_write_allocation(self) )
  CHECK(218, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode InitExpression_write(InitExpression* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_InitExpression_write = "InitExpression.write";
#define LUMI_FUNC_NAME _func_name_InitExpression_write
Returncode InitExpression_write(InitExpression* self) {
  if (self->_base._base.is_statement) {
    if (!self->_base._base.result_type->type_data->is_primitive && self->symbol->variable->is_create) {
      CHECK(224, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
      CHECK(225, InitExpression_write_allocation(self) )
    }
    else {
      if (NULL != self->arguments->parameters->first) {
        CHECK(227, InitExpression_write_assign(self) )
      }
    }
  }
  else {
    CHECK(229, (self->symbol)->_base._base._dtl[4](self->symbol) )
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
extern Func InitExpression__dtl[];
#endif
#if LUMI_STAGE == LUMI_FUNCTIONS
Func InitExpression__dtl[] = {(void*)Expression_get_parent_type, (void*)SyntaxTreeNode_link_types, (void*)InitExpression_analyze, (void*)SyntaxTreeNode_m_order_constants, (void*)InitExpression_write, (void*)Expression_write_dynamic, (void*)Expression_write_refman, (void*)Expression_analyze_call, (void*)Expression_analyze_mock, (void*)InitExpression_write_preactions};
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
#include "expression/call.c"
#include "expression/constant.c"
#include "expression/container.c"
#include "expression/expression.c"
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