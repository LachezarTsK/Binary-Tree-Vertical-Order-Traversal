
#include<utility>
#include<queue>
#include<unordered_map>
#include<vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {
    }
};

class Solution {
public:
    const int MIN_TREE_NODE_VALUE = -100;
    const int MAX_TREE_NODE_VALUE = 100;

    vector<vector<int>> verticalOrder(TreeNode* root) {

        if (root == nullptr) {
            return vector<vector<int>>();
        }

        queue<pair < TreeNode*, int>> queue;
        unordered_map<int, vector<int>> map_vertical_levels;

        queue.push(pair<TreeNode*, int>(root, 0));
        map_vertical_levels[0] = vector<int>();
        map_vertical_levels[0].push_back(root->val);

        int minVertical = MAX_TREE_NODE_VALUE;
        int maxVertical = MIN_TREE_NODE_VALUE;

        while (!queue.empty()) {

            /*
            Here 'pair<TreeNode*, int>' can be replaced with the much more concise  'auto'. 
            However, the first expression makes the code easier to read since it reminds 
            the reader about what the pair consists of.
             */
            pair<TreeNode*, int> currentPair = queue.front();
            queue.pop();
            minVertical = min(minVertical, currentPair.second);
            maxVertical = max(maxVertical, currentPair.second);

            if (currentPair.first->left != nullptr) {
                int vertical = currentPair.second - 1;
                map_vertical_levels[vertical].push_back(currentPair.first->left->val);
                queue.push(pair<TreeNode*, int>(currentPair.first->left, vertical));
            }

            if (currentPair.first->right != nullptr) {
                int vertical = currentPair.second + 1;
                map_vertical_levels[vertical].push_back(currentPair.first->right->val);
                queue.push(pair<TreeNode*, int>(currentPair.first->right, vertical));
            }
        }

        vector<vector<int>> nodesInVerticalOrder;
        for (int i = minVertical; i <= maxVertical; i++) {
            nodesInVerticalOrder.push_back(map_vertical_levels[i]);
        }

        return nodesInVerticalOrder;
    }
};
