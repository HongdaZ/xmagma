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
xMat6 <- xMat6 - xMat5 %*% xMat7
xMat6 <- xMat6 - xMat5 %*% t( xMat6 )
xMat6 <- xMat6 - xMat5 %*% ( xMat6 - 2 * xMat7 )
xMat6 <- xMat6 - t( xMat5 ) %*% xMat7
xMat6 <- xMat6 - ( xMat5 -xMat7 ) %*% xMat7
xMat6 <- xMat6 - t( xMat5 ) %*% t( xMat6 )
xMat6 <- xMat6 - ( xMat5 - 2 * xMat7 ) %*% t( xMat6 + 3 * xMat7 )
xV4 <- c( -8, 86, -6 )
xV5 <- c( 1, 2.55741, -1.18504 )
xMat6 <- xMat5
xV4 <- c( 0.561985,
          -107.274344,
          5.306721)
xV4 <- xMat6 %*% xV4
xV6 <- t( xV5 ) %*% xMat6
xV4 <- t( xMat6 ) %*% xV4;
xV6 <-  xV6 %*% xMat6
xV6 <- xV6 + xV5
xV7 <- c( 0.561985, -107.274344, 5.306721 )
xV6 <- xV6 - xV7
xV6 <- xV6 * 5
xV6 <- xV6 / 100
xV6 %*% xV4 
xV4 %*% xV6
xV6 <- xV6 + xV5 + 2 * xV7
xV6 <- xV6 + xV5 + xV7 * 2
xV6 <- xV5 * 2
xV6 <- ( xV5 + xV7 )* 2;
xV6 <- xV7 / 2
xV6 <- ( xV5 + xV7 ) / 2
xV6 <- - xV7
xV6 <- -( xV5 + xV7 ) 
xV6 <- ( xV5 + xV5 + xV7 * 2 )
xV6 <- ( xV5 + t( xV4 ) )
xV6 <- xV5 + ( - ( xV5 + xV6 ) )
xV6 <- xV5 * 2 + ( - ( xV5 + xV6 ) )
xV6
xV6 <- xV5 / 2 - ( - (  3 * xV5 + xV6 + t( xV4 ) ) )
xV6 <- xV5 %*% xMat6 + xV5
xV5 %*% xMat6 %*% xV4

xV5 %*% xMat6 %*% xV5 
xV5 %*% xMat6 %*% ( xV5  + xV4 )
t( xV4 ) %*% xV5
xV3 <- t( t( c( 1, 3, -2 ) ) )
xV4 <- t( t( c( 2, 3, 5 ) ) )
xV5 <- t( c( 7, 13, 11 ) )
xV6 <- t( c( 17, 19, 23 ) )
t( 2 * xV4 - xV3 / 2 ) %*% t( 2 * xV5 * 2 / 2 + xV6 * 2 ) 
xV3 <- xMat6 %*% xV4
xV7 <- xV6 %*% xMat6
