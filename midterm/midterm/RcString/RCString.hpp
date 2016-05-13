/*
 * This is a reference counted string implementation.  Two RCString objects
 * that have a common ancestor and contain the original string should point to
 * the same data object.  This provides very fast copies.
 *
 * You are not allowed to use std::string in this.
 */

#ifndef CS540_RC_STRING_HPP
#define CS540_RC_STRING_HPP


namespace cs540 {


class RCString {
    private:
        class RCString_data {
            friend class RCString;
	    char *data;
            int ref_count = 0;
        };
    public:
	RCString() {}
	//Constructor
	RCString(const char* dataIn) {
		m_data = new RCString_data();
		int length = 0;
		
		//Be careful of Buffer overflows, and non-terminating nil
		char* tempPointer = const_cast<char*>(dataIn);
		while (*tempPointer != '\0') {
			++tempPointer;
			++length;
		}
		
		m_data->data = new char[length]();	
		for (int i = 0; i < length; ++i)
			m_data->data[i] = dataIn[i];
		++m_data->ref_count;
	}
	//Copy Constructor
	RCString(RCString &copyRCString) {
		m_data = copyRCString.m_data;
		--m_data->ref_count;
	}
        // Public methods.
        ~RCString() {
            // Delete the data object if the ref count goes to 0.
            if (--m_data->ref_count == 0) {
                delete m_data;
            }
        }

	//IN PROGRESS
	RCString operator+(const RCString &rc1, const RCString &rc2) {
		int length = 0;
		char* tempPointer = const_cast<char*>(rc1.m_data->data);
		for (int i = 0; *(tempPointer+(sizeof(char *)*i) ) != '\0'; ++i) {	
			++length;
		}
		char myString[length];
		for (int i = 0; i < length; ++i)
			myString[i] = tempPointer[i];
		tempPointer = const_cast<char*>(rc2.m_data->data);
		while (*tempPointer != '\0') {
			++tempPointer;
			++length;
		}
		for (int i = length; i < length; ++i)
		myString[i] = tempPointer[i];
	
		return RCSTring(strrc1.m_data
	}

    private:
        RCString_data *m_data;
};



}



#endif
