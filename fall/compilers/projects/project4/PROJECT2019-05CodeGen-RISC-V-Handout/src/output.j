.class public foo
.super java/lang/Object

.field public static d F
.field public static e F
.field public static a I
.field public static b I
.field public static c I

.method public static vinit()V
	.limit locals 100
	.limit stack 100
	ldc 0.0
	putstatic foo/d F
	ldc 0.0
	putstatic foo/e F
	ldc 0
	putstatic foo/a I
	ldc 0
	putstatic foo/b I
	ldc 0
	putstatic foo/c I
	return
.end method

.method public static <init>()V
	aload_0
	invokenonvirtual java/lang/Object/<init>()V
	return
.end method

.method public static main([Ljava/lang/String;)V
	.limit locals 100
	.limit stack 100
	invokestatic foo/vinit()V
	return
.end method