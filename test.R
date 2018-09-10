xMat5 <- matrix( c(
    0.,       3.0000 ,  6.0000,
    1.0000,   4.0000, 100.0000,
    2.0000,   5.0000,   8.0000), nrow = 3, byrow = T )
xMat6 <- matrix( c(115.0000, 133.0000, 337.0000,
                   931.0000, 1003.0000, 1819.0000,
                   1933.0000, 2617.0000, 21901.0000), nrow = 3, byrow = T )
xMat7 <- matrix( 7, nrow = 3, ncol = 3 )
xMat6 <- xMat6 + xMat5 %*% t( xMat6 )
xMat6 <- xMat6 + xMat5 %*% ( xMat6 + xMat7 )
xMat6 <- xMat6 + t( xMat5 ) %*% xMat7
xMat6 <- xMat6 + t( xMat5 + xMat6 ) %*% xMat7;
xMat6 <- xMat6 + t( xMat5 ) %*% t( xMat6 )
xMat6 <- xMat5 
xMat6 <- xMat6 + ( xMat5 + xMat7 ) %*% ( xMat6 + xMat7 * 2);
xMat6 <- xMat5 
xMat6 <- xMat6 + ( xMat5 -xMat7 ) %*% ( xMat5 - 10 * xMat7 )
xMat6
