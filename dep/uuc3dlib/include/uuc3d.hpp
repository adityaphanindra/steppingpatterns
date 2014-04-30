#ifndef UUC3D_38DHJWTOANTQ
#define UUC3D_38DHJWTOANTQ

// vim:set tabstop=4 cindent:

// Author: Geert-Jan Giezeman <geert@cs.uu.nl>
// Copyright: Utrecht University, 2011

/*! \file
\brief Header file declaring C3d functionality by Utrecht University
*/

#include "basic_io.hpp"
#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>

/** \namespace UuIcsC3d
  * \brief Main namespace of Utrecht University C3d support.
  */
namespace UuIcsC3d
{

	/**
	 * \defgroup C3dExcept C3d exception types
	 * @{
	 */

	/** \struct PreconditionError
	  * PreconditionError is thrown in cases where an invalid call is made.
	  */
    struct PreconditionError
    {
    };

	//! OpenError is thrown if a file cannot be opened
    struct OpenError
    {
		/**
		  * @param [in] filename Name of the file that could not be opened.
		  */
        OpenError(std::string const &filename)
            : m_filename(filename) {}
		/**
		  * Get the name of the file.
		  */
        std::string filename() const {return m_filename;}
    private:
        std::string m_filename;
    };

	//! ContentError is thrown if the content of a file is not valid.
    struct ContentError
    {
		/**
		  * Constructor.
		  * @param msg A message that describes what is not valid.
		  * @param filename The name of the file (may be empty string).
		  */
        ContentError(std::string const &msg, std::string const &filename)
            : m_msg(msg), m_filename(filename) {}
		//! Get the name of the file.
        std::string filename() const {return m_filename;}
		//! Get the message.
        std::string msg() const {return m_msg;}
    private:
        std::string m_msg;
        std::string m_filename;
    };

	/**
	 * @}
	 */
}

namespace UuIcsC3d
{

//	typedef uint16_t unsigned16_t;
	//! Type used for 16 bit wide unsigned integers..
	typedef unsigned short unsigned16_t;

	/**
	 * \defgroup C3dLL Low level C3d functionality
	 * @{
	 * \brief The low level interface is close to the C3d file format.
	 * A basic understanding of the C3D specification is necessary to
	 * understand it.
	 *
	 * The low level interface is accessed from the high level
	 * UuIcsC3d::C3dFileinfo class. The main access class is UuIcsC3d::Content,
	 * which holds the content of the header and parameter sections. Another
	 * class is UuIcsC3d::FileInfo1, which holds the most important parameters.
	 * This class is only used internally.
	 */


	/**
	  * A C3d file is divided in blockes of 512 bytes (or 256 words).
	  * When referring to these bytes or blocks, we use 1-based indexes,
	  * just like the specification does. In the API, we use 0-based indexes,
	  * which is usual in C-based languages.
	  */
    typedef unsigned char Block[512];

	/**
	  * Represents the events in the C3d header section
	  * (words 150-234 of the first block of the file)
	  */
	struct HeaderEvent {
	    //! The event label
		std::string label;
		//! The display flag (true is ON)
		bool displayed;
		//! the event time in seconds
		float time;
	};

	/**
	  * Represent the first block (512 bytes or 256 16-bit words)
	  * of a C3d file.
	  * The data in this structure are in close correspondence with the header
	  * as found in a C3d file. E.g., indexes start at 1.
	  * \ingroup C3dLL
	  */
	struct Header {
		//! The number of trajectories.
		int trajectory_count;
		//! The total number of analog data per frame (channels time
		//! samples per frame.
		int analog_per_frame;
		//! The number of the first frame (1 based)
		int first_frame;
		//! The number of the last frame (1 based)
		int last_frame;
		//! The largest gap that was filled.
		int max_interpolation_gap;
		//! The 3d scale factor.
		float scaling_factor;
		//! The number of the first block of the 3d data.
		int data_start_block;
		//! The number of analog samples per 3d frame.
		int analog_samples_per_frame;
		//! The frame rate in Hz.
		float frame_rate;
		//! Whether label and range data are present.
		bool has_label_and_range;
		//! The first block of the label and range data.
		int label_and_range_block;
		//! The header events.
		std::vector<HeaderEvent> events;
	};

