/* 
 * File:   xmagma_backend.h
 * Author: hzhang
 * Initialize magma and queue
 * Created on July 20, 2018, 8:23 PM
 */

#ifndef XMAGMA_BACKEND_H
#define XMAGMA_BACKEND_H

#ifdef HAVE_CUBLAS
#include "cublas_v2.h"    
#include "magma_v2.h"
#else 
#include "magma.h" // for clmagma
#endif
#include "magma_lapack.h" 

namespace xmagma {
    class Backend;
    class Queue {
    friend Backend;
    public:
        Queue(): queue( NULL ), dev( 0 ) {
            magma_init();
            magma_queue_create( dev, &queue ); }
        ~Queue(){
            magma_queue_destroy( queue );
            magma_finalize();
        }
    private:
        magma_queue_t queue;
        magma_int_t dev;
    };
    class Backend {
    public:
        static magma_queue_t& get_queue() {
            return magmaQueue.queue;
        }
        static magma_int_t& get_dev() {
            return magmaQueue.dev;
        }
        static Queue magmaQueue;
    };
    Queue Backend::magmaQueue;
}

#endif /* XMAGMA_BACKEND_H */

