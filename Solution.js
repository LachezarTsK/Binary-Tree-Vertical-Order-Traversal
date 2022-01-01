
function TreeNode(val, left, right) {
    this.val = (val === undefined ? 0 : val);
    this.left = (left === undefined ? null : left);
    this.right = (right === undefined ? null : right);
}

//Pair is applied as a Linked List Node.
function Pair(treeNode = null, vertical_level = - 1) {
    this.treeNode = treeNode;
    this.vertical_level = vertical_level;
    this.next = null;
}

/**
 * @param {TreeNode} root
 * @return {number[][]}
 */
var verticalOrder = function (root) {

    if (root === null) {
        return [];
    }
    const MAX_NUMBER_OF_TREE_NODES = 100;
    
    let head_queuePairs = new Pair(root, 0);
    let tail_queuePairs = head_queuePairs;
    const map_vertical_levels = new Map();
    map_vertical_levels.set(0, [root.val]);

    let minVertical = MAX_NUMBER_OF_TREE_NODES;
    let maxVertical = -MAX_NUMBER_OF_TREE_NODES;

    while (head_queuePairs !== null) {

        let pair = head_queuePairs;
        minVertical = Math.min(minVertical, pair.vertical_level);
        maxVertical = Math.max(maxVertical, pair.vertical_level);

        if (pair.treeNode.left !== null) {

            let vertical = pair.vertical_level - 1;
            if (!map_vertical_levels.has(vertical)) {
                map_vertical_levels.set(vertical, []);
            }

            map_vertical_levels.get(vertical).push(pair.treeNode.left.val);
            tail_queuePairs.next = new Pair(pair.treeNode.left, vertical);
            tail_queuePairs = tail_queuePairs.next;
        }

        if (pair.treeNode.right !== null) {

            let vertical = pair.vertical_level + 1;
            if (!map_vertical_levels.has(vertical)) {
                map_vertical_levels.set(vertical, []);
            }

            map_vertical_levels.get(vertical).push(pair.treeNode.right.val);
            tail_queuePairs.next = new Pair(pair.treeNode.right, vertical);
            tail_queuePairs = tail_queuePairs.next;
        }

        head_queuePairs = head_queuePairs.next;
    }

    const nodesInVerticalOrder = [];
    for (let i = minVertical; i <= maxVertical; i++) {
        nodesInVerticalOrder.push(map_vertical_levels.get(i));
    }
    return nodesInVerticalOrder;
};
