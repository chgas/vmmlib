#include "matrix_test.hpp"

#include <vmmlib/matrix.hpp>
#include <vmmlib/vector.hpp>

#include <sstream>

namespace vmml
{

bool
matrix_test::run()
{
    bool ok = true;
    
    matrix< 2, 3, double > m0;
    double data[] = { 1, 2, 3, 4, 5, 6 };
    
    
    // iterator set test
    {
        matrix< 2, 3, double > m_correct;
        m_correct( 0, 0 )   = 1;
        m_correct( 0, 1 )   = 2;
        m_correct( 0, 2 )   = 3;
        m_correct( 1, 0 )   = 4;
        m_correct( 1, 1 )   = 5;
        m_correct( 1, 2 )   = 6;
        
        m0.set( data, data + 6 );

        bool ok = m0 == m_correct;

        if ( ok )
        {
            matrix< 4, 4, double > m_c2;
            m_c2( 0, 0 )    = 1;
            m_c2( 0, 1 )    = 2;
            m_c2( 0, 2 )    = 3;
            m_c2( 0, 3 )    = 4;
            m_c2( 1, 0 )    = 5;
            m_c2( 1, 1 )    = 6;
            m_c2( 1, 2 )    = 7;
            m_c2( 1, 3 )    = 8;
            m_c2( 2, 0 )    = 9;
            m_c2( 2, 1 )    = 10;
            m_c2( 2, 2 )    = 11;
            m_c2( 2, 3 )    = 12;
            m_c2( 3, 0 )    = 13;
            m_c2( 3, 1 )    = 14;
            m_c2( 3, 2 )    = 15;
            m_c2( 3, 3 )    = 16;
            
            double m2_data[] = 
                { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
            matrix< 4, 4, double > m2;
            m2.set( m2_data, m2_data + 16 );
            
            ok = m2 == m_c2;
            
            std::cout << m2 << std::endl;
            std::cout << m_c2 << std::endl;
        }
        log( "iterator set", ok );
    
    }
    
    
    
    m0.set( data, data + 6 );
    
    // test operator== / operator !=
    {
        bool ok = true;
		matrix< 2, 3, double > m0_copy;
		m0.set( data, data + 6 );
		m0_copy.set( data, data + 6 );
		ok = m0 == m0_copy;
		if ( ok )
		{
			ok = ! ( m0 != m0_copy );
		}
		log( "operator==, operator!=", ok );
		if ( ! ok )
		{
			std::stringstream error;
			error << m0 << m0_copy << std::endl;
			log_error( error.str() );
		}
	}

    // test equal
    {
        bool ok = true;
		matrix< 2, 3, double > m0_copy;
		m0.set( data, data + 6 );
		m0_copy.set( data, data + 6 );
        m0( 0, 0 ) += 0.00000005;
        bool oper_ok = m0 == m0_copy;
        bool eq_ok = m0.equals( m0_copy, 0.0000001 );
		if ( ! oper_ok && eq_ok )
            ok = true;
        else 
            ok = false;
		log( "equals( ..., tolerance )", ok );
		if ( ! ok )
		{
			std::stringstream error;
			error << m0 << m0_copy << std::endl;
			log_error( error.str() );
		}
	}

    // test copy ctor
    {
        bool ok = true;
		matrix< 2, 3, double > m0_copy( m0 );
		ok = m0 == m0_copy;
		if ( ok )
		{
			ok = ! ( m0 != m0_copy );
		}
		log( "copy constructor", ok );
		if ( ! ok )
		{
			std::stringstream error;
			error << m0 << m0_copy << std::endl;
			log_error( error.str() );
		}
	}


    // test ::IDENTITY / ::ZERO
    {
        bool ok = true;
		matrix< 5, 5, double > identity( matrix< 5, 5, double >::IDENTITY );
		matrix< 5, 2, double > zero( matrix< 5, 2, double >::ZERO );
        
        double id_data[] = { 1,0,0,0,0, 0,1,0,0,0,  0,0,1,0,0, 0,0,0,1,0, 0,0,0,0,1 };
		matrix< 5, 5, double > id_correct;
        id_correct = id_data;
        
        double zero_data[] = { 0,0,0,0,0, 0,0,0,0,0 };
		matrix< 5, 2, double > zero_correct;
        zero_correct = zero_data;
        
		ok = identity == id_correct;
        if ( ok ) ok = zero == zero_correct;

		log( "static IDENTITY, ZERO members", ok );
		if ( ! ok )
		{
			std::stringstream error;
			error 
                << "identity "  << identity 
                << "zero "      << zero
                << std::endl;
			log_error( error.str() );
		}
	}

    // test operator+, operator +=
    {
        bool ok = true;
        
        matrix< 2, 2, double > m0, m1;
        double m0_data[] = { 1, 2, 3, 4 };
        double m1_data[] = { 2, 3, 4, 5 };
        m0 = m0_data;
        m1 = m1_data;
        
        matrix< 2, 2, double > result;
        double result_data[] = { 3, 5, 7, 9 };
        result = result_data;
        
        ok = result == m0 + m1;
        
        if ( ok )
        {
            m0 = m0_data;
            m0 += m1;
            ok = result == m0;
        }
		log( "matrix addition: operator+, operator+=", ok );
	}



    // test operator+, operator +=
    {
        bool ok = true;
        
        matrix< 2, 2, double > m0, m1;
        double m0_data[] = { 3, 5, 7, 9 };
        double m1_data[] = { 2, 3, 4, 5 };
        m0 = m0_data;
        m1 = m1_data;
        
        matrix< 2, 2, double > result;
        double result_data[] = { 1, 2, 3, 4 };
        result = result_data;
        
        ok = result == m0 - m1;
        
        if ( ok )
        {
            m0 = m0_data;
            m0 -= m1;
            ok = result == m0;
        }
		log( "matrix subtraction: operator-, operator-=", ok );
	}


    // test operator[]
    {
        bool ok = true;
		m0 = data;
		ok = m0[ 1 ][ 1 ] == 5;
		if ( ok )
			ok = m0[ 1 ][ 1 ] == m0.at( 1, 1 );
		if ( ok ) 
		{
			m0[ 1 ][ 2 ] = 23;
			ok = m0.at( 1, 2 ) == 23;
		}
		
		log( "operator[]", ok );
		if ( ! ok )
		{
			std::stringstream error;
			error 
				<< " m0 " << m0 
				<< " m0[ 1 ][ 1 ] " << m0[ 1 ][ 1 ] 
				<< " m0.at( 1, 1 ) " << m0.at( 1, 1 )
				<< std::endl;
			log_error( error.str() );
		}
	}

    // test getRow/setRow/getColumn/setColumn
    {
        bool ok = true;
		matrix< 2, 3, double > M;
		double Mdata[] = { 1, 2, 3, 4, 5, 6 };
		M = Mdata;
		matrix< 1, 3, double > M_row;
        M.get_row( 1, M_row );
        
		matrix< 2, 1, double > M_column;
        M.get_column( 2, M_column );
		
		for( size_t column = 0; ok && column < 3; ++column )
		{
			ok = M.at( 1, column ) == M_row.at( 0, column );
		}

		for( size_t row = 0; ok && row < 2; ++row )
		{
			ok = M.at( row, 2 ) == M_column.at( row, 0 );
		}
		
		double Mdata_row[] = { 3, 2, 5, 4, 5, 6 };
		matrix< 2, 3, double > Mr;
		Mr = Mdata_row;
		
		M = Mdata;
		M_row.at( 0, 0 ) = 3;
		M_row.at( 0, 1 ) = 2;
		M_row.at( 0, 2 ) = 5;
		M.set_row( 0, M_row );
		for( size_t column = 0; ok && column < 3; ++column )
		{
			ok = M == Mr;
		}
		
		double Mdata_column[] = { 1, 5, 3, 4, 2, 6 };
		matrix< 2, 3, double > Mc;
		Mc = Mdata_column;
		M = Mdata;
		M_column.at( 0, 0 ) = 5;
		M_column.at( 1, 0 ) = 2;
		M.set_column( 1, M_column );
		for( size_t row = 0; ok && row < 2; ++row )
		{
			ok = M == Mc;
		}

		log( "get/set_row(),get/set_column()", ok );
		if ( ! ok )
		{
			std::stringstream error;
			error 
				<< "M " << M 
				<< "M_row " << M_row 
				<< "Mr " << Mr 
				<< "M_column " << M_column 
				<< "Mc " << Mc 
				<< std::endl;
			log_error( error.str() );
		}
	}

	
    // test transpose functionality 
    {
        bool ok = true;
		m0 = data;
        matrix< 3, 2, double > m1;
        matrix< 3, 2, double > m0t = transpose( m0 );
        m1.set( data, data + 6, false );
        
        ok = m1 == m0t;
		log( "transpose(), transpose_to()", ok );
        if ( !ok )
        {
			std::stringstream error;
			error << m1 << m0t << std::endl;
			log_error( error.str() );
		}
    }
    
    
    // test multiplication
    {
        bool ok = true;
        matrix< 2, 3, double > mul0;
        double mul0data[] = { 1, 0, 2, -1, 3, 1 };
        mul0 = mul0data;
        
        matrix< 3, 2, double > mul1;
        double mul1data[] = { 3, 1, 2, 1, 1, 0 };
        mul1 = mul1data;
        
        matrix< 2, 2, double > result;
        result.multiply( mul0, mul1 );
        
        matrix< 2, 2, double > correct_result;
        double correct_result_data[] = { 5, 1, 4, 2 };
        correct_result = correct_result_data;
        ok = result == correct_result;
    
        if ( ok )
        {
            result = mul0 * mul1;
            ok = result == correct_result;
        }
        
        if ( ok )
        {
            matrix< 2, 2, double > id2;
            identity( id2 );
            
            if ( result * id2 != result )
            {
                ok = false;
            }
        }

        if ( ok )
        {
            #if 1
            matrix< 2, 2, double > mul0, mul1;
            matrix< 2, 2, double > correct_result;
            double res_data[] = { 3, 1, 4, 1 };
            correct_result = res_data;
            #endif
            mul0.set( mul0data, mul0data + 4 );
            mul1.set( mul1data, mul1data + 4 );
            mul0 *= mul1;
            ok = mul0 == correct_result;
        }

		log( "matrix multiplication ( multiply(), operator*, operator*= )", ok );

        if ( ! ok )
        {
			std::stringstream error;
			error
				<< "result = M0 * M1 \n"
                << "M0 "        << mul0 
                << "M1 "        << mul1 
                << "result "    << result
                << std::endl;
			log_error( error.str() );
        }
    }

    // test matrix * column vector multiplication
    {
        bool ok = true;
        matrix< 4, 4, double > transform;
        double transformData[] = 
        {
            0.6555, 0.2769, 0.6948, 0.4387, 
            0.1712, 0.0462, 0.3171, 0.3816, 
            0.7060, 0.0971, 0.9502, 0.7655, 
            0, 0, 0, 1
        };
        transform = transformData;
        vector< 4, double > v;
        double vData[] = { 0.1869, 0.4898, 0.4456, 1 };
        v = vData;
        
        vector< 4, double > v_result;
        v_result = transform * v;
        
        vector< 4, double > v_correct_result;
        double vResultData[] = { 1.0064414500000000707302660885034, 
            .57752579999999997806270357614267, 
            1.3684200999999998060729922144674, 
            1. };
        v_correct_result = vResultData;
        
        ok = v_result == v_correct_result;
        
        log( "matrix * vector multiplication", ok );
        if ( ! ok )
        {
            std::stringstream ss;
            ss 
                << "A " << transform 
                << "v              " << v << "\n"
                << "v_result       " << v_result << "\n"
                << "correct result " << v_correct_result << "\n"
                << std::endl;
            log_error( ss.str() );
        }
        
    }



    // test matrix4x4 * vector3 multiplication
    {
        bool ok = true;
        matrix< 4, 4, double > transform;
        double transformData[] = 
        {
            0.6555, 0.2769, 0.6948, 0.4387, 
            0.1712, 0.0462, 0.3171, 0.3816, 
            0.7060, 0.0971, 0.9502, 0.7655, 
            0, 0, 0, 1
        };
        transform = transformData;
        vector< 3, double > v;
        double vData[] = { 0.1869, 0.4898, 0.4456 };
        v = vData;
        
        vector< 3, double > v_result;
        v_result = transform * v;
        
        vector< 3, double > v_correct_result;
        double vResultData[] =
        {   
            1.0064414500000000707302660885034, 
            .57752579999999997806270357614267, 
            1.3684200999999998060729922144674, 
            1. 
        };
        v_correct_result = vResultData;
        
        ok = v_result.equals( v_correct_result );
        
        log( "matrix4x4 * vector3 ( m4x4 * v4( v3.xyz, 1.0 ) ) multiplication", ok );
        if ( ! ok )
        {
            std::stringstream ss;
            ss 
                << "A " << transform 
                << "v              " << v << "\n"
                << "v_result       " << v_result << "\n"
                << "correct result " << v_correct_result << "\n"
                << "diff " << v_result - v_correct_result << "\n"
                << std::endl;
            log_error( ss.str() );
        }
        
    }



	#ifdef VMMLIB_SAFE_ACCESSORS
	ok = true;
	{
		matrix< 3, 2 > m;
		try
		{
			m.at( 3, 2 );
			ok = false;
		}
		catch(...)
		{}
		try
		{
			if ( ok ) m.at( 1, 1 );
		}
		catch(...)
		{
			ok = false;
		}
		try
		{
			if ( ok ) 
			{
				m[ 3 ][ 2 ];
				ok = false;
			}
		}
		catch(...)
		{}
		log( "safe accessors (debug option)", ok );
	}
	#endif

	// getSubMatrix
    {
        matrix< 2, 3, double >  m_src;
        double m_src_data[] = { 1, 2, 3, 4, 5, 6 };
        m_src = m_src_data;
        matrix< 1, 2, double >  m_sub;

        m_src.get_sub_matrix( m_sub, 1, 1 );
        
        matrix< 1, 2, double > result;
        double res_data[] = { 5, 6 };
        result = res_data;
        
        bool ok = m_sub == result;
        log( "get_sub_matrix()", ok );
	}
    
    {
        matrix< 2, 3, double >  m_src;
        double m_src_data[] = { 1, 2, 3, 4, 5, 6 };
        m_src = m_src_data;
        
        matrix< 2, 2, double >  m_sub;
        double m_sub_data[] = { 7, 8, 9, 0 };
        m_sub = m_sub_data;
        
        m_src.set_sub_matrix( m_sub, 0, 1 );
        
        matrix< 2, 3, double > result;
        double res_data[] = { 1, 7, 8, 4, 9, 0 };
        result = res_data;
        
        bool ok = m_src == result;
        log( "set_sub_matrix()", ok );
    
    }


    // matrix inversion for 2x2
    {
        bool ok = true;
        matrix< 2, 2, double > M, M_inverse, M_inverse_correct;
        double Mdata[] = 
        #if 1
        { 1., 3., 4., 2. };
        #else
        {
            .81472368639317893634910205946653, .12698681629350605515327288230765,
            .90579193707561922455084868488484, .91337585613901939307623933927971
        };
        #endif
        M = Mdata;

        double M_inverse_correct_data[] = 
        #if 1
        { -0.2, 0.3, 0.4, -0.1 };
        #else
        {   1.4518186460466018239401364553487, -.20184661818884985784450236678822,
            -1.4397639425722887906999858387280,  1.2950101881184494789778227641364
        };
        #endif
        M_inverse_correct = M_inverse_correct_data;

        M.inverse( M_inverse );
               
        ok = M_inverse == M_inverse_correct;
		log( "matrix inversion for 2x2 matrices, maximum precision", ok, true );
        if ( ! ok )
        {
            ok = M_inverse.equals( M_inverse_correct, 1e-15 );
			log( "matrix inversion 2x2, tolerance: 1e-15.", ok );
        }
        if ( ! ok )
        {  
			std::stringstream error;
			error
                << "matrix M " << M 
                << "inverse (computed)" << M_inverse 
                << "inverse (correct)" << M_inverse_correct 
                << " diffs " << M_inverse - M_inverse_correct 
                << std::endl;
			log_error( error.str() );
        }
    }


    // matrix inversion for 3x3 
    {
        bool ok = true;
        matrix< 3, 3 > M, M_inverse, M_inverse_correct;
        double Mdata[] = { 8, 1, 6, 3, 5, 7, 4, 9, 2 };
        M.set( Mdata, Mdata + 9 );

        double M_inverse_correct_data[] = 
            {   .14722222222222222222222222222222, -.14444444444444444444444444444444, .63888888888888888888888888888889e-1,
                -.61111111111111111111111111111111e-1, .22222222222222222222222222222222e-1, .10555555555555555555555555555556,
                -.19444444444444444444444444444444e-1, .18888888888888888888888888888889, -.10277777777777777777777777777778 };

        M_inverse_correct.set( M_inverse_correct_data, M_inverse_correct_data + 9 );

        M.inverse( M_inverse );
        
        ok = M_inverse == M_inverse_correct;
		log( "matrix inversion for 3x3 matrices, maximum precision", ok, true );
        if ( ! ok )
        {
            ok = M_inverse.equals( M_inverse_correct, 1e-15 );
			log( "matrix inversion 3x3, tolerance: 1e-15.", ok );
        }
        if ( ! ok )
        {  
			std::stringstream error;
			error
                << "matrix M " << M 
                << "inverse (computed)" << M_inverse 
                << "inverse (correct)" << M_inverse_correct 
                << std::endl;
			log_error( error.str() );
        }
    }


    // matrix inversion for 4x4 
    {
        bool ok = true;
        matrix< 4, 4, double > M, M_inverse, M_inverse_correct;
        double Mdata[] = { 17., 24., 1., 8., 23., 5., 7., 14.,
             4., 6., 13., 20., 10., 12., 19., 21. };
        M.set( Mdata, Mdata + 16 );

        double M_inverse_correct_data[] = { -5.780346820809248e-03, 4.962205424633170e-02, -4.811027123165852e-02, 1.493997332147622e-02, 
                4.277456647398844e-02, -3.797243219208537e-02, -1.013783903957314e-02, 1.867496665184526e-02, 
                -3.930635838150288e-02, -1.333926189417519e-02, -1.333036905291240e-01, 1.508225878168074e-01, 
                1.387283236994219e-02, 1.013783903957314e-02, 1.493108048021343e-01, -1.066251667407737e-01 };

        M_inverse_correct.set( M_inverse_correct_data, M_inverse_correct_data + 16 );

        M.inverse( M_inverse );
        
        ok = M_inverse == M_inverse_correct;
		log( "matrix inversion for 4x4 matrices, maximum precision", ok, true );
        if ( ! ok )
        {
            ok = M_inverse.equals( M_inverse_correct, 1e-9 );
			log( "matrix inversion 4x4, tolerance: 1e-15.", ok );
        }
        if ( ! ok )
        {  
			std::stringstream error;
			error
                << "matrix M " << M 
                << "inverse (computed)" << M_inverse 
                << "inverse (correct)" << M_inverse_correct 
                << "diff " << M_inverse - M_inverse_correct
                << std::endl;
			log_error( error.str() );
        }
    }
    
    // set( .... )
    {
        bool ok = true;
        
        double mData[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        
        matrix< 4, 4, double > m4x4;
        matrix< 4, 4, double > m4x4C;
        m4x4C = mData;

        m4x4.set( mData, mData + 16, true );
        
        ok = m4x4 == m4x4C;
        
        m4x4C = transpose( m4x4C );
        
        m4x4.set( mData, mData + 16, false );
        
        ok = m4x4 == m4x4C;
        
        log( "set( iterator_t, bool ) ", ok );
    
    }
    
    // test direct sum
    {
        matrix< 2, 1, double > upper_left;
        double ul_data[] = { 1, 2 };
        upper_left = ul_data;
        
        matrix< 2, 3, double > lower_right;
        double lr_data[] = { 3, 4, 5, 6, 7, 8 };
        lower_right = lr_data;
        
        matrix< 4, 4, double > result;
        matrix< 4, 4, double > correct_result;
        double corr_res_data[] = {
            1, 0, 0, 0,
            2, 0, 0, 0, 
            0, 3, 4, 5, 
            0, 6, 7, 8 };
        correct_result = corr_res_data;
        
        result.direct_sum( upper_left, lower_right );
        bool ok = result == correct_result;
        log( "direct_sum", ok );
    }
    
    // test determinants
    {
        matrix< 2, 2, double >  m22;
        matrix< 3, 3, double >  m33;
        matrix< 4, 4, double >  m44;
        
        double data[] =
        {
            1,2,0,0,
            2,1,2,0,
            0,2,1,2,
            0,0,2,1
        };
        
        m44.set( data, data+16 );
        m44.get_sub_matrix( m33 );
        m33.get_sub_matrix( m22 );
        
        double  det44 = m44.det();
        double det33 = m33.det();
        double det22 = m22.det();
        
        bool ok = det44 == 5.0 && det33 == -7.0 && det22 == -3.0;
        
        log( "determinant for 2x2, 3x3 and 4x4 matrices", ok );
    }
	
	// test convolution
	{
		matrix< 4, 4, int > data;
		int test_data[] = {
            1, 2, 3, 4,
            5, 6, 7, 8, 
            9, 8, 7, 6, 
            5, 4, 3, 2 };
		matrix< 3, 3, int > kernel;
		int test_kernel[] = {
			1, 2, 3, 
			4, 5, 6, 
			7, 8, 9 };
		
		data = test_data;
		kernel = test_kernel;
		data.convolve(kernel);
		
		matrix< 4, 4, int > correct_result;
        int corr_res_data[] = {
            159, 192, 237, 264,
            297, 296, 293, 290, 
            273, 250, 217, 196, 
            231, 198, 153, 126 };
        correct_result = corr_res_data;
		bool ok = data == correct_result;
		log( "convolution", ok );
	}
    
    
    
    {
        bool ok = true;
        matrix< 4, 4, double > m;
        identity( m );
        
        vector< 3, double >  v;
        double scale[] = { 1.0, 0.0, 0.0 };
        m.pre_rotate_x( 2.3 );
        //m.scale( scale );
        
        #if 0
        if ( is_positive_definite( m ) )
        {
        
        }
        #endif
        
        std::string data;
        //m.getString( data );
        //std::cout << data << std::endl;
    }

    #ifndef VMMLIB_NO_CONVERSION_OPERATORS
    {
    
        matrix< 4, 4, double > m;
        double* array               = m;
        const double* const_array   = m;
        
        array[ 3 ] = 1.0;
        //const_array[ 3 ] = 1.0;
    }
    #endif
	
	
	{
		//test computation of norm
		matrix< 4, 4, int > data_2;
		int test_data[] = {
			1, 2, 3, 4,
			5, 6, 7, 8, 
			9, 8, 7, 6, 
			5, 4, 3, 2 };
		data_2 = test_data;
		float_t norm_check = 22.0907220343745223090082;
		float_t norm = data_2.frobenius_norm();
		ok = norm == norm_check;
		if ( ok )
		{	
			log( "matrix frobenius norm", ok  );
		} else
		{
			std::stringstream error;
			error 
			<< "matrix frobenius norm: should be: " << norm_check << " is: " << norm << std::endl;
			log_error( error.str() );
		}
	}
	
	{
		//test khatri-rao matrix product
		matrix< 3, 4, int > left;
		matrix< 4, 4, int > right;
		matrix< 12, 4, int > khatri_rao;
		matrix< 12, 4, int > khatri_rao_check;
		int data_left[] = {
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12 };
		int data_right[] = {
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12,
			13, 14, 15, 16 };
		left = data_left;
		right = data_right;
		
		int data_khatri_rao[] = {
			1,4,9,16,
			5,12,21,32,
			9,20,33,48,
			13,28,45,64,
			5,12,21,32,
			25,36,49,64,
			45,60,77,96,
			65,84,105,128,
			9,20,33,48,
			45,60,77,96,
			81,100,121,144,
			117,140,165,192 };
		khatri_rao_check = data_khatri_rao;
		
		khatri_rao = left.khatri_rao_product( right );
		
		ok = khatri_rao == khatri_rao_check;
		if ( ok )
		{	
			log( "khatri-rao matrix product ", ok  );
		} else
		{
			std::stringstream error;
			error 
			<< "khatri-rao matrix product: should be: " << std::endl 
			<< std::setprecision(24) << khatri_rao_check << std::endl 
			<< " is: " << std::endl << khatri_rao << std::endl;
			log_error( error.str() );
		}
	}
	
	
	{
		//matrix type cast
		matrix< 2, 3, float > matrix_type_a;
		matrix< 2, 3, int > matrix_type_b;
		matrix< 2, 3, int > matrix_type_b_check;
		
		matrix_type_a.fill(2.4); 
		matrix_type_b_check.fill(2);
		matrix_type_b.cast_from( matrix_type_a );
		
		if ( matrix_type_b_check == matrix_type_b )
		{	
			log( "type cast ", true  );
		} else
		{
			std::stringstream error;
			error << "type cast - matrix type float: " << std::endl << matrix_type_a << std::endl
			<< " matrix cast int should be: " << std::endl << matrix_type_b_check << std::endl
			<< " is: " << matrix_type_b << std::endl;
			log_error( error.str() );
		}		
		
	}
	
	//get_min() + get_max()
	{
		matrix< 3, 2, int >  m_get_min_max;
		m_get_min_max.zero();
		m_get_min_max.at(0,1) = 4; m_get_min_max.at(2,1) = 8;
		
		int m_min = m_get_min_max.get_min();
		int m_max = m_get_min_max.get_max();
		
		if ( (m_min == 0) && (m_max == 8) )	{	
			log( "get min/max" , true  );
		} else
		{
			std::stringstream error;
			error 
			<< "get min/max: " << std::endl
			<< "min should be: " << std::endl << 0 << " is: " << m_min << std::endl 
			<< "max should be: " << std::endl << 29 << " is: " << m_max << std::endl;
			
			log_error( error.str() );
		}	
	}
	
	//quantize
	{
		matrix< 4, 3, float >  m_raw;
		m_raw.fill(0.45692);
		m_raw.at( 2,2) = 0.67777; m_raw.at(1,0) = 0.111111; m_raw.at(2,0) = -0.23; m_raw.at(3, 0) = -0.99;
		m_raw.at(0,0) = -0.8; m_raw.at(2,1) = 0.0; m_raw.at(3,2) = 0.99; m_raw.at(1,0) = 0.23;
		matrix< 4, 3, unsigned char >  m_quant; m_quant.zero();
		matrix< 4, 3, unsigned char >  m_quant_check; 
		int data_unsigned[] = {24, 186, 186, 157, 186, 186, 98, 128, 215, 0, 186, 255};
		m_quant_check.set(data_unsigned, data_unsigned+12);
		
		float min_value = 50;
		float max_value = -50;
		
		m_raw.quantize( m_quant, min_value, max_value );
		
		matrix< 4, 3, char >  m_quant_sign; m_quant_sign.zero();
		matrix< 4, 3, char >  m_quant_sign_check; 
		int data_signed[] = {-102, 59, 59, 30, 59, 59, -29, 0, 87, -127, 59, 127};
		m_quant_sign_check.set(data_signed, data_signed +12 );
		
		m_raw.quantize( m_quant_sign, min_value, max_value );
		
	
		//dequantize
		matrix< 4, 3, float >  m_dequant;
		matrix< 4, 3, float >  m_dequant_sign;
		
		m_quant.dequantize( m_dequant, min_value, max_value );
		m_quant_sign.dequantize( m_dequant_sign, min_value, max_value );
		
		if ( ( m_quant_check == m_quant ) && ( m_quant_sign_check == m_quant_sign ) && m_dequant.equals(m_dequant_sign, 0.01) )	{	
			log( "quantize/dequantize" , true  );
		} else
		{
			std::stringstream error;
			error 
			<< "quantize/dequantize " << std::endl
			<< "raw is: " << std::endl << m_raw << std::endl 
			<< "unsigned quantized is: " << std::endl << m_quant << std::endl
			<< "signed quantized is: " << std::endl << m_quant_sign << std::endl
			<< "dequantized unsigned is: " << std::endl << m_dequant << std::endl 
			<< "dequantized signed is: " << std::endl << m_dequant_sign << std::endl 
			<< "min_value : " << min_value << " max_value: " << max_value << std::endl;
			
			log_error( error.str() );
		}	
	}
	{
		//number of nonzeros
		
		matrix< 4, 5, int > m_nnz;
		m_nnz.fill(2);
		m_nnz.at( 3,3 ) = 0; m_nnz.at( 2,3 ) = -4;
		size_t number_nonzeros = m_nnz.nnz();
		
		matrix< 4, 4, float > m_nnz2;
		m_nnz2.fill( 0.9878);
		m_nnz2.at( 3,3 ) = 0; m_nnz2.at( 2,3 ) = -1; m_nnz2.at( 2,2 ) = 0.045; m_nnz2.at( 1,2 ) = -0.085;
		m_nnz2.at( 0,2 ) = 0.00000035; m_nnz2.at( 0,1 ) = -0.00000035;
		size_t number_nonzeros2 = m_nnz2.nnz( 0.00001 );
				
		ok = ( number_nonzeros == 19 ) && (number_nonzeros2 == 13);
		log( "get number of nonzeros" , ok  );
		
	}
	
    return ok;
}




} // namespace vmml

