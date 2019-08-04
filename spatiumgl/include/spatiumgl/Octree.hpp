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

#ifndef SPATIUMGL_IDX_OCTREE_H
#define SPATIUMGL_IDX_OCTREE_H

#include "Tree.h"
#include "OctreeNode.h"

namespace spatiumgl {
	namespace idx {

		/// \class Octree
		/// \brief Octree data structure
		///
		/// Octree is a hierarchical data structure composed of nodes (OctreeNodes). 
		/// Each node in the tree can have 8 children. Each child expands one octant of space. 
		/// One node represents the root of the tree.
		class SubsampleOctree : public Tree<void,8>
		{
		public:

			/// Constructor
			Octree(const BoundingBox<double, 3> &bounds)
				: Tree<void,8>(new OctreeNode())
				, m_boundingBox(bounds)
			{
				// Make bounding box cubical
				// ... ?? Really neccasseryy?
			}

			/// Determine index of child (0 - 8) depening on bounding box of parent and positon of a point.
			/// Also outputs the bounding box of this child.
			///
			/// \param[in] boundsParent Bounding box of parent
			/// \param[in] point Point positon (must be within bounding box)
			/// \param[out] boundsChild Bounding box of child
			/// \return Child index (0 = topleft, 1 = topright, 2 = bottom right, 3 = bottom left)
			static size_t determineChild(const BoundingBox<double, 3> &boundsParent, const std::array<double, 3> &point, BoundingBox<double, 3> &boundsChild)
			{
				std::array<double, 3> min = boundsParent.min();
				std::array<double, 3> max = boundsParent.max();
				std::array<double, 3> center = boundsParent.center();
				if (point[0] < center[0])
				{
					// Left half
					if (point[1] < center[1])
					{
						// Bottom
						boundsChild = BoundingBox<double, 3>::fromMinMax(min, center);
						return 0;
					}
					else
					{
						// Top
						boundsChild = BoundingBox<double, 3>::fromMinMax({ min[0], center[1] }, { center[0], max[1] });
						return 2;
					}
				}
				else
				{
					// Right half
					if (point[1] < center[1])
					{
						// Top
						boundsChild = BoundingBox<double, 3>::fromMinMax({ center[0], min[1] }, { max[0], center[1] });
						return 1;
					}
					else
					{
						// Bottom
						boundsChild = BoundingBox<double, 3>::fromMinMax(center, max);
						return 3;
					}
				}
			}
			
			/// Get the bounding box 
			BoundingBox<double, 3> bounds() const
			{
				return m_boundingBox;
			}

			/// Get the maximum point count for a node.
			///
			/// A node is split when it exceeds this number.
			size_t division() const
			{
				return m_division;
			}

		protected:
			const BoundingBox<double, 3> m_boundingBox;
			const size_t m_division;
		};

	} // namespace idx
} // namespace spatiumgl

#endif // SPATIUMGL_IDX_OCTREE_H