	//! The common part of groups and parameters
    struct GroupParamCommon
    {
		//! Default constructor. Data needs to be filled in later.
        GroupParamCommon(): m_id(0) {}
		/**
		  * Constructor.
		  * @param locked Whether this element is locked (only used when writing
		  * @param id A non negative integer identifier.
		  * a C3d file).
		  * @param name The name of the element.
		  * @param description A description of the parameter.
		  */
        GroupParamCommon(bool locked, int id, std::string const &name,
				std::string const &description)
            : m_locked(locked),m_id(id), m_name(name),
              m_description(description) {}
		//! Get the numeric identifier.
        int id() const
        { return m_id; }
		//! Set the numeric identifier.
        void set_id(int id)
        { m_id = id; }
		//! Whether this value is locked.
		//! This library doesn't restrict access to locked values.
		//! It is up to the library deal with locked parameters.
		bool is_locked() const
		{ return m_locked; }
		//! Make this value locked.
		//! This only influences how a C3d file is written.
		void set_locked(bool value)
		{ m_locked = value; }
		//! Get the name of a group or parameter.
        std::string name() const
        { return m_name; }
		//! Set the name of a group or parameter.
        void set_name(std::string name)
        { m_name = name; }
		//! Get the description of a group or parameter.
        std::string description() const
        { return m_description; }
		//! Set the description of a group or parameter.
        void set_description(std::string const &description)
        { m_description = description; }
    protected:
		//! locked value
		bool m_locked;
		//! Group or parameter id
        int m_id;
		//! name value
        std::string m_name;
		//! description value
        std::string m_description;
    };

	/** A C3d parameter
	  * A parameter is a multidimensional array (up to 7 dimensions)
	  * of type char, byte, short (16 bit value) or float (32 bit).
	  */
    struct Parameter: GroupParamCommon
    {
		/**
		  * An enum describing the four base types that a parameter can contain.
		  */
        enum DataType {DtChar=-1, DtByte=1, DtShort=2, DtFloat=4};
		/**
		  * Constructs an empty parameter.
		  * An empty parameter is not valid in a C3d file, so values like
		  * id, name, data type and value will have to be set later.
		  */
		Parameter() {}
		/**
		  * Construct a complete parameter.
		  * @param [in] locked Whether this parameter is locked.
		  * @param [in] id Numeric identifier.
		  * @param [in] name Name of the parameter.
		  * @param [in] data_type One of the enumeration types indicating the
		  * type stored in the multidimensional array.
		  * @param [in] dimension_size Vector describing the number and sizes of
		  * the array dimensions. Each dimension size should be positive and
		  * not larger than 256.
		  * @param [in] data_start Begin iterator of an array of unsigned chars
		  * storing the raw data of the array.
		  * @param [in] data_end (Past the) end iterator of an array of
		  * unsigned chars storing the raw data of the array.
		  * @param [in] description Description of the parameter.
		  * @param [in] io Shared pointer to an IO object for decoding the raw
		  * character data.
		  */
        Parameter(bool locked, int id, std::string name, int data_type,
            std::vector<int> const &dimension_size,
			unsigned char const*data_start, unsigned char const*data_end,
            std::string const &description, boost::shared_ptr<BasicIO> io);
		//! \name Accessors
		//! @{

