#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_12.5/Main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(UnitTest)
    {
    public:

        TEST_METHOD(TestStackMinMaxPositions)
        {
            Node* head;
            Node* tail;
            int values[] = { 37, 102, 8, 63, 21, 9, 44, 3, 77 };
            int n = sizeof(values) / sizeof(values[0]);

            createList(head, tail, values, n);

            std::stack<int> stack;

            Node* current = head;
            while (current != nullptr) {
                stack.push(current->data);
                current = current->next;
            }

            int max_val = stack.top();
            int min_val = stack.top();
            int max_pos = 1;
            int min_pos = 1;
            int pos = 1;

            stack.pop();

            while (!stack.empty()) {
                pos++;
                int val = stack.top();
                if (val > max_val) {
                    max_val = val;
                    max_pos = pos;
                }
                if (val < min_val) {
                    min_val = val;
                    min_pos = pos;
                }
                stack.pop();
            }

            // Free memory allocated for the linked list
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }

            Assert::AreEqual(102, max_val);
            Assert::AreEqual(2, n - max_pos + 1); // Corrected position calculation
            Assert::AreEqual(3, min_val);
            Assert::AreEqual(8, n - min_pos + 1); // Corrected position calculation
        }
    };
}
