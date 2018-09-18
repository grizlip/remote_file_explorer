#pragma once

#include "request.h"
#include "response.h"
#include "servercommunicationmock.h"
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <serveraccess.h>
#include <QString>
#include <QStringList>
using namespace testing;
using namespace file_remote_explorer_library;

TEST(Test1, MainTestSet)
{
  //Setup
  Response r(ResponseStatus::OK, QStringList{});
  ServerCommunicationMock scm(r);
  ServerAccess sa(scm);
  QString path("Example path");

  //Execute
  sa.setNewPath(path);
  Request result = scm.getRequest();
  QString resultPath = result.getArguments().first();
  Command resultCommand = result.getCommand();

  //Assert
  EXPECT_EQ(resultCommand, COMMAND_GET_FILES_LIST);
  EXPECT_EQ(resultPath, path);
}

TEST(Test2, MainTestSet)
{
  //Setup
  Response r(ResponseStatus::OK, QStringList{"Contents of a file"});
  ServerCommunicationMock scm(r);
  ServerAccess sa(scm);
  QString path("Example path to a file");

  //Execute
  sa.getFile(path);
  Request result = scm.getRequest();
  QString resultPath = result.getArguments().first();
  Command resultCommand = result.getCommand();

  //Assert
  EXPECT_EQ(resultCommand, COMMAND_GET_FILE);
  EXPECT_EQ(resultPath, path);
}
