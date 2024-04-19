using namespace std;

struct node {
    node* parent;
    node* right;
    node* left;
    int elem;

    // TODO paste your height method here
    int height() {
        if (!this) {
            return 0;
        }
        int leftHeight = (left) ? left->height() : 0;
        int rightHeight = (right) ? right->height() : 0;

        return max(leftHeight, rightHeight) + 1;
    }
};
