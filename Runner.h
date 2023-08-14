#include <any>
#include<vector>
#include <map>
#include <type_traits>
#include"Node.h"
class Runner{
public:
    map<string, any> variables;
    map<string, shared_ptr<FunctionNode>> functions;
    any run(shared_ptr<Node> node);
    any runBinary(shared_ptr<BinaryOperationNode> node);
    any evalute(int left, int right, string op);
    any evalute(string left, string right, string op);
    any evalute(bool left, bool right, string op);
    void SetVariable(string name, any value);
    any GetVariable(string name);
    any runCall(shared_ptr<CallNode> call);
    void CreateFunction(shared_ptr<FunctionNode> call);
    any runFunction(string name, vector<shared_ptr<Node>> args);
    void runIf(shared_ptr<IfNode> node);
    void runCycle(shared_ptr<CycleNode> node);
};