		//! Get the data type of the array elements.
        DataType data_type() const { return m_data_type; }
		//! Get the bounds of the multidimensional array.
        std::vector<int> bounds() const { return m_dimension_size; }
		/** Get a byte.
		  * @param [in] index The index (0 based) in the multidimensional array.
		  * @pre The data type must be DtByte.
		  * @pre check_index(index) must be true.
		  */
        unsigned char get_byte(std::vector<int> const &index) const;
		/**
		  * Short form for getting a byte for the case that the data array is
		  * one dimensional.
		  */
        unsigned char get_byte(int i1) const;
		/**
		  * Shorter form for get_byte for the case that the there is exactly
		  * one value in the data array.
		  */
        unsigned char get_the_byte() const;
		/** Get a character.
		  * @param [in] index The index (0 based) in the multidimensional array.
		  * @pre The data type must be DtChar.
		  * @pre check_index(index) must be true.
		  */
        char get_char(std::vector<int> const &index) const;
		/**
		  * Short form for getting a char for the case that the data array is
		  * one dimensional.
		  */
        char get_char(int i1) const;
		/**
		  * Shorter form for get_char for the case that the there is exactly
		  * one value in the data array.
		  */
        char get_the_char() const;
		/**
		  * Returns true iff de tata type is DtChar and the array is one or
		  * higher dimensional.
		  */
		bool contains_string() const;
		/**
		  * Returns the string indicated by index.
		  * All strings in a parameter have the same length. The last value of
		  * the bounds indicates the length of each string.
		  * \pre Data type is DtChar.
		  * \pre check_string_index(index) would return true.
		  */
        std::string get_string(std::vector<int> const &index) const;
		/**
		  * Short form of getting a string for the case that the data array is
		  * two dimensional (so can be seen as a one dimensional string array).
		  */
		std::string get_string(int i1) const;
		/**
		  * Shorter form for get_string for the case that the there is exactly
		  * one string in the data array.
		  */
        std::string get_the_string() const;
		/** Get a short integer.
		  * @param [in] index The index (0 based) in the multidimensional array.
		  * @pre The data type must be DtShort.
		  * @pre check_index(index) must be true.
		  */
        int get_short(std::vector<int> const &index) const;
		/**
		  * Short form for get_short for the case that the data array is
		  * one dimensional.
		  */
        int get_short(int i1) const;
		/**
		  * Shorter form for get_short for the case that the there is exactly
		  * one value in the data array.
		  */
        int get_the_short() const;
		/** Get an unsigned short integer.
		  * @param [in] index The index (0 based) in the multidimensional array.
		  * @pre The data type must be DtShort.
		  * @pre check_index(index) must be true.
		  */
        unsigned get_ushort(std::vector<int> const &index) const;
		/**
		  * Short form for get_ushort for the case that the data array is
		  * one dimensional.
		  */
        unsigned get_ushort(int i1) const;
		/**
		  * Shorter form for get_ushort for the case that the there is exactly
		  * one value in the data array.
		  */
        unsigned get_the_ushort() const;
		/** Get a float.
		  * @param [in] index The index (0 based) in the multidimensional array.
		  * @pre The data type must be DtFloat.
		  * @pre check_index(index) must be true.
		  */
        float get_float(std::vector<int> const &index) const;
		/**
		  * Short form for get_float for the case that the data array is
		  * one dimensional.
		  */
        float get_float(int i1) const;
		/**
		  * Shorter form for get_float for the case that the there is exactly
		  * one value in the data array.
		  */
        float get_the_float() const;
		/**
		  * Size (in bytes) that this parameter will take when written to a C3d
		  * file.
		  */
		int representation_size() const;
		/**
		  * The uninterpreted character data as found in the C3d file.
		  */
		std::vector<unsigned char> const &raw_data() const
		{ return m_data;}
		/**
		  * Checks whether index is valid with respects to the array bounds.
		  * The dimension (number of elements) must be the same as the dimension
		  * of bounds and for every dimension the value should non negative and
		  * less than the value of bounds of that dimension.
		  */
        bool check_index(std::vector<int> const &index) const;
		/**
		  * Check whether index is valid for a string access.
		  * This is equivalent to appending a 0 to index and then calling
		  * check_index(index)
		  */
        bool check_string_index(std::vector<int> const &index) const;
		//! @}
		//! \name Mutating operations
		//! This part of the interface is not yet complete.
		//! @{
		/**
		  * Set the value of the single unsigned short.
		  * @pre The data type must be DtShort.
		  * @pre There must be exactly one value (all bounds are 1).
		  */
		void set_the_ushort(unsigned16_t val);
		/**
		  * Set the value of an unsigned short.
		  * @pre The data type must be DtShort.
		  * @pre There data array must be one dimensional.
		  */
		void set_ushort(int i1, unsigned16_t val);
		/**
		  * Places an array of strings in the data array and adapts the bounds.
		  * All strings will be padded with the pad character such that they
		  * are as long as the longest initial string.
		  * @pre The data type must be DtChar.
		  */
		void set_strings(std::vector<std::string> const &strings, char pad);
		//! @}
    private:
        int get_offset(int data_size, std::vector<int> const &index) const;
		int get_string_offset(std::vector<int> const &index) const;
        DataType m_data_type;
        std::vector<int> m_dimension_size;
		std::vector<unsigned char> m_data;
		boost::shared_ptr<BasicIO> m_io; // decoder of binary data, appropriate for input file
    };

	/**
	  * A group of C3d parameters.
	  * Every parameter in a C3d file belongs to a group.
	  */
    struct Group: GroupParamCommon
    {
		/**
		  * Construct a group without data.
		  * At least the id and name of the group should be set later.
		  */
        Group()  {}
		/**
		  * Construct a group with only its id.
		  * At least the name of the group should be set later.
		  */
        Group(int id)
            : GroupParamCommon(false, id, std::string(), std::string()) {}
		/**
		  * Construct a group with all of its attributes.
		  */
        Group(bool locked, int id, std::string name,
				std::string const &description)
            : GroupParamCommon(locked, id, name, description) {}
		/**
		  * Add a aparmeter to this group.
		  */
        void add_parameter(Parameter const &param);
		/**
		 * Whether this group has a parameter with this name.
		 */
        bool has_parameter(std::string const &name) const;
		/**
		  * Retrieves a parameter of this group by name.
		  * @param [in] name The name of the parameter.
		  * @result The parameter with this name.
		  * @pre A parameter with this name exists.
		  */
        Parameter const &get_parameter(std::string const &name) const;
		/**
		  * Retrieves a parameter of this group by name.
		  * @param [in] name The name of the parameter.
		  * @result The parameter with this name.
		  * @pre A parameter with this name exists.
		  */
        Parameter &get_parameter(std::string const &name);
		/**
		  * Retrieves a parameter of this group by name.
		  * @param [in] name The name of the parameter.
		  * @result Pointer to the parameter with this name.
		  * Null pointer if this parameter does not exist.
		  */
		Parameter const *get_parameter_checked(std::string const &name) const;
		/**
		  * Retrieves a parameter of this group by name.
		  * @param [in] name The name of the parameter.
		  * @result Pointer to the parameter with this name.
		  * Null pointer if this parameter does not exist.
		  */
		Parameter *get_parameter_checked(std::string const &name);
		/**
		  * Get all parameters in this group.
		  */
		std::vector<Parameter> const &the_parameters() const
		{ return m_parameters;}
		/**
		  * The size (in bytes) that this group and all its parameters
		  * will take in a C3d file.
		  */
		int total_representation_size() const;
		/**
		  * The size (in bytes) that this group will take in a C3d file,
		  * not including the parameters belonging to this group.
		  */
		int group_representation_size() const;
    private:
        std::vector<Parameter> m_parameters;
    };

	//! Stores the header and parameter data of a C3d file
    class Content
    {
		Header m_header;
		//! decoder of binary data, appropriate for input file
		boost::shared_ptr<BasicIO> m_io; 
        std::vector<Group> m_groups;
		void parse_params(std::vector<unsigned char> const &);
        std::string m_filename;
    public:
		Content();
		/** Opens a C3d file and reads the header and parameter section.
		  * \param [in] filename Name of the file. This name will be stored.
		  * \throw UuIcsC3d::OpenError if file cannot be opened.
		  * \throw UuIcsC3d::ContentError if file contains erroneous content.
		  */
        void open(std::string const &filename);
		/**
		  * Get the header (first block) of the C3d file.
		  */
        Header const &header() const 
        {return m_header;};
		/**
		  * Get the header (first block) of the C3d file.
		  */
        Header &header() 
        {return m_header;};
		/**
		  * Get the encoder/decoder for this C3d file.
		  */
        boost::shared_ptr<BasicIO> io() const
        { return m_io;}
        //std::string group_name(int gid) const;
		/**
		  * Checks whether a group with this name exists.
		  */
        bool has_group(std::string const &name) const;
		/**
		  * Retrieves a group by name.
		  * @param [in] name The name of the group.
		  * @result The group with this name.
		  * @pre has_group(name).
		  */
        Group const &get_group(std::string const &name) const;
		/**
		  * Retrieves a group by name.
		  * @param [in] name The name of the group.
		  * @result The group with this name.
		  * @pre has_group(name).
		  */
        Group &get_group(std::string const &name);
		/**
		  * Retrieves a group by name.
		  * @param [in] name The name of the group.
		  * @result A pointer to the group with this name if this group exists,
		  * else a null pointer.
		  */
        Group const *get_group_checked(std::string const &name) const;
		/**
		  * Retrieves a group by name.
		  * @param [in] name The name of the group.
		  * @result A pointer to the group with this name if this group exists,
		  * else a null pointer.
		  */
        Group *get_group_checked(std::string const &name);
		/**
		  * @result Get all groups.
		  */
		std::vector<Group> const & the_groups() const { return m_groups;}
		/**
		  * The name of the file as supplied to the last call to open.
		  */
		std::string filename() const { return m_filename; }
    };

	//! Opens a C3d file, read the header and parameter section and return a
	//! UuIcsC3d::Content object.
    Content open_c3d_file(char const *filename);
	//! Opens a C3d file, read the header and parameter section and return a
	//! UuIcsC3d::Content object.
    Content open_c3d_file(std::string const &filename);

	//! The most important general data of a C3d file.
	struct FileInfo1 {
		//! 0 based block number of start of data.
		int data_startblock0;
		//! The number of frames.
		int frame_count;
		//! The number of marker points in each frame.
		int points_per_frame;
		//! The number of analog channels per frame.
		int analog_channels;
		//! How many analog samples are taken during each frame.
		int samples_per_frame;
		//! The size in bytes of the data of a single frame.
		int frame_size;
		//! The scaling factor for converting integer coordinates to floating point
		float point_scale;
		//! Whether the file contains integer data (or floating point).
		bool is_integer;
	};

	/**
	 * @}
	 */

}

namespace UuIcsC3d
{

	/**
	 * \defgroup C3dHL High level C3d functionality
	 *
	 * @{
	 */

	//!  A single marker point as found in a C3d file
	struct DataPoint3d {
		//! A point can be measured, generated by some computation or invalid
		enum Status { Generated=1, Measured=2, Invalid=64};
	  private:
		float m_coords[3];
		float m_residual;
		char m_mask; // (bits 0-6 can indicate a camera)
		Status m_type;
		unsigned16_t m_flags;
	  public:
		//! Typedef used for return type of coordinates function
		typedef float const (&CTripleF)[3];
		//! Initialises to an Invalid point.
		DataPoint3d(): m_residual(-1), m_mask(0), m_type(Invalid), m_flags(0)
			{m_coords[0]=0; m_coords[1]=0;m_coords[2]=0;}
		//! @{

		//! Set the value of the point.
		//! Residual and camera mask can not be set in this way and should
		//! be set separately, if necessary.
		//! @param[in] x x-coordinate
		//! @param[in] y y-coordinate
		//! @param[in] z z-coordinate
		//! @param[in] f Flags (an unsigned int of 16 bits, for user purposes)
		//! @param[in] v The status of this point (measured, generated or invalid)
		void set_value(float x, float y, float z, unsigned f,
						Status v = Generated);
		//! Set the value of the point.
		//! Residual and camera mask can not be set in this way and should
		//! be set separately, if necessary.
		//! @param[in] in_coordinates A pointer to three floats (x, y, z)
		//! @param[in] f Flags (an unsigned int of 16 bits, for user purposes)
		//! @param[in] v The status of this point (measured, generated or invalid)
		void set_value(float const*in_coordinates, unsigned f,
						Status v = Generated);
		//! Set the value of the point.
		//! Residual and camera mask can not be set in this way and should
		//! be set separately, if necessary.
		//! @param[in] in_coordinates A pointer to three doubles (x, y, z)
		//! @param[in] f Flags (an unsigned int of 16 bits, for user purposes)
		//! @param[in] v The status of this point (measured, generated or invalid)
		void set_value(double const*in_coordinates, unsigned f,
						Status v = Generated);
		//! Make the point invalid
		void invalidate() { m_type = Invalid; }
		//! Sets the mask
		void set_mask(char mask)
		{ m_mask = mask;}
		//! Sets the residual value
		void set_residual(float r)
		{ m_residual = r;}
		//! @}

		//! @{

		//! The status of a point can be Invalid, Measured (by cameras) or
		//! Generated (by some computation).
		Status status() const {return m_type;}
		//! false if the status is Invalid, otherwise true.
		bool is_valid() const { return m_type==Generated || m_type==Measured; }
		//! The x, y and z coordinates as an array.
		CTripleF coordinates() const {return m_coords;}
		//! The x coordinate of a point
		float x() const { return m_coords[0];}
		//! The y coordinate of a point
		float y() const { return m_coords[1];}
		//! The z coordinate of a point
		float z() const { return m_coords[2];}
		//! A user defined 16 bit unsigned value that can be stored with a point.
		//! This only works when coordinates are stored as floats and is an
		//! extension that is not sanctioned by the C3d spec. It uses some
		//! space that is not used in the current spec.
		unsigned flags() const {return m_flags;}
		//! A mask indicating which cameras were used for measuring the position
		char mask() const {return m_mask;}
		//! A measure for indicating the error for measured points
		float residual() const {return m_residual;}
		//! @}
	};

	//! The data of a single frame
	struct FrameData {
		//! The trajectory data.
		std::vector<DataPoint3d> points;
		//! The analog data.  analog_data[c][s] is sample s of channel c.
		std::vector< std::vector<float> > analog_data; 
	};

    //! A string that is padded with spaces (e.g. to fit in a unform length array)
	struct SpacePaddedString {
		//! Construct an empty string
		SpacePaddedString() :m_size(0) {}
		//! Construct a string
		//! @param [in] str Initialising string.
		SpacePaddedString(std::string const &str):m_val(str) {compute_size();}
		//! Return the complete string, spaces included.
		std::string complete() const {return m_val;}
		//! Return the string but with spaces stripped.
		std::string stripped() const {return m_val.substr(0, m_size);}
		//! Set the string
		void set(std::string const &str) {m_val = str; compute_size(); }
	private:
		std::string m_val;
		std::string::size_type m_size;
		void compute_size();
	};

	class C3dFile;

	//! Class for storing data from the parameter section of a C3d file.
	class C3dFileInfo {
		Content m_content;
		FileInfo1 m_fi1;
		std::vector<SpacePaddedString> m_labels;
	public:
		//! \name Constructors
		//! @{

		/*! Constructs an object where is_valid() returns false. */
		C3dFileInfo();
		/*! Initialises the file by reading the parameter section of the named file
		  May throw OpenError if a the file can not be opened for reading.
		  May throw ContentError if the content of the file is not valid.
		  @param [in] filename The name of the file to be openened.
		   */
		C3dFileInfo(std::string const &filename);
		//! @}

		//! \name Accessors
		//! @{

		//! If the parameter section was read succesfully, this will return
		//! true. Otherwise, it will return false.
		bool is_valid() const; 
		//! The number of frames in this file.
		int frame_count() const { return m_fi1.frame_count; }
		//! The number of points in each frame.
		//! You can also view this as the number of trajectories in the file,
		//! as each trajectory will have exactly one point in each frame.
		int points_per_frame() const { return m_fi1.points_per_frame; }
		//! The labels for the points.
		//! The number of labels need not be the same as the number of points.
		//! label[i] will be a name for point[i] if i is valid for both.
		std::vector<SpacePaddedString> point_labels() const
		{ return m_labels; }
		//! The number of analog channels.
		int analog_channels() const { return m_fi1.analog_channels; }
		//! The rate at which analog data is stored can be higher than the frame
		//! rate. E.g., analog data can be sampled at 100Hz while trajectories
		//! are sampled at 25 Hz. In that case, this function will return 4.
		int analog_samples_per_frame() const { return m_fi1.samples_per_frame; }
		//! Reopens the file (using the same name that was supplied at the
		//! constructor) and returns an auto_ptr to a file that can be used
		//! for reading the frame data. The destructor that will be called
		//! automatically when the auto_ptr goes out of scope will close the
		//! file.
		std::auto_ptr<C3dFile> open() const;
		//! @}

		//! \name Mutating operations
		//! @{
		//! These functions set values and are directly related to the accessor
	    //!	functions with a similar name. They can be used if this object is
		//! used in writing a C3d file.

		/**
		  * Sets the number of 512 byte parameter blocks (and thus the data start).
		  */
		void set_param_blocks(int c) ;
		/**
		  * Sets the number of frames.
		  */
		void set_frame_count(int) ;
		/**
		  * Sets the number of marker points.
		  */
		void set_points_per_frame(int) ;
		/**
		  * Sets the total number of analog data per frame.
		  */
		void set_analog_samples_per_frame(int) ;
		/**
		  * Sets the number of analog channels.
		  */
		void set_analog_channels(int) ;
		/**
		  * Sets labels for the marker points.
		  * The number of labels need not be the same as the number of marker
		  * points. If necessary, the labels will be padded with the pad
		  * character, such that all labels have the same length.
		  */
		void set_point_labels(std::vector<std::string> const &labels,
						char pad = ' ');
		//! @}

		//! \name Access to low level interface
		//! @{

		/**
		  * Get the low level Content structure.
		  */
		Content const &content() const { return m_content; }
		/**
		  * Get the low level FileInfo1 structure.
		  */
		FileInfo1 const &fi1() const { return m_fi1; }
		//! @}
	};

	//! Class for reading frame data of a C3d file
	class C3dFile {
		C3dFile(C3dFile const &in); // not implemented: no copying
		struct Impl;
		boost::scoped_ptr<Impl> m_impl;
	public:
		//! Constructor @param[in] fi C3d file information
		C3dFile(C3dFileInfo const &fi);
		~C3dFile();
		//! Get the data of one frame
		//! @param[out] data will be filled with the data
		//! @param[in] frame_no is the number of the frame (0 based)
		//! Should be less than the value of frame_count in the
		//! corresponding C3dFileInfo object.
		void get_frame_data(FrameData &data, int frame_no) const;
		//! Get the data of one point
		//! @param[in] frame_no is the number of the frame (0 based).
		//! Should be less than the value of frame_count in the
		//! corresponding C3dFileInfo object.
		//! @param[in] point_no the number of the point (0 based).
		//! Should be less than the value of points_per_frame in the
		//! corresponding C3dFileInfo object.
		DataPoint3d get_point(int frame_no, int point_no) const;
	};

	//! Deprecated function
	bool write_with_same_header(std::string const &fn, C3dFileInfo const &fi,
					std::vector<FrameData> const &data);

//	bool write(std::string const &fn, C3dFileInfo const &fi, std::vector<FrameData> const &data, UuIcsC3d::BasicIO const* encoder);
	/*! Write a c3dfile
	  @param[in] fn is the name of the file that is written
	  @param[in] fi is the header information that is to be written
	  @param[in] data is the trajectory data
	  @param[in] encoder is the encoder that is to be used. Only the Intel
	  encoder is supported at the moment.
	  */
	bool write(std::string const &fn, C3dFileInfo fi, std::vector<FrameData> const &data, UuIcsC3d::BasicIO const* encoder);

/**
  * @}
  */

}

#endif // UUC3D_38DHJWTOANTQ
