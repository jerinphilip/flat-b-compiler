#include "ast.h"

void ast::program::accept(visitor::pprinter &p){ }
void ast::declarations::accept(visitor::pprinter &p){ }
void ast::id::accept(visitor::pprinter &p){ }
void ast::id_::accept(visitor::pprinter &p){ }
//void ast::expr::accept(visitor::pprinter &p){ }
void ast::code::accept(visitor::pprinter &p){ }
void ast::statement::accept(visitor::pprinter &p){ }
void ast::assign::accept(visitor::pprinter &p){ }
void ast::cblock::accept(visitor::pprinter &p){ }
void ast::while_::accept(visitor::pprinter &p){ }
void ast::if_::accept(visitor::pprinter &p){ }
void ast::for_::accept(visitor::pprinter &p){ }
void ast::print::accept(visitor::pprinter &p){ }
void ast::println::accept(visitor::pprinter &p){ }
void ast::typed_ids::accept(visitor::pprinter &p){ }
void ast::integer::accept(visitor::pprinter &p){ }
void ast::binOp::accept(visitor::pprinter &p){ }
