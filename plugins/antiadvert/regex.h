#pragma once
#include "dre2.h"

typedef struct
{
	size_t count;
	unsigned char **items;
} regex_items;

/**
 * @brief 
 * Get all matches in an array from the specified input string and regex.
 * The array should be freed with cleanup_dre2_matches()
 * @param re - DRE2 regex.
 * @param input - The input string.
 * @return regex_items* - The matches.
 */
regex_items *dre2_get_matches(struct dre2 *re, unsigned char *input);

/**
 * @brief 
 * Get all splited string in an array from the specified input string and regex.
 * The array should be freed with cleanup_dre2_matches()
 * @param re - DRE2 regex.
 * @param input - The input string.
 * @return regex_items* - The matches.
 */
regex_items *dre2_get_splits(struct dre2 *re, unsigned char *input);

/**
 * @brief 
 * Free a regex_items struct and all items.
 * @param matches 
 */
void cleanup_dre2_matches(regex_items *matches);

/**
 * @brief 
 * Get all matches in an array from the specified input string and regex.
 */
void RegexMatch(const char *input, const char *pattern);

/**
 * @brief 
 * Replace all matches with a specific string.
 */
void RegexReplace(const char* in, const char* str, const char* pattern);

/**
 * @brief 
 * Get all splited string in an array from the specified input string and regex.
 */
void RegexSplit(const char* in, const char* pattern);