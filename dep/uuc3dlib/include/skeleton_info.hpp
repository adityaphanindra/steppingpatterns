#ifndef SAJKEUIWOCN389SN56702KDKF
#define SAJKEUIWOCN389SN56702KDKF

// vim:set tabstop=4 expandtab cindent:

// Author: Geert-Jan Giezeman <geert@cs.uu.nl>
// Copyright: Utrecht University, 2011

#include <string>
#include <vector>

namespace UuIcsC3d {

	/**
	 * \defgroup C3dSubjects C3d labelling of subjects
	 * The Vicon C3d files use a convention for assigning labels to subjects.
	 * A label consists of a subject name followed by a colon followed by a marker name.
	 * For instance, there may be labels Tom:lasi, Tom:rasi and Tim:lasi. That would
	 * indicate a subject Tom with labels lasi an rasi and a subject Tim with label lasi.
	 * The two main functions in this modules are fill_subjects and fill_skeletons.
     * The second deals with skeletons. Skeletons provide more structure: the markers are grouped>
	 * @{
	 */

//! \brief A range of strings with const access only.
struct ConstNameRange {
	//! Default constructor that makes an empty range.
	ConstNameRange() : m_begin(0), m_end(0) {}
	//! Constructor taling two iterators.
	ConstNameRange(std::string *begin, std::string * end): m_begin(begin), m_end(end) {}
	//! Access to begin iterator (first element).
	std::string const *begin() const {return m_begin;}
	//! Access to end iterator (beyond last element).
	std::string const *end() const {return m_end;}
private:
	std::string const *m_begin;
	std::string const *m_end;
};

//! \brief Abstract class for describing labels of a subject.
struct MarkerNames {
    //! The number of names.
	virtual int count() const;
    //! Pointer to the first name.
	virtual std::string const *begin() const = 0;
    //! Pointer beyond the last name.
	virtual std::string const *end() const = 0;
};

//! \brief Abstract class for describing skeletons.
//!
//! Usually, a skeleton consists of a number of segments that have a number of
//! markers on them. The segments are connected through joints.
//! Here, the markers are a name. Segments are called groups and have a name
//! too.
struct SkeletonInfo: MarkerNames {
	struct GrEl { int gr; int el ;};
	//! The number of groups in a skeleton
	virtual int group_count() const =0;
	//! The name of group g.
	//! \pre g should be less than group_count() and not negative.
	virtual std::string group_name(int g) const =0;
	//! The names of all members of group g.
	virtual ConstNameRange group_members(int g) const =0;
	//! List to which other groups group g is connected (through some joint).
	//! The groups are identified by 0 based indices (not larger than
	//! group_count().
	virtual std::vector<int> group_connections(int g) const =0;
	virtual GrEl to_grel(int label_no) const =0;
	virtual int to_label_no(GrEl const & grel) const =0;
};
	/**
	 * @}
	 */

}

#endif
