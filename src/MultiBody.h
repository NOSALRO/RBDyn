// This file is part of RBDyn.
//
// RBDyn is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// RBDyn is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with RBDyn.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

// includes
// std
#include <stdexcept>
#include <unordered_map>
#include <vector>

// SpaceVecAlg
#include <SpaceVecAlg>

// RBDyn
#include "Body.h"
#include "Joint.h"

namespace rbd
{

/**
	* Kinematic tree of a multibody system.
	* Same representation as featherstone except joint 0 is the root joint.
	*/
class MultiBody
{
public:
	MultiBody();

	/**
		* @param bodies Bodies of the multibody system.
		* @param joints Joints of the mutibody system.
		* @param pred Predeccesor body index of each joint.
		* @param succ Successor body index of each joint.
		* @param parent Parent body index of each body.
		* @param Xfrom Transformation from the center of the predecessor body.
		* @param Xto Transformation to the center of the successor body.
		*/
	MultiBody(std::vector<Body> bodies, std::vector<Joint> joints,
		std::vector<int> pred, std::vector<int> succ,
		std::vector<int> parent, std::vector<sva::PTransform> Xfrom,
		std::vector<sva::PTransform> Xto);

	/// @return Number of bodies.
	std::size_t nrBodies() const
	{
		return bodies_.size();
	}

	/// @return Number of joints.
	std::size_t nrJoints() const
	{
		return joints_.size();
	}

	/// @return Bodies of the multibody system.
	const std::vector<Body>& bodies() const
	{
		return bodies_;
	}

	/// @return Body at num position in bodies list.
	const Body& body(int num) const
	{
		return bodies_[num];
	}

	/// @return Joints of the multibody system.
	const std::vector<Joint>& joints() const
	{
		return joints_;
	}

	/// @return Joint at num position in joint list.
	const Joint& joint(int num) const
	{
		return joints_[num];
	}

	/// @return Predeccesor body index of each joint.
	const std::vector<int>& predecessors() const
	{
		return pred_;
	}

	/// @return Predecessor body of joint num.
	int predecessor(int num) const
	{
		return pred_[num];
	}

	/// @return Successor body index of each joint.
	const std::vector<int>& successors() const
	{
		return succ_;
	}

	/// @return Successor body of joint num.
	int successor(int num) const
	{
		return succ_[num];
	}

	/// @return Parent body index of each body.
	const std::vector<int>& parents() const
	{
		return parent_;
	}

	/// @return Parent body of body num.
	int parent(int num) const
	{
		return parent_[num];
	}

	/// @return Transformation from the center of the predecessor body
	const std::vector<sva::PTransform>& transformsFrom() const
	{
		return Xfrom_;
	}

	/// @return Transformation from the center of the predecessor body for joint num
	const sva::PTransform& transformFrom(int num) const
	{
		return Xfrom_[num];
	}

	/// @return Transformation to the center of the successor body
	const std::vector<sva::PTransform>& transformsTo() const
	{
		return Xto_;
	}

	/// @return Transformation to the center of the successor body for joint num
	const sva::PTransform& transformTo(int num) const
	{
		return Xto_[num];
	}

	/// @return Index of the body with Id id.
	int bodyIndexById(int id) const
	{
		return bodyId2Ind_.find(id)->second;
	}

	/// @return Index of the joint with Id id.
	int jointIndexById(int id) const
	{
		return jointId2Ind_.find(id)->second;
	}

	/// @return Total number of parameters.
	int nrParams() const
	{
		return nrParams_;
	}

	/// @return Total number of DoF.
	int nrDof() const
	{
		return nrDof_;
	}



	// safe accessors version for python binding

	/** Safe version of @see body.
		* @throw std::out_of_range.
		*/
	const Body& sBody(int num) const
	{
		return bodies_.at(num);
	}

	/** Safe version of @see joint.
		* @throw std::out_of_range.
		*/
	const Joint& sJoint(int num) const
	{
		return joints_.at(num);
	}

	/** Safe version of @see predecessor.
		* @throw std::out_of_range.
		*/
	int sPredecessor(int num) const
	{
		return pred_.at(num);
	}

	/** Safe version of @see successor.
		* @throw std::out_of_range.
		*/
	int sSuccessor(int num) const
	{
		return succ_.at(num);
	}

	/** Safe version of @see parent.
		* @throw std::out_of_range.
		*/
	int sParent(int num) const
	{
		return parent_.at(num);
	}

	/** Safe version of @see transformFrom.
		* @throw std::out_of_range.
		*/
	const sva::PTransform& sTransformFrom(int num) const
	{
		return Xfrom_.at(num);
	}

	/** Safe version of @see transformTo.
		* @throw std::out_of_range.
		*/
	const sva::PTransform& sTransformTo(int num) const
	{
		return Xto_.at(num);
	}

	/** Safe version of @see bodyIndexById.
		* @throw std::out_of_range.
		*/
	int sBodyIndexById(int id) const
	{
		return bodyId2Ind_.at(id);
	}

	/** Safe version of @see jointIndexById.
		* @throw std::out_of_range.
		*/
	int sJointIndexById(int id) const
	{
		return jointId2Ind_.at(id);
	}

private:
	std::vector<Body> bodies_;
	std::vector<Joint> joints_;

	std::vector<int> pred_;
	std::vector<int> succ_;
	std::vector<int> parent_;
	/// Transformation from the center of the predecessor body
	std::vector<sva::PTransform> Xfrom_;
	/// Transformation to the center of the successor body
	std::vector<sva::PTransform> Xto_;

	std::unordered_map<int, int> bodyId2Ind_;
	std::unordered_map<int, int> jointId2Ind_;

	int nrParams_;
	int nrDof_;
};

} // namespace rbd
