#ifndef SUBJ83SNKRIWON423KHTJEIYU589
#define SUBJ83SNKRIWON423KHTJEIYU589

// vim:set tabstop=4 cindent:

// Author: Geert-Jan Giezeman <geert@cs.uu.nl>
// Copyright: Utrecht University, 2011

#include "uuc3d.hpp"
#include "skeleton_info.hpp"

namespace UuIcsC3d
{
	/**
	 * \addtogroup C3dSubjects C3d labelling of sunjects
	 * @{
	 */

    /*! \brief A LabeledSubject is a subject with a name for which the markers
	  are linked to a label index (or point index).
	*/
	struct LabeledSubject {
		/** Constructor that takes the name of the subject and the
		 * SkeletonInfo that specifies the structure of the skeleton.
		  */
		LabeledSubject(std::string const &name, MarkerNames const &label_info);
		/** Get the subject name (the part before the first colon in the
		 * complete label.
		 */
		std::string name() const {return m_name;}
		/** Get the number of labels in this subject.
		  */
		unsigned label_count() const { return m_label_count;}
		//! point_index()[e] is the index in the point_data part of a frame
		//! belonging to element e, which is a specific element in
		//! a skeleton_info group.
		//! The value is -1 if there is no such element.
		std::vector<int> const &point_index() const { return m_point_index;}
		/** Set the name for this subject.
		  */
		void set_name(std::string const &name) {m_name=name;}
		/** Sets a value that will be reflected by future calls to
		 * point_index().
		 */
		void set_index(int el, int val) {m_point_index[el]=val;}
	private:
		std::string m_name; // The prefix that is used in the labelling
		unsigned m_label_count;
		std::vector<int> m_point_index; 
	};
	/** Expects a number of labels in Vicon style (subject name followed by
	  * colon followed by the marker name). Extracts a number of
	  * LabeledSubject objects from that info.
	  * \param subjects the resulting subjects.
	  * \param labels the labels as found in a c3d file.
	  * \param marker_names the expected names of the markers.
	  * \result value contains the labels that could not be classified as a
	  *  label_info label. It contains indices in the labels vector.
	  */
	std::vector<unsigned> fill_subjects(std::vector<LabeledSubject> &subjects,
					std::vector<SpacePaddedString> const &labels,
					MarkerNames const &marker_names);
	/*! \brief A LabeledSkeleton is a subject with a name for which the markers
	  of a skeleton are linked to a label index (or point index).
	*/
	struct LabeledSkeleton {
		/** Constructor that takes the name of the subject and the
		 * SkeletonInfo that specifies the structure of the skeleton.
		  */
		LabeledSkeleton(std::string const &name, SkeletonInfo const &skel_info);
		/** Get the subject name (the part before the first colon in the
		 * complete label.
		 */
		std::string name() const {return m_name;}
		/** Get the number of labels in this subject.
		  */
		unsigned label_count() const { return m_label_count;}
		//! point_index()[g][e] is the index in the point_data part of a frame
		//! belonging to element e in group g, which is a specific element in
		//! a skeleton_info group.
		//! The value is -1 if there is no such element.
		std::vector< std::vector<int> > const &point_index() const { return m_point_index;}
		/** Set the name for this subject.
		  */
		void set_name(std::string const &name) {m_name=name;}
		/** Sets a value that will be reflected by future calls to
		 * point_index().
		 */
		void set_index(int gr, int el, int val) {m_point_index[gr][el]=val;}
	private:
		std::string m_name; // The prefix that is used in the labelling
		unsigned m_label_count;
		std::vector< std::vector<int> > m_point_index; 
	};

	/** Expects a number of labels in Vicon style (subject name followed by
	  * colon followed by the marker name). Extracts a number of
	  * LabeledSkeleton objects from that info.
	  * \param subjects the resulting LabeledSkeleton objects.
	  * \param labels the labels (SpacePaddedString vector) as found in a c3d file.
	  * \param skel_info the expected names and structure of each skeleton.
	  * \result value contains the labels that could not be classified as a
	  *  skel_info label. It contains indices in the labels vector.
	  */
	std::vector<unsigned> fill_skeletons(std::vector<LabeledSkeleton> &subjects,
					std::vector<SpacePaddedString> const &labels,
					SkeletonInfo const &skel_info);

	
	/**
	 * @}
	 */
}

#endif // SUBJ83SNKRIWON423KHTJEIYU589
