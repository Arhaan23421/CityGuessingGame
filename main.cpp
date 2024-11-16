#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct TreeNode {
    string value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(string val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
    TreeNode() {
        left = nullptr;
        right = nullptr;
    }
};

string removefirstLet(string sample)
{
    string result;
    result = sample.substr(1,sample.length()-1);
    return result;
}

TreeNode* makeTree(ifstream &fin)
{
    string line;
    getline(fin, line);
    TreeNode* result  = new TreeNode(line);
    if(line[0] == 'Q') {
        result->left = makeTree(fin);
        result->right = makeTree(fin);
    }
    return result;

}
void playGame(TreeNode* tree)
{
    if(tree->value[0] == 'A') {
        cout<< "is your answer " << removefirstLet(tree->value)<<endl;
        string answer2;
        getline(cin, answer2);
        if(answer2.compare("y") ==0) {
            cout<< "sweet"<<endl;
        }
        else {
            cout<<" Darn. What was your answer? ";
            string answer3;
            string question;
            getline(cin, answer3);
            cout<< "please enter a question that would distinguish between " << removefirstLet(tree->value)<< " and "<< answer3<<" ";
            getline(cin, question);
            string qa;
            cout<< " if you were thinking of "<< answer3<<" what would the correct answer to your question be? ";
            getline(cin, qa);
            TreeNode* templeft;
            TreeNode* tempright;
            if(qa.compare("y")==0) {
                templeft = new TreeNode("A" +answer3);
                tempright = new TreeNode(tree->value);
            }
            else {
                tempright = new TreeNode("A" +answer3);
                templeft = new TreeNode(tree->value);
            }
            tree->value = "Q" + question;
            tree->left = templeft;
            tree->right = tempright;

        }
    }
    else {
        cout<<removefirstLet(tree->value)<<endl;
        string answer;
        getline(cin, answer);

        if(answer.compare("y") ==0) {
            playGame(tree->left);

        }
        else {
            playGame(tree->right);
        }
    }
}
void saveinfoHelper(TreeNode* tree, ofstream &file)
{
    if(tree ==nullptr) {
        return;
    }
    else {
        file<< tree->value <<endl;
        saveinfoHelper(tree->left, file);
        saveinfoHelper(tree->right, file);
    }
}

void saveinfo(TreeNode* root)
{
    cout<< " do you want to save your information? ";
    string answer;
    getline(cin, answer);
    if(answer.compare("y")==0) {
        cout<< " what would you like the file to be named? ";
        getline(cin, answer);
        ofstream file(answer);
        saveinfoHelper(root, file);

    }
}

int main() {
    cout << "City Guessing Game" << endl << endl;
    cout << "Welcome to the city City Guessing Game!" << endl;
    string filename;
    cout << "Enter the name of the data file: ";
    getline(cin, filename);
    TreeNode* root = nullptr;
    ifstream fin(filename);
    root = makeTree(fin);
    playGame(root);
    string ans;
    cout<< "do you want to play again? ";
    getline(cin, ans);
    while(ans.compare("y")==0) {
        playGame(root);
        cout<< "do you want to play again? ";
        getline(cin, ans);
    }
    saveinfo(root);
    cout << "Good bye!" << endl;
    return 0;
}