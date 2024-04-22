#include "binarytree.h"

class BST {
	BinaryTree* tree = new BinaryTree();

	public:
	bool search(int num) {
		return search_node(tree->getRoot(), num);
	}

	bool search_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
			return true;
		}
		if (num > n->elem) {
			// proceed to right
			return search_node(n->right, num);
		} else {
			return search_node(n->left, num);
		}
	}

    // TODO perform post-processing by checking for violation after insertion
    // from the node inserted (or from its parent) until the root
	node* insert(int num) {
		node* n = tree->getRoot();
		if (n == NULL) {
			return tree->addRoot(num);
		}
		node* inserted = insert_node(n, num);
		balance(inserted);
		return inserted;
	}

	node* insert_node(node* n, int num) {
		if (n == NULL) {
			return NULL;
		}
		if (n->elem == num) {
			return NULL;
		}
		if (num > n->elem) {
			if (!n->right) {
				return tree->addRight(n, num);
			} else {
				return insert_node(n->right, num);
			}
		} else {
			if (!n->left) {
				return tree->addLeft(n, num);
			} else {
				return insert_node(n->left, num);
			}
		}
	}

	void balance(node* n) {
		if (!n) return;
		int balanceFactor = n->left->height() - n->right->height();
		if (balanceFactor > 1 || balanceFactor < -1) {
			restructure(n);
		}
		balance(n->parent);
	}


    // TODO perform post-processing by checking for violation after deletion
    // from the parent of the node removed until the root
    bool remove(int num) {
        return remove_node(tree->getRoot(), num);
    }

	bool remove_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
            if (n->left && n->right) {
                node* r = n->right;
                while (r->left) {
                    r = r->left;
                }
                int rem = tree->remove(r);
                n->elem = rem;
            } else {
    			tree->remove(n);
            }
            return true;
		}
		if (num > n->elem) {
			return remove_node(n->right, num);
		} else {
			return remove_node(n->left, num);
		}
	}

    bool restructure(node* gp) {
        node* par;
		if (gp->left && gp->right) {
			if (gp->left->height() > gp->right->height()) {
				par = gp->left;
			} else {
				par = gp->right;
			}
		} else if (!gp->left) {
			par = gp->right;
		} else {
			par = gp->left;
		}

        bool gtop_right = false;
        if (gp->right == par) {
            gtop_right = true;
        }

        node* child;
        if (par->left && par->right) {
	        if (par->left->height() > par->right->height()) {
		        child = par->left;
	        } else if (par->left->height() == par->right->height()) {
				if (gtop_right) {
					child = par->right;
				} else {
					child = par->left;
				}
	        } else {
		        child = par->right;
	        }
        } else if (!par->left) {
	        child = par->right;
        } else if (!par->right) {
	        child = par->left;
        }

        bool ptoc_right = false;
        if (par->right == child) {
            ptoc_right = true;
        }

        if (gtop_right && ptoc_right) {
        	cout << "ZIGLEFT" << endl;
            zigleft(par);
        } else if (gtop_right && !ptoc_right) {
        	cout << "ZIGZAGLEFT" << endl;
            zigright(child);
        	zigleft(child);
        } else if (!gtop_right && !ptoc_right) {
        	cout << "ZIGRIGHT" << endl;
            zigright(par);
        } else {
        	cout << "ZIGZAGRIGHT" << endl;
            zigleft(child);
        	zigright(child);
        }
        return true;
    }

    void zigleft(node* curr) {
        tree->zigleft(curr);
    }

    void zigright(node* curr) {
        tree->zigright(curr);
    }

	void print() {
		tree->print();
	}
};
