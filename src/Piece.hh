#ifndef PIECE_HH
#define PIECE_HH

#include <string>

typedef struct Piece
{
	std::string type;
	bool color;
	bool alive;
	// location
    int x, y;
} Piece;

/*
 * Piece* positions[8][8] = {
 *          wr,      wh,       wb,     wk,      wq,      wb,      wh,      wr,
 *          wp,      wp,       wp,     wp,      wp,      wp,      wp,      wp,
 *     nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
 *     nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
 *     nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
 *     nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
 *          bp,      bp,       bp,     bp,      bp,      bp,      bp,      bp,
 *          br,      bh,       bb,     bk,      bq,      bb,      bh,      br,
 * };
 */

#endif

