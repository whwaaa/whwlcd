del /f /q whwlcd.tar.gz
tar -zcf whwlcd.tar.gz .git
start "我的窗口标题" "C:\Users\whw\Desktop\资料文件\其他资料\FILE\ShareMem.exe" "C:\Users\whw\Desktop\projproj\screenproj\whwlcd.tar.gz"
#linux解压错误可用使用bsdtar ：yum install -y bsdtar     bsdtar -zxvf xxx.tar.gz