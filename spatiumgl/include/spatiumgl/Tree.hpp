/*
 * Program: Spatium Graphics Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef SPATIUMGL_IDX_TREE_H
#define SPATIUMGL_IDX_TREE_H

#include "TreeNode.h"

namespace spatiumgl {
	namespace idx {

		// Forward declare iterator
		template<typename G>
		class TreeIterator;

		/// \class Tree
		/// \brief Tree data structure
		///
		/// Tree is a hierarchical data structure composed of nodes (TreeNode). It has
		/// one node that represents the root of the tree.
		template<typename G, size_t N>
		class Tree
		{
		public:

			/// Constructor.
			///
			/// \param[in] rootNode Root node (optional)
			Tree(TreeNode<G,N> *rootNode = nullptr)
				: m_root(rootNode)
			{
			}

			/// Constructor
			///
			/// \param[in] rootObject Object for root node
			/// \param[in] rootNode Root node (optional)
			Tree(const G& rootObject, TreeNode<G,N> *rootNode = new TreeNode<G,N>)
				: m_root(rootNode)
			{
				m_root->setObject(rootObject);
			}

			/// Get the root node.
			///
			/// \return Root node
			TreeNode<G,N>* root() const
			{
				return m_root;
			}

			/*
			/// Get iterator pointing to the beginning of the tree (root node).
			///
			/// This iterator traverses the tree in depth-first order.
			///
			/// \return Tree iterator
			TreeIterator<G> begin()
			{
				return TreeIterator<G>(*this);
			}

			/// Get iterator pointing to the end of the tree.
			///
			/// This iterator traverses the tree in depth-first order.
			///
			/// \return Tree iterator
			TreeIterator<G> end()
			{
				return TreeIterator<G>(*this, true);
			}
			*/

		protected:
			const TreeNode<G,N> *m_root;
		};

	} // namespace idx
} // namespace spatiumgl

#endif // SPATIUMGL_IDX_TREE_H