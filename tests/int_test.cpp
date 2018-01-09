#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include "simple_msgs/int.h"
#include <time.h>
#include <stdlib.h>

// TEST FOR USING THE INT MESSAGE WRAPPER

SCENARIO("Using a Int Message")
{
	int int_1 = static_cast<int>(rand()) / RAND_MAX;
	int int_2 = static_cast<int>(rand()) / RAND_MAX;
	// Testing constructors.
	GIVEN("A Int created from an empty constructor")
	{
		simple_msgs::Int empty_int;
		WHEN("We check the Int's value")
		{
			THEN("It has to be zero") { REQUIRE(empty_int.get() == 0); }
		}
	}

	GIVEN("A Int created from a int")
	{
		simple_msgs::Int single_int(int_1);
		WHEN("We check the Int's value")
		{
			THEN("It has to be equal to the params from the constructor") { REQUIRE(single_int.get() == int_1); }
		}
	}

	// Testing copy-constructors.
	GIVEN("A Int")
	{
		simple_msgs::Int single_int(int_1);
		WHEN("I construct a new Int from the serialized data of the existing Int")
		{
			simple_msgs::Int copy_buffer_int(single_int.getBufferData());
			THEN("The new Int has to be equal to the other") { REQUIRE(copy_buffer_int == single_int); }
		}
		WHEN("I copy-construct a new Int")
		{
			simple_msgs::Int copy_int(single_int);
			THEN("The new Int is equal to the other") { REQUIRE(copy_int == single_int); }
		}
		WHEN("I move-construct a new Int")
		{
			simple_msgs::Int moved_int(std::move(single_int));
			THEN("The new Int's value is equal to the previous' one")
			{
				REQUIRE(moved_int.get() == single_int.get());
			}
		}
	}

	// Testing copy-assignments.
	GIVEN("A Int")
	{
		simple_msgs::Int single_int(int_1);
		WHEN("I copy-assign from that Int's buffer")
		{
			simple_msgs::Int copy_assigned_buffer_int;
			copy_assigned_buffer_int = single_int.getBufferData();
			THEN("The new Int has to be same as the original") { REQUIRE(copy_assigned_buffer_int == single_int); }
		}
		WHEN("I copy-assign from that Int")
		{
			simple_msgs::Int copy_assigned_int;
			copy_assigned_int = single_int;
			THEN("The new Int has to be same as the original") { REQUIRE(copy_assigned_int == single_int); }
		}
		WHEN("I move-assign from that Int")
		{
			simple_msgs::Int move_assigned_int;
			move_assigned_int = std::move(single_int);
			THEN("The new Int has to be same as the original") { REQUIRE(move_assigned_int.get() == int_1); }
		}
	}

	// Testing getter-setter
	GIVEN("An instance of a Int.")
	{
		// start a Int
		simple_msgs::Int d;

		WHEN("I set the value of the Int")
		{
			int x = static_cast<int>(rand()) / RAND_MAX;
			d.set(x);
			THEN("The Int's value is correct") { REQUIRE(d.get() == x); }
		}
	}

	// Testing operations.
	GIVEN("Two identical Ints")
	{
		simple_msgs::Int single_int_1(int_1);
		simple_msgs::Int single_int_2(int_1);
		WHEN("I compare these Ints")
		{
			THEN("They have to be equal") { REQUIRE(single_int_1 == single_int_2); }
		}
		WHEN("I change the first Int")
		{
			single_int_1.set(int_2);
			THEN("They have to be different") { REQUIRE(single_int_1 != single_int_2); }
		}
	}

	GIVEN("A Int")
	{
		simple_msgs::Int single_int(int_1);
		WHEN("I increase the value of the int_")
		{
			single_int++;
			THEN("The new value is correct") { REQUIRE(single_int.get() == int_1 + 1.0); }
		}
		WHEN("I decrease the value of the int_")
		{
			single_int--;
			THEN("The new value is correct") { REQUIRE(single_int.get() == int_1 - 1.0); }
		}
		WHEN("I add to the value of the int_")
		{
			single_int += 2.0;
			THEN("The new value is correct") { REQUIRE(single_int.get() == int_1 + 2.0); }
		}
		WHEN("I subtract from the value of the int_")
		{
			single_int -= 5.0;
			THEN("The new value is correct") { REQUIRE(single_int.get() == int_1 - 5.0); }
		}
		WHEN("I add a int to the int_")
		{
			simple_msgs::Int added_int = single_int + 6.0;
			THEN("The new value is correct") { REQUIRE(added_int.get() == int_1 + 6.0); }
		}
		WHEN("I subtract a int of the int_")
		{
			simple_msgs::Int subtracted_int = single_int - 6.0;
			THEN("The new value is correct") { REQUIRE(subtracted_int.get() == int_1 - 6.0); }
		}
		WHEN("I multiply to the value of the int_")
		{
			single_int *= 2.0;
			THEN("The new value is correct") { REQUIRE(single_int.get() == int_1 * 2.0); }
		}
		WHEN("I divide from the value of the int_")
		{
			single_int /= 5.0;
			THEN("The new value is correct") { REQUIRE(single_int.get() == int_1 / 5.0); }
		}
		WHEN("I multiply a int to the int_")
		{
			simple_msgs::Int multiplied_int = single_int * 6.0;
			THEN("The new value is correct") { REQUIRE(multiplied_int.get() == int_1 * 6.0); }
		}
		WHEN("I divide the int by a int_")
		{
			simple_msgs::Int divided_int = single_int / 6.0;
			THEN("The new value is correct") { REQUIRE(divided_int.get() == int_1 / 6.0); }
		}
		WHEN("I get the message topic")
		{
			std::string topic_name = single_int.getTopic();
			THEN("I get the correct one") { REQUIRE(topic_name == "INTG"); }
		}
	}
}
