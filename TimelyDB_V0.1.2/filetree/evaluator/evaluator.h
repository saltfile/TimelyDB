#ifndef DTIMEDB_EVALUATOR_H
#define DTIMEDB_EVALUATOR_H

#include "../ast/header.h"
#include "../ast/header.h"
#include "environment.h"

#include <memory>

    /**
     * 递归求值生成 执行计划树
     *
     */
    class Evaluator
    {
    public:
        bool is_error(const std::shared_ptr<ExecutionPlanNode> & obj);

        std::shared_ptr<ExecutionPlanNode> new_error(const char * format, ...);
        std::shared_ptr<ExecutionPlanNode> new_string(std::string & value);
        std::shared_ptr<ExecutionPlanNode> new_integer(int64_t value);
        std::shared_ptr<ExecutionPlanNode> new_float(float value);
        std::shared_ptr<ExecutionPlanNode> new_null();

        std::shared_ptr<ExecutionPlanNode> eval(const std::shared_ptr<Node> & node, Environment * env, const std::shared_ptr<ExecutionPlanNode> & root);
        std::shared_ptr<ExecutionPlanNode> eval_program(const std::list<std::shared_ptr<dt::Statement>> & stats, Environment * env, const std::shared_ptr<ExecutionPlanNode> & root);
        std::shared_ptr<ExecutionPlanNode> eval_string(const std::shared_ptr<String> & node);
        std::shared_ptr<ExecutionPlanNode> eval_integer(const std::shared_ptr<Integer> & node);
        std::shared_ptr<ExecutionPlanNode> eval_float(const std::shared_ptr<Float> & node);
        std::shared_ptr<ExecutionPlanNode> eval_null(const std::shared_ptr<Null> & node);
        std::shared_ptr<ExecutionPlanNode> eval_identifier(const std::shared_ptr<Identifier> & node, Environment * env);

        std::shared_ptr<ExecutionPlanNode> eval_show(const std::shared_ptr<Show> & node);
        std::shared_ptr<ExecutionPlanNode> eval_use(const std::shared_ptr<Use> & node);
        std::shared_ptr<ExecutionPlanNode> eval_create(const std::shared_ptr<Create> & node);
        std::shared_ptr<ExecutionPlanNode> eval_insert(const std::shared_ptr<Insert> & node);
        std::shared_ptr<ExecutionPlanNode> eval_select(const std::shared_ptr<Select> & select, const std::shared_ptr<ExecutionPlanNode> & root);

        std::shared_ptr<ExecutionPlanNode> eval_sys(const std::shared_ptr<System> & node, const std::shared_ptr<ExecutionPlanNode> & where);

        // 前缀表达式求值
        std::shared_ptr<ExecutionPlanNode> eval_prefix(const std::shared_ptr<Prefix> & node, Environment * env, const std::shared_ptr<ExecutionPlanNode> & root);
        std::shared_ptr<ExecutionPlanNode> eval_minus_prefix_expression(const std::shared_ptr<ExecutionPlanNode> & right);

        // 中缀表达式求值
        std::shared_ptr<ExecutionPlanNode> eval_infix(const std::string & op, const std::shared_ptr<ExecutionPlanNode> & left, const std::shared_ptr<ExecutionPlanNode> & right);
        std::shared_ptr<ExecutionPlanNode> eval_string_infix_expression(const std::string & op, const std::shared_ptr<ExecutionPlanNode> & left, const std::shared_ptr<ExecutionPlanNode> & right);

        bool use_database(const std::string & db_name);
        // 转换成表达式树
//        std::shared_ptr<ExprNode> convert_to_new_tree(const std::shared_ptr<Expression> & old_node);

    public:
        std::string                     m_curr_db_name;
    };

#endif //DTIMEDB_EVALUATOR_H
