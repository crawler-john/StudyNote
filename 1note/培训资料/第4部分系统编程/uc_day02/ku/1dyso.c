#include <stdio.h>
#include <dlfcn.h>

typedef int(*PFUNC_CAL)(int,int);
typedef void(*PFUNC_SHOW)(int,char,int,int);

int main()
{
	//加载共享库
	void *handle = dlopen("shared/libmath.so",RTLD_LAZY);
	if(handle==NULL)
	{
		printf("dlopen失败:%s\n",dlerror());
		return -1;
	}

	//获取函数地址
	PFUNC_CAL add = (PFUNC_CAL)dlsym(handle,"add");
	if(add==NULL)
	{
		//获取错误信息
		printf("dlsym失败:%s\n",dlerror());
		return -1;
	}

	PFUNC_CAL sub = (PFUNC_CAL)dlsym(handle,"sub");
	if(sub==NULL)
	{
		printf("dlsym失败:%s\n",dlerror());
		return -1;
	}

	PFUNC_SHOW show = (PFUNC_SHOW)dlsym(handle,"show");
	if(show==NULL)
	{
		printf("dlsym失败:%s\n",dlerror());
		return -1;
	}

	show(30,'+',20,add(30,20));
	show(30,'-',20,sub(30,20));

	//卸载共享库
	dlclose(handle);

	return 0;
}


