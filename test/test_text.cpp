#include <gtest.h>
#include "Text.h"

TTextMem TTextLink::MemHeader;

TEST (TextLink, can_create_text_link)
{
	ASSERT_NO_THROW(TTextLink t("hello"));
}


TEST(Text, can_create_text)
{
	ASSERT_NO_THROW(TText t);
}

TEST(Text, can_go_to_the_first_link)
{
	EXPECT_TRUE(false);
}