#include <iostream>
#include <fstream>
#include <string.h>
#include <random>
using namespace std;

/*File Handlers*/
ifstream fin("input.txt");
ofstream fout("output.txt");


class Phase2_MOS{
    /*Memory*/
    char M[300][4];
    char buffer[40];
    int PCB[5]; // JobId, TTL, TLL, TTC, LLC;
    char IR[4];
    char R[4];
    int VA, RA;
    int TTC, LLC;
    int TTL, TLL;
    int PTR;
    int IC;
    int C;
    int SI = 0, PI = 0, TI = 0;

    Phase2_MOS(){
        memset(M, '\0', 1200);
        memset(buffer, '\0', 40);
        memset(IR, '\0', 4);
        memset(R, '\0', 4);
        TTC = 0, LLC = 0;
        C = 0;
    }

    void initPCB(){
        int counterPCB = 0;
        memset(PCB, '\0', 5);
        
        // For JobId, TTL, TLL 
        for (int i = 4; i < 12; i++){
            string val = "";
            for (int j = 0; j < 4; j++){
                val += buffer[i+j];
            }
            PCB[counterPCB++] = stoi(val);
        }

        // For TTC, LLC
        PCB[counterPCB++] = 0;
        PCB[counterPCB] = 0;
    }


    void read(int RA){
        char temp[4];
        memcpy(temp, buffer, 4);

        if (!strcmp(temp, "$END"))
            terminate(1)
        else
            fin.getline(M[RA], buffer);
    }


    void write(int RA){
        LLC++;

        if (LLC > TLL)
            terminate(2);
        else{
            char str[40];
            int k = 0;
            for(int i = RA; i < (RA + 10); i += 4){
                for(int j = 0; j < 4; j++)
                    str[k++] = M[i][j];
            }
            fout << str << endl;
        }
    }


    void terminate(int EM){
        int jobID = PCB[0];

        fout << endl << endl;
        if (EM == 0)
            fout << "Program with id " << jobID << "terminated with no errors." << endl;
        else
            fout << "Program with id " << jobID << "terminated with " << errors[EM] << endl;
    }


    int allocate(){
        return (rand() % 30);
    }


    void load(){
        int currPTR = 0;
        int m;
        char temp[5];
        while (!fin.eof()){
            fin.getline(buffer, 41);
            memset(temp, '\0', 5);
            memcpy(temp, buffer, 4); 

            //Control Card
            if (!strcmp(temp, "$AMJ")){
                initPCB();
                // yet to understand
            }
            else if (!strcmp(temp, "$DATA")){
                startExecution();
            }
            else if (!strcmp(temp, "$END")){
                continue;
            }
            else{
                // yet to understand
            }
        }
    }

    void startExecution(){
        IC = 0;
        executeUserProgram();
    }


    int addressMap(int VA){
        if (VA >= 0 && VA < 100){
            int pte = PTR + (VA / 10);
            if (M[pte] != "*")
                return (atoi(M[pte]) * 10) + (VA % 10);
            else
                PI = 3;
        }
        else
            PI = 2;
        return -1;
    }


    void executeUserProgram(){
        int tempAdd, realAdd;
        char temp[2];
        while(true){
            RA = addressMap(IC);
            if (PI != 0)
                break;

            memcpy(IR, M[RA], 4);
            IC++;

            tempAdd = atoi(IR[3] + IR[4]);
            realAdd = addressMap(tempAdd);

            memset(temp, '/0', 2);
            memcpy(temp, IR, 2);



        }
    }

};






void mos(int SI, int loc = 0){
    switch(SI){
        case 1:
            read(loc);
            break;
        case 2:
            write(loc);
            break;
        case 3:
            Terminate();
            break;
        default:
            cout<<"Error! Wrong SI."<<endl;
    }
}

void start_execution(){
    IC = 0;
    executeUserProgram();
}


int main(){
    load();
    fin.close();
    fout.close();
    return 0;
}

