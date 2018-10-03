##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=aes
ConfigurationName      :=Release
WorkspacePath          :=/home/paul/Documents/crystal-eye-paul
ProjectPath            :=/home/paul/git-repo/tiny-AES-c/aes
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=paul
Date                   :=02/10/18
CodeLitePath           :=/home/paul/.codelite
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="aes.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/up_aes_client.c$(ObjectSuffix) $(IntermediateDirectory)/up_aes.c$(ObjectSuffix) $(IntermediateDirectory)/up_base64.c$(ObjectSuffix) $(IntermediateDirectory)/up_aes_simple_client.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/paul/git-repo/tiny-AES-c/aes/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/up_aes_client.c$(ObjectSuffix): ../aes_client.c $(IntermediateDirectory)/up_aes_client.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/paul/git-repo/tiny-AES-c/aes_client.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_aes_client.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_aes_client.c$(DependSuffix): ../aes_client.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_aes_client.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_aes_client.c$(DependSuffix) -MM ../aes_client.c

$(IntermediateDirectory)/up_aes_client.c$(PreprocessSuffix): ../aes_client.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_aes_client.c$(PreprocessSuffix) ../aes_client.c

$(IntermediateDirectory)/up_aes.c$(ObjectSuffix): ../aes.c $(IntermediateDirectory)/up_aes.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/paul/git-repo/tiny-AES-c/aes.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_aes.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_aes.c$(DependSuffix): ../aes.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_aes.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_aes.c$(DependSuffix) -MM ../aes.c

$(IntermediateDirectory)/up_aes.c$(PreprocessSuffix): ../aes.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_aes.c$(PreprocessSuffix) ../aes.c

$(IntermediateDirectory)/up_base64.c$(ObjectSuffix): ../base64.c $(IntermediateDirectory)/up_base64.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/paul/git-repo/tiny-AES-c/base64.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_base64.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_base64.c$(DependSuffix): ../base64.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_base64.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_base64.c$(DependSuffix) -MM ../base64.c

$(IntermediateDirectory)/up_base64.c$(PreprocessSuffix): ../base64.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_base64.c$(PreprocessSuffix) ../base64.c

$(IntermediateDirectory)/up_aes_simple_client.c$(ObjectSuffix): ../aes_simple_client.c $(IntermediateDirectory)/up_aes_simple_client.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/paul/git-repo/tiny-AES-c/aes_simple_client.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_aes_simple_client.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_aes_simple_client.c$(DependSuffix): ../aes_simple_client.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_aes_simple_client.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_aes_simple_client.c$(DependSuffix) -MM ../aes_simple_client.c

$(IntermediateDirectory)/up_aes_simple_client.c$(PreprocessSuffix): ../aes_simple_client.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_aes_simple_client.c$(PreprocessSuffix) ../aes_simple_client.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


