/**
 * @file ITextAnalyzer.hpp
 * @author Dinesh Subhuraaj (dineshsubhuraaj@gmail.com)
 * @brief  
 * @version 0.1
 * @date 2022-08-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include<string>

/**
 * @brief TODO
 * 
 */
class ITextAnalyzer
{
    public:
        /**
         * @brief 
         * 
         */
        virtual void findSmileyPositions(std::string) = 0;
        
        /**
         * @brief 
         * 
         */
        virtual void findTenMostUsedWords(std::string) = 0;
};