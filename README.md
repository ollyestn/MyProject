# MyProject
A UE5 First Person Project

1、class AMyActor:
	CreateSpline(): 蓝图可调用方法，在ConstructScript()中调用，生成样条曲线USplineComponent，只可以在Editor中使用，Play()状态下不可见，可用于在编辑器中规划路径点等。
	
	CreateSplineActor()
	蓝图可调用方法，用于生成ASplineActor类的实例。
	
2、class ASplineActor:	
	SetSplinePoints ():	设置Spline的顶点
	CreateSplineMesh(): 生成线条Mesh
	
	USplineComponent* Spline: 线条组件
	UStaticMesh* SplineStaticMesh: 线条使用的静态mesh
	ESplineMeshAxis::Type ForwardAxis: Mesh的朝向
	
	另外：发光（通过材质），流动（速度参数）
	
	
	
	
	
