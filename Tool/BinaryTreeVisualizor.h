#ifndef _BINARYTREEVISUALIZOR_H_
#define _BINARYTREEVISUALIZOR_H_


namespace MyTools
{
	struct BinaryTreeNode
	{
		int centre_x;
		int centre_y;
		BinaryTreeNode* left;
		BinaryTreeNode* right;
	};

	template<typename NodeType>
	class BinaryTreeVisualizor
	{
	public:
		typedef NodeType* NodePtr;
		typedef typename BinaryTreeVisualizor<NodeType> self;
		typedef BinaryTreeNode* ResultTreeNodePtr;
	public:
		BinaryTreeVisualizor(float layer_interval, float sibling_interval, float radius)
			: root(nullptr),
			layer_interval(layer_interval),
			sibling_interval(sibling_interval),
			radius(radius),
			left(0),
			right(0),
			height(0)
		{
		}
		BinaryTreeVisualizor(const BinaryTreeVisualizor& rhs)
		{
			destroy_result_tree();
			copy(rhs);
		}
		self& operator = (const BinaryTreeVisualizor& rhs)
		{
			destroy_result_tree();
			copy(rhs);
			return *this;
		}
		~BinaryTreeVisualizor(){ destroy_result_tree(); }
		void SetLayerInterval(float interval){ layer_interval = interval; }
		void SetSiblingInterval(float interval){ sibling_interval = interval; }
		void SetRadius(float radius){ this->radius = radius; }
		void VisulizeTree(NodePtr TreeRoot)
		{
			destroy_result_tree();
			if (TreeRoot != nullptr)
			{
				root = create_result_node(0, 1);
				VisulizeLeftTree(&root->left, 0, 1, TreeRoot->left);
				VisulizeRightTree(&root->right, 0, 1, TreeRoot->right);
			}
		}
		int GetLeft(){ return left; }
		int GetRight(){ return right; }
		int GetHeight(){ return height; }
	private:
		ResultTreeNodePtr create_result_node(int centre_x, int centre_y)
		{
			BinaryTreeNode* node = new BinaryTreeNode;
			node->centre_x = centre_x;
			node->centre_y = centre_y;
			node->left = node->right = nullptr;
			return node;
		}

		ResultTreeNodePtr copy_result_node(ResultTreeNodePtr src)
		{
			return create_result_node(src->centre_x, src->centre_y);
		}
		void copy(const BinaryTreeVisualizor& rhs)
		{
			layer_interval = rhs.layer_interval;
			sibling_interval = rhs.sibling_interval;
			radius = rhs.radius;
		}
		void destroy_result_tree()
		{
			__destroy_result_tree(root);
		}

		void __destroy_result_tree(ResultTreeNodePtr root)
		{
			if (root != nullptr)
			{
				__destroy_result_tree(root->left);
				__destroy_result_tree(root->right);
				delete root;
				root = nullptr;
			}
		}

		void copy_result_tree(ResultTreeNodePtr src)
		{
			__copy_result_tree(&root, src);
		}

		void __copy_result_tree(ResultTreeNodePtr* dst, ResultTreeNodePtr src)
		{
			if (src == nullptr)
			{
				dst = nullptr;
				return
			}
			else
			{
				ResultTreeNodePtr node = copy_result_node(src);
				*dst = node;
				__copy_result_tree(&((*dst)->left), node->left);
				__copy_result_tree(&((*dst)->right), node->right);
			}
		}

		void VisulizeLeftTree(ResultTreeNodePtr* result_tree, int pre_centre_x, int pre_centre_y, NodePtr src_tree)
		{
			if (src_tree != nullptr)
			{
				*result_tree = create_result_node(pre_centre_x - 1, pre_centre_y + 1);
				if (pre_centre_x - 1 < left) left = pre_centre_x - 1;
				if (pre_centre_y + 1 > height) height = pre_centre_y + 1;
				VisulizeLeftTree(&((*result_tree)->left), pre_centre_x - 1, pre_centre_y + 1, src_tree->left);
				VisulizeRightTree(&((*result_tree)->right), pre_centre_x - 1, pre_centre_y + 1, src_tree->right);
			}
		}

		void VisulizeRightTree(ResultTreeNodePtr* result_tree, int pre_centre_x, int pre_centre_y, NodePtr src_tree)
		{
			if (src_tree != nullptr)
			{
				*result_tree = create_result_node(pre_centre_x + 1, pre_centre_y + 1);
				if (pre_centre_x + 1 > right) right = pre_centre_x + 1;
				if (pre_centre_y + 1 > height) height = pre_centre_y + 1;
				VisulizeLeftTree(&((*result_tree)->left), pre_centre_x + 1, pre_centre_y + 1, src_tree->left);
				VisulizeRightTree(&((*result_tree)->right), pre_centre_x + 1, pre_centre_y + 1, src_tree->right);
			}
		}

	private:
		ResultTreeNodePtr root;
		float layer_interval;
		float sibling_interval;
		float radius;
		int left;
		int right;
		int height;
	};
}


#endif