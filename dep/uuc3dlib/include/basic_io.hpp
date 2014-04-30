#ifndef BASIC_IO_EHX8AMAKEUQO3
#define BASIC_IO_EHX8AMAKEUQO3

// vim:set tabstop=4 cindent:

// Author: Geert-Jan Giezeman <geert@cs.uu.nl>
// Copyright: Utrecht University, 2011

#include <boost/shared_ptr.hpp>

namespace UuIcsC3d {
	//! Enum describing the three possible binary encodings.
	enum EncodingType {   Pt_Intel = 84, Pt_Dec = 85, Pt_Mips = 86};

	//! Class for encoding and decoding basic types to/from unsigned char sequence.
    struct BasicIO {
		//! Get the enum identifying the encoding.
		virtual EncodingType get_encoding() const =0;
		/**
		  * Decode 2 bytes to get a signed short.
		  */
        virtual short to_int16(unsigned char const *) const =0;
		/**
		  * Decode 2 bytes to get an unsigned signed short.
		  */
        virtual unsigned short to_uint16(unsigned char const *) const =0;
		/**
		  * Decode 4 bytes to get an unsigned integer.
		  */
        virtual unsigned  to_uint32(unsigned char const *) const =0;
		/**
		  * Decode 4 bytes to get an integer.
		  */
        virtual int  to_int32(unsigned char const *) const =0;
		/**
		  * Decode 4 bytes to get a float.
		  */
        virtual float to_float(unsigned char const *) const =0;
		/**
		  * Encode a short integer to 2 bytes.
		  */
        virtual void encode(unsigned char *, short int ) const =0;
		/**
		  * Encode an unsigned short integer to 2 bytes.
		  */
        virtual void encode(unsigned char *, unsigned short) const =0;
		/**
		  * Encode a float to 4 bytes.
		  */
        virtual void encode(unsigned char *, float) const =0;
		/**
		  * Encode n short integers to 2*n bytes.
		  */
        virtual void encode_array(unsigned char *, short int const *, int n ) const;
		/**
		  * Encode n unsigned short integers to 2*n bytes.
		  */
        virtual void encode_array(unsigned char *, unsigned short const *, int n) const;
		/**
		  * Encode n floats to 4*n bytes.
		  */
        virtual void encode_array(unsigned char *, float const *, int n) const;
	private:
        virtual void encode(unsigned char *, int) const;  // not implemented
        virtual void encode(unsigned char *, unsigned) const;  // not implemented
        virtual void encode_array(unsigned char *, int const *, int n) const;  // not implemented
        virtual void encode_array(unsigned char *, unsigned const *, int n) const;  // not implemented
    };

	//! Native, or otherwise preferred, encoding for this platform.
	EncodingType platform_encoding(); 

	/**
	  * Thrown in cases where an illgal value is encountered.
	  */
    struct IllegalValue {};
	/**
	  * Exception that may be thrown if a function is called that is not
	  * (fully) implemented.
	  */
    struct NotImplemented{};
	/**
	  * Get an encoder/decoder for a specific encoding type.
	  */
    boost::shared_ptr<BasicIO> get_basic_io(int pt);
	/**
	  * Get the native encoder/decoder for this platform
	  */
	boost::shared_ptr<BasicIO> get_native_io();

}

#endif // BASIC_IO_EHX8AMAKEUQO3
