call ndk-build clean
call ndk-build TARGET_LINK=0 NDK_DEBUG=0 CONFIGURATION=StaticRelease
call ndk-build TARGET_LINK=0 NDK_DEBUG=1 CONFIGURATION=StaticDebug
rmdir /s /q libs
rmdir /s /q obj
call ndk-build clean
call ndk-build TARGET_LINK=1 NDK_DEBUG=0 CONFIGURATION=DynamicRelease
call ndk-build TARGET_LINK=1 NDK_DEBUG=1 CONFIGURATION=DynamicDebug
rmdir /s /q libs
rmdir /s /q obj
rem xcopy /y ..\..\..\..\BuildFiles\Android\arm64-v8a\StaticRelease\libD39330A106574FC38508EC1C37BBB18A.a %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\arm64-v8a\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\arm64-v8a\DynamicRelease\libD39330A106574FC38508EC1C37BBB18A.so %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\arm64-v8a\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi\StaticRelease\libD39330A106574FC38508EC1C37BBB18A.a %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\armeabi\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi\DynamicRelease\libD39330A106574FC38508EC1C37BBB18A.so %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\armeabi\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi-v7a\StaticRelease\libD39330A106574FC38508EC1C37BBB18A.a %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\armeabi-v7a\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi-v7a\DynamicRelease\libD39330A106574FC38508EC1C37BBB18A.so %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\armeabi-v7a\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips\StaticRelease\libD39330A106574FC38508EC1C37BBB18A.a %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\mips\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips\DynamicRelease\libD39330A106574FC38508EC1C37BBB18A.so %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\mips\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips64\StaticRelease\libD39330A106574FC38508EC1C37BBB18A.a %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\mips64\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips64\DynamicRelease\libD39330A106574FC38508EC1C37BBB18A.so %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\mips64\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86\StaticRelease\libD39330A106574FC38508EC1C37BBB18A.a %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\x86\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86\DynamicRelease\libD39330A106574FC38508EC1C37BBB18A.so %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\x86\DynamicRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86_64\StaticRelease\libD39330A106574FC38508EC1C37BBB18A.a %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\x86_64\StaticRelease\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86_64\DynamicRelease\libD39330A106574FC38508EC1C37BBB18A.so %ECO_FRAMEWORK%\Lab2\BuildFiles\Android\x86_64\DynamicRelease\
pause
