#ifndef __INPUT_H_
#define __INPUT_H_

const int MAX_PARAMS = 2;

class Input {
    int count;
    bool cmd;

    // add additional space for one extra parameter in
    // order for the validation to work
    // (ie error "too many parameters" is displayed)
    std::string params[MAX_PARAMS];

    public:
        Input();
        ~Input();

        void add(const std::string&);

        void setCMD();

        void unsetCMD();

        // shows whether the input is gathered from a command line
        // at the time of starting the program (true), or it is
        // entered during the program runtime by the user (false)
        bool isCMD() const;

        char getAction() const;

        int getID() const;


        // ::params: input - input structure is modified
        void get_input();

        // ::params: input - input structure 
        // ::return: 1 if input is valid, else 0
        bool isValid() const;

        // set input value and input count to 0, nullify pointers 
        // inside input->params
        //
        // ::params: input - input structure is modified
        void clear_input();
};

#endif
