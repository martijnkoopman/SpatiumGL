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

#ifndef SPATIUMGL_IDX_OCTREENODE_H
#define SPATIUMGL_IDX_OCTREENODE_H

namespace spatiumgl {
	namespace idx {

		/// \class OctreeNode
		/// \brief Node in an Octree.
		class OctreeNode : public TreeNode<void,8>
		{
		public:

			/// Constructor
			///
			/// \param[in] parent Parent node
			OctreeNode(OctreeNode *parent = nullptr)
				: TreeNode<void,8>(parent)
			{
			}
		};

	} // namespace idx
} // namespace spatiumgl

#endif // SPATIUMGL_IDX_OCTREENODE_H