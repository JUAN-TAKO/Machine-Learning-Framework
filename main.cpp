#include "include/core/Graph.hpp"
#include <iostream>


class Test : public ara::Module{
    auto t1 = testLayer(10, 30);
    auto t2 = testLayer(20, 20);
    auto t3 = anotherOne(120);
    auto t4 = testLayerB(10,10,10);
    auto t5 = testLayerB(20,10,20);
public:
    ara::Variable forward(Variable in){
        auto a = t1(in);
        auto b = a;
        Variable c;
        a = t2(b);
        c = a
        c = t3(c);
        b = t4(t5(c));
        return b;
    }
}

class FullyConnected : public ara::Module{
public:
    FullyConnected(unsigned int inSize, unsigned int outSize){
        weights = Matrix.random(inSize, outSize);
    }
    ara::Variable forward(inVec){
        return inVec * weights;
    }
private:
    Matrix weights;
    unsigned int activation;

};

class Net : public ara::Module{
private:
    auto fc1 = FullyConnected(100, 50);
    auto fc2 = FullyConnected(50, 40);
    auto fc3 = FullyConnected(40, 25);
    auto fc4 = FullyConnected(25, 10);
    auto relu1 = ara::relu();
    auto relu2 = ara::relu();
    auto relu3 = ara::relu();
    auto softmax4 = ara::softmax();
public:
    Net(){}
    ara::Variable forward(ara::Variable inVec);
        out = relu1(out);
        out = fc2(out);
        out = relu2(out);
        out = fc3(out);
        out = relu3(out);
        out = fc4(out);
        return softmax4(out);
    }
    void train(ara::DataSet dataset, ara::Optimizer optim, unsigned int epochs, unsigned int batchSize, bool parallel = false){
        for(int i(0); i < epochs, i++){
            ara::Variable a;
            ara::Variable t;
            for(int j : data){
                a = dataset.data[j];
                t = dataset.target[j];           //when parallel = true :
                auto output = net(a, parallel);  //returns immediatly but the variable output "knows" it's not ready yet
                auto loss = ara::loss(output, t) //loss to "knows" it has to wait for output so it's not ready either, also returns immediatly
                loss.backward();                 //same again
                if(j % BATCH_SIZE == 0){
                    optimizer.step();            //the optimizer needs the values, waits for the values, doesn't return immediatly
                    std::cout << "Batch " << j/batchSize << "/" << dataset.data.size()/batchSize << " of epoch " << i << "/" << epochs << std::endl;
                    std::cout << "loss : " << loss << std::endl;
                }
            }
        }
    }
};

int main(){

    auto data = ara::load("data.csv");
    auto target = ara::load("target.csv");
    auto test = ara::load("test.csv");
    auto test_target = ara::load("test_target.csv");
    const int BATCH_SIZE = 100;
    const int EPOCHS = 20;
    Net net();
    auto optimizer = ara::adam(net, 0.02);
    
    auto dataset = ara::DataSet(data, target);
    net.train(dataset, optimizer, EPOCHS, BATCH_SIZE);
    
    float loss;
    for (int i : test){
        auto pred = net(test[i]);
        loss += ara::loss(pred, test_target[i]);
    }
    loss /= test.size();
    std::cout << "loss : " << loss << std::endl;
    return 0;
}
