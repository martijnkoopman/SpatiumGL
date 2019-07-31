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

#ifndef SPATIUMGL_IDX_TREENODE_H
#define SPATIUMGL_IDX_TREENODE_H

namespace spatium {
	namespace idx {

		/// \class TreeNode
		/// \brief Node in a Tree.
		///
		/// TreeNode is a node in a Tree. Each node has a fixed  number of children.
		/// A TreeNode is a container for a single object. The type of this object is
		/// passed as template argument. It may be void.
		/// No weak_ptrs and shared_ptrs are used to reduce size.
		template<typename G, size_t N>
		class TreeNode
		{
		public:

			/// Constructor
			///
			/// \param[in] parent Parent node
			TreeNode(TreeNode<G,N> *parent = nullptr)
				: m_parent(parent)
				, m_children()
				, m_object()
			{
			}

			/// Constructor
			///
			/// \param[in] object Object for node
			/// \param[in] parent Parent node
			TreeNode(const G& object, TreeNode<G,N> *parent = nullptr)
				: m_object(object)
				, m_children()
				, m_parent(parent)
			{
			}

			/// \return True when child count > 0, otherwise false.
			bool hasChildren()
			{
				for (size_t i = 0; i < N; i++)
				{
					if (m_children[i] != nullptr)
					{
						return true;
					}
				}
				return false;
			}

			/// Get child count.
			///
			/// \return Child count
			size_t childCount() const
			{
				size_t count = 0;
				for (size_t i = 0; i < N; i++)
				{
					if (m_children[i] != nullptr)
					{
						count++;
					}
				}
				return count;
			}

			/// Get a child.
			///
			/// \param[in] index Child index
			/// \return Child or nullptr
			TreeNode<G,N>* child(size_t index) const
			{
				if (index >= N)
				{
					return nullptr;
				}
				return m_children[index];
			}

			/// Set child node.
			///
			/// \param[in] index Index of child.
			/// \param[in] object Object
			/// \param[in] dispose Dispose old child if true (default = true)
			///                    This will invalidate any other pointers pointing to 
			///					   this object.
			/// \return Created child node
			TreeNode<G,N>* setChild(size_t index, const G& object, bool dispose=true)
			{
				if (index >= N)
				{
					return nullptr;
				}

				// Create new node
				TreeNode<G, N> *newNode = new TreeNode<G,N>(object, this);

				// Remove old node
				TreeNode<G, N>* oldNode = m_children[index];
				m_children[index] = nullptr;

				// Set new node
				m_children[index] = newNode;

				// Delete old node
				if (dispose && oldNode != nullptr)
				{
					delete oldNode;
				}

				return newNode;
			}

			/// Remove a child.
			///
			/// \param[in] index Index of child.
			/// \param[in] dispose Dispose child if true (default = true)
			///                    This will invalidate any other pointers pointing to 
			///					   this object.
			/// \return True on success, false if child doesn't exist
			bool removeChild(size_t index, const G& object, bool dispose = true)
			{
				if (index >= N)
				{
					return false;
				}

				// Remove node
				TreeNode<G, N>* oldNode = m_children[index];
				m_children[index] = nullptr;

				// Dispose node
				if (oldNode != nullptr)
				{
					if (dispose)
					{
						delete oldNode;
					}

					return true;
				}
				else
				{
					return false;
				}
			}

			/// Set the object.
			G& object()
			{
				return m_object;
			}

			/// Get the object.
			void setObject(const G& object)
			{
				m_object = object;
			}

		protected:
			TreeNode<G,N> *m_parent;
			std::array<TreeNode<G,N>,N> m_children;
			G m_object;
		};

	} // namespace idx
} // namespace spatiumgl

#endif // SPATIUMGL_IDX_TREENODE_H