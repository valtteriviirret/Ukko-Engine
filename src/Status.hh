#ifndef STATUS_HH
#define STATUS_HH

#include "Piece.hh"
#include "Pieces.hh"

class Status
{
	public:
		Status();
		~Status();
		Status* getStatus();
		void setStatus();
		void updateStatus();

	private:
		Status* status;
};

#endif
