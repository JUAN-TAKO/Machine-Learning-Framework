class Module : public Operation{
public:
    virtual Variable forward() = 0;
    template<typename... Args>
    virtual Variable operator()(Args... args){
        inputs = {args};
        return forward(args);
    }
    virtual void backward(Variable pb_for){
        
    }
    
private:
    std::shared_ptr<Graph> graph;
}