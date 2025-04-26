class Solution {
public:
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        if (trees.size() == 1) return trees[0];
        
        unordered_map<int, TreeNode*> valToRoot;
        unordered_set<int> leaves;
        
        // Paso 1: Hasheamos las raices y almacenamos las hojas
        for (TreeNode* root : trees) {
            valToRoot[root->val] = root;
            if (root->left) leaves.insert(root->left->val);
            if (root->right) leaves.insert(root->right->val);
        }
        
        // Paso 2: Buscar una raiz que no aparezca como hoja
        TreeNode* mainRoot = nullptr;
        for (TreeNode* root : trees) {
            if (leaves.find(root->val) == leaves.end()) {
                if (mainRoot != nullptr) return nullptr; // Solo puede haber una raíz candidata
                mainRoot = root;
            }
        }
        if (mainRoot == nullptr) return nullptr;
        
        // Paso 3: Tratamos de armar el BST final
        unordered_set<int> visited;
        visited.insert(mainRoot->val);
        int count = 1;
        
        if (!buildTree(mainRoot, valToRoot, visited, count, LONG_MIN, LONG_MAX)) {
            return nullptr;
        }
        
        // Paso 4: Verificar que todos los árboles de trees fueron usados
        if (count != trees.size()) {
            return nullptr;
        }
        
        return mainRoot;
    }
    
private:
    // Funcion que verifica que se pueda armar el BST, que se pueda combinar un BST con otro
    bool buildTree(TreeNode* node, unordered_map<int, TreeNode*>& valToRoot, 
                  unordered_set<int>& visited, int& count, long minVal, long maxVal) {
        if (node == nullptr) return true;
        
        // Verificar límites BST para el merge
        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }
        
        // Si es una hoja y existe un árbol con esta raíz
        if (node->left == nullptr && node->right == nullptr) {
            auto it = valToRoot.find(node->val);
            if (it != valToRoot.end() && visited.find(node->val) == visited.end()) {
                TreeNode* childRoot = it->second;
                node->left = childRoot->left;
                node->right = childRoot->right;
                visited.insert(node->val);
                count++;
            }
        }
        
        // Verificar subárbol izquierdo
        if (node->left) {
            if (!buildTree(node->left, valToRoot, visited, count, minVal, node->val)) {
                return false;
            }
        }
        
        // Verificar subárbol derecho
        if (node->right) {
            if (!buildTree(node->right, valToRoot, visited, count, node->val, maxVal)) {
                return false;
            }
        }
        
        return true;
    }
};
