/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   xmagma_operations.h
 * Author: hzhang
 *
 * Created on July 23, 2018, 12:35 PM
 */

#ifndef XMAGMA_OPERATIONS_H
#define XMAGMA_OPERATIONS_H

#include "xmagma_matrix.h"
#include "xmagma_matrix_expression.h"
#include "xmagma_R_array.h"

namespace xmagma{
    
    /* Copy matrix */
    template< typename T > 
    int copy_matrix( const Matrix< T >& mat1, 
            Matrix< T >& mat2 ){
    return 0; };
    template<>
    int copy_matrix< float >( const Matrix< float >& mat1,
            Matrix< float >& mat2 ){
        magma_scopymatrix( mat1.size1(), mat1.size2(), mat1.get_pointer(),
                mat1.ld(), mat2.get_pointer(), mat2.ld(), 
                Backend::get_queue()  );
        return 0;
    }
    template<>
    int copy_matrix< double >( const Matrix< double >& mat1,
            Matrix< double >& mat2 ){
        magma_dcopymatrix( mat1.size1(), mat1.size2(), mat1.get_pointer(),
                mat1.ld(), mat2.get_pointer(), mat2.ld(), 
                Backend::get_queue()  );
        return 0;
    }
    /* Transfer matrix from host to device */
    template< typename T > 
    void transfer_matrix( RMatrix< T >& mat1, 
            Matrix< T >& mat2 ){};
    template<>
    void transfer_matrix< float >( RMatrix< float >& mat1,
            Matrix< float >& mat2 ){
        magma_ssetmatrix( mat1.size1(), mat1.size2(), mat1.begin(),
                mat1.size1(), mat2.get_pointer(), mat2.ld(), 
                Backend::get_queue()  );
    }
    template<>
    void transfer_matrix< double >( RMatrix< double >& mat1,
            Matrix< double >& mat2 ){
        magma_dsetmatrix( mat1.size1(), mat1.size2(), mat1.begin(),
                mat1.size1(), mat2.get_pointer(), mat2.ld(), 
                Backend::get_queue()  );
    }
    
}


#endif /* XMAGMA_OPERATIONS_H */

