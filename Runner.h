#include <any>
#include<vector>
#include <map>
#include <type_traits>
#include"Node.h"
class Runner{
public:
    map<string, any> variables;
    any run(shared_ptr<Node> node);
    any runBinary(shared_ptr<BinaryOperationNode> node);
    any evalute(int left, int right, string op);
    any evalute(string left, string right, string op);
    void SetVariable(string name, any value);
    any GetVariable(string name);
    any runCall(shared_ptr<CallNode> call);
    void runIf(shared_ptr<IfNode> node);
};