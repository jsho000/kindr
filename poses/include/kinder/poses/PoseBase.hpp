/*
 * Copyright (c) 2013, Christian Gehring, Hannes Sommer, Paul Furgale, Remo Diethelm
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Autonomous Systems Lab, ETH Zurich nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Christian Gehring, Hannes Sommer, Paul Furgale,
 * Remo Diethelm BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
#ifndef KINDER_POSES_POSESBASE_HPP_
#define KINDER_POSES_POSESBASE_HPP_


#include "kinder/common/common.hpp"


namespace kinder {
//! Generic pose interface
/*! \ingroup poses
 */
namespace poses {
//! Internal stuff (only for developers)
namespace internal {

/*! \class TransformationTraits
 * \brief Transformation trait to implement transformations of positions.
 *
 *  (only for advanced users)
 */
template<typename Pose_>
class TransformationTraits {
 public:
//  inline static Position transform(const Pose& pose, const Position& position);
//  inline static Position inverseTransform(const Pose& pose, const Position& position);
};

/*! \class get_position
 * \brief This class provides the type of the position
 *
 *  (only for advanced users)
 */
template<typename Pose_>
class get_position {
 public:
//  typedef typename positions::eigen_implementation::Position3D Position;
};

} // namespace internal



/*! \ingroup poses
 * \class PoseBase
 * \brief Base class that defines the interface of a pose
 *
 * \tparam Derived_ the derived class that should implement the pose
 */
template<typename Derived_>
class PoseBase {
 public:
  /*! \brief Standard constructor.
    *  Creates an empty generic pose object
    */
  PoseBase() = default;

  /*! \brief Constructor from derived pose.
   *  This constructor has been deleted because the abstract class does not contain any data.
   */
  PoseBase(const Derived_&) = delete; // on purpose!!

  /*! \brief Gets the derived pose.
   *  (only for advanced users)
   *  \returns the derived pose
   */
  operator Derived_& () {
    return static_cast<Derived_&>(*this);
  }

  /*! \brief Gets the derived pose.
   *  (only for advanced users)
   *  \returns the derived pose
   */
  operator const Derived_& () const {
    return static_cast<const Derived_&>(*this);
  }

  /*! \brief Gets the derived pose.
   *  (only for advanced users)
   *  \returns the derived pose
   */
  const Derived_& derived() const {
    return static_cast<const Derived_&>(*this);
  }


  /*! \brief Transforms a position
   *  \returns the transformed position
   */
  typename internal::get_position<Derived_>::Position transform(typename internal::get_position<Derived_>::Position& position) const {
    return internal::TransformationTraits<Derived_>::transform(this->derived(), position);
  }

  /*! \brief Transforms a position in reverse
   *  \returns the transformed position
   */
  typename internal::get_position<Derived_>::Position inverseTransform(typename internal::get_position<Derived_>::Position& position) const {
    return internal::TransformationTraits<Derived_>::inverseTransform(this->derived(), position);
  }


};

/*! \ingroup poses
 * \class HomogeneousTransformationBase
 * \brief Base class that defines the interface of a homogeneous transformation
 *
 * \tparam Derived_ the derived class that should implement the homogeneous transformation
 */
template<typename Derived_>
class HomogeneousTransformationBase : public PoseBase<Derived_> {
 public:

  template<typename OtherDerived_>
  HomogeneousTransformationBase& operator =(const HomogeneousTransformationBase<OtherDerived_>& other) {
    return *this;
  }

};


} // namespace internal

namespace internal {

} // namespace poses
} // namespace kinder


#endif /* KINDER_POSES_POSESBASE_HPP_ */
