protoc.exe -I=./ --cpp_out=./ ./ProtocolClientToServer.proto
protoc.exe -I=./ --cpp_out=./ ./ProtocolClientToServerEnum.proto
protoc.exe -I=./ --cpp_out=./ ./ProtocolServerToClient.proto
protoc.exe -I=./ --cpp_out=./ ./ProtocolServerToClientEnum.proto
IF ERRORLEVEL 1 PAUSE