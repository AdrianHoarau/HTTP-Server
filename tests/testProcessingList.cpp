/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** testProcessingList.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "processingList.hpp"

Test(processSimpleAdd, processingList)
{
    processingList processList;

    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::SSL_MODULE);

    cr_assert_eq(processList.getCurrentType(), moduleType::SSL_MODULE);
}

Test(processRemoveAdd, processingList)
{
    processingList processList;

    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::SSL_MODULE);

    cr_assert_eq(processList.getCurrentType(), moduleType::SSL_MODULE);
    processList.remove();
    cr_assert_eq(processList.getCurrentType(), moduleType::PHPCGI);
}

Test(processAddAtPos, processingList)
{
    processingList processList;

    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::SSL_MODULE, 1);

    processList.remove();
    cr_assert_eq(processList.getCurrentType(), moduleType::SSL_MODULE);
}

Test(processRemoveAtPos, processingList)
{
    processingList processList;

    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::SSL_MODULE, 1);

    processList.remove(1);
    processList.remove();
    cr_assert_eq(processList.getCurrentType(), moduleType::PHPCGI);
}

Test(processAddHigher, processingList)
{
    processingList processList;

    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::SSL_MODULE, 3);

    processList.remove();
    processList.remove();
    cr_assert_eq(processList.getCurrentType(), moduleType::SSL_MODULE);
}

Test(processRemoveHigher, processingList)
{
    processingList processList;

    processList.add(moduleType::PHPCGI);

    processList.remove(10);
    cr_assert_eq(processList.getCurrentType(), moduleType::NONE);
}