
um:     file format elf64-x86-64


Disassembly of section .init:

Disassembly of section .plt:

Disassembly of section .text:

00000000004011f0 <run_instruction>:
  4011f0:	41 57                	push   r15
  4011f2:	41 56                	push   r14
  4011f4:	41 55                	push   r13
  4011f6:	41 54                	push   r12
  4011f8:	55                   	push   rbp
  4011f9:	48 89 fd             	mov    rbp,rdi
  4011fc:	53                   	push   rbx
  4011fd:	89 f3                	mov    ebx,esi
  4011ff:	48 83 ec 08          	sub    rsp,0x8
  401203:	48 85 ff             	test   rdi,rdi
  401206:	0f 84 94 02 00 00    	je     4014a0 <run_instruction+0x2b0>
  40120c:	89 d8                	mov    eax,ebx
  40120e:	c1 e8 1c             	shr    eax,0x1c
  401211:	83 f8 0d             	cmp    eax,0xd
  401214:	74 2a                	je     401240 <run_instruction+0x50>
  401216:	89 da                	mov    edx,ebx
  401218:	c1 ea 06             	shr    edx,0x6
  40121b:	89 d1                	mov    ecx,edx
  40121d:	89 da                	mov    edx,ebx
  40121f:	83 e3 07             	and    ebx,0x7
  401222:	c1 ea 03             	shr    edx,0x3
  401225:	83 e1 07             	and    ecx,0x7
  401228:	83 e2 07             	and    edx,0x7
  40122b:	41 89 d4             	mov    r12d,edx
  40122e:	83 f8 0c             	cmp    eax,0xc
  401231:	0f 87 82 02 00 00    	ja     4014b9 <run_instruction+0x2c9>
  401237:	ff 24 c5 70 27 40 00 	jmp    QWORD PTR [rax*8+0x402770]
  40123e:	66 90                	xchg   ax,ax
  401240:	89 d8                	mov    eax,ebx
  401242:	81 e3 ff ff ff 01    	and    ebx,0x1ffffff
  401248:	c1 e8 19             	shr    eax,0x19
  40124b:	83 e0 07             	and    eax,0x7
  40124e:	89 5c 85 00          	mov    DWORD PTR [rbp+rax*4+0x0],ebx
  401252:	b8 01 00 00 00       	mov    eax,0x1
  401257:	48 83 c4 08          	add    rsp,0x8
  40125b:	5b                   	pop    rbx
  40125c:	5d                   	pop    rbp
  40125d:	41 5c                	pop    r12
  40125f:	41 5d                	pop    r13
  401261:	41 5e                	pop    r14
  401263:	41 5f                	pop    r15
  401265:	c3                   	ret    
  401266:	66 2e 0f 1f 84 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]
  40126d:	00 00 00 
  401270:	31 c0                	xor    eax,eax
  401272:	eb e3                	jmp    401257 <run_instruction+0x67>
  401274:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  401278:	48 85 ed             	test   rbp,rbp
  40127b:	0f 84 43 03 00 00    	je     4015c4 <run_instruction+0x3d4>
  401281:	8b 7c 9d 00          	mov    edi,DWORD PTR [rbp+rbx*4+0x0]
  401285:	e8 16 fc ff ff       	call   400ea0 <Segment_new>
  40128a:	48 8b 7d 38          	mov    rdi,QWORD PTR [rbp+0x38]
  40128e:	48 89 c3             	mov    rbx,rax
  401291:	e8 42 08 00 00       	call   401ad8 <Seq_length>
  401296:	85 c0                	test   eax,eax
  401298:	0f 8f c2 02 00 00    	jg     401560 <run_instruction+0x370>
  40129e:	44 8b 6d 30          	mov    r13d,DWORD PTR [rbp+0x30]
  4012a2:	44 8b 7d 34          	mov    r15d,DWORD PTR [rbp+0x34]
  4012a6:	4c 8b 75 28          	mov    r14,QWORD PTR [rbp+0x28]
  4012aa:	45 39 fd             	cmp    r13d,r15d
  4012ad:	0f 84 2a 03 00 00    	je     4015dd <run_instruction+0x3ed>
  4012b3:	44 89 e8             	mov    eax,r13d
  4012b6:	49 89 1c c6          	mov    QWORD PTR [r14+rax*8],rbx
  4012ba:	41 8d 45 01          	lea    eax,[r13+0x1]
  4012be:	89 45 30             	mov    DWORD PTR [rbp+0x30],eax
  4012c1:	44 89 e2             	mov    edx,r12d
  4012c4:	b8 01 00 00 00       	mov    eax,0x1
  4012c9:	44 89 6c 95 00       	mov    DWORD PTR [rbp+rdx*4+0x0],r13d
  4012ce:	eb 87                	jmp    401257 <run_instruction+0x67>
  4012d0:	48 85 ed             	test   rbp,rbp
  4012d3:	0f 84 d2 02 00 00    	je     4015ab <run_instruction+0x3bb>
  4012d9:	44 8b 64 9d 00       	mov    r12d,DWORD PTR [rbp+rbx*4+0x0]
  4012de:	48 8b 45 28          	mov    rax,QWORD PTR [rbp+0x28]
  4012e2:	4a 8d 3c e0          	lea    rdi,[rax+r12*8]
  4012e6:	e8 95 fe ff ff       	call   401180 <Segment_free>
  4012eb:	48 8b 45 28          	mov    rax,QWORD PTR [rbp+0x28]
  4012ef:	4a 83 3c e0 00       	cmp    QWORD PTR [rax+r12*8],0x0
  4012f4:	74 14                	je     40130a <run_instruction+0x11a>
  4012f6:	ba ab 01 00 00       	mov    edx,0x1ab
  4012fb:	be 5b 27 40 00       	mov    esi,0x40275b
  401300:	bf e8 3d 60 00       	mov    edi,0x603de8
  401305:	e8 6e 03 00 00       	call   401678 <Except_raise>
  40130a:	48 8b 7d 38          	mov    rdi,QWORD PTR [rbp+0x38]
  40130e:	4c 89 e6             	mov    rsi,r12
  401311:	e8 86 0b 00 00       	call   401e9c <Seq_addlo>
  401316:	b8 01 00 00 00       	mov    eax,0x1
  40131b:	e9 37 ff ff ff       	jmp    401257 <run_instruction+0x67>
  401320:	8b 7c 9d 00          	mov    edi,DWORD PTR [rbp+rbx*4+0x0]
  401324:	48 8b 35 b5 2d 20 00 	mov    rsi,QWORD PTR [rip+0x202db5]        # 6040e0 <stdout@@GLIBC_2.2.5>
  40132b:	e8 90 f6 ff ff       	call   4009c0 <putc@plt>
  401330:	b8 01 00 00 00       	mov    eax,0x1
  401335:	e9 1d ff ff ff       	jmp    401257 <run_instruction+0x67>
  40133a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  401340:	48 8b 3d a9 2d 20 00 	mov    rdi,QWORD PTR [rip+0x202da9]        # 6040f0 <stdin@@GLIBC_2.2.5>
  401347:	e8 04 f7 ff ff       	call   400a50 <getc@plt>
  40134c:	83 f8 ff             	cmp    eax,0xffffffff
  40134f:	0f 84 2b 02 00 00    	je     401580 <run_instruction+0x390>
  401355:	99                   	cdq    
  401356:	c1 ea 18             	shr    edx,0x18
  401359:	01 d0                	add    eax,edx
  40135b:	0f b6 c0             	movzx  eax,al
  40135e:	29 d0                	sub    eax,edx
  401360:	89 44 9d 00          	mov    DWORD PTR [rbp+rbx*4+0x0],eax
  401364:	b8 01 00 00 00       	mov    eax,0x1
  401369:	e9 e9 fe ff ff       	jmp    401257 <run_instruction+0x67>
  40136e:	66 90                	xchg   ax,ax
  401370:	48 85 ed             	test   rbp,rbp
  401373:	0f 84 19 02 00 00    	je     401592 <run_instruction+0x3a2>
  401379:	44 89 e2             	mov    edx,r12d
  40137c:	8b 44 95 00          	mov    eax,DWORD PTR [rbp+rdx*4+0x0]
  401380:	85 c0                	test   eax,eax
  401382:	0f 85 58 01 00 00    	jne    4014e0 <run_instruction+0x2f0>
  401388:	8b 44 9d 00          	mov    eax,DWORD PTR [rbp+rbx*4+0x0]
  40138c:	89 45 20             	mov    DWORD PTR [rbp+0x20],eax
  40138f:	b8 01 00 00 00       	mov    eax,0x1
  401394:	e9 be fe ff ff       	jmp    401257 <run_instruction+0x67>
  401399:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  4013a0:	8b 54 9d 00          	mov    edx,DWORD PTR [rbp+rbx*4+0x0]
  4013a4:	b8 01 00 00 00       	mov    eax,0x1
  4013a9:	85 d2                	test   edx,edx
  4013ab:	0f 84 a6 fe ff ff    	je     401257 <run_instruction+0x67>
  4013b1:	44 89 e2             	mov    edx,r12d
  4013b4:	8b 74 95 00          	mov    esi,DWORD PTR [rbp+rdx*4+0x0]
  4013b8:	89 ca                	mov    edx,ecx
  4013ba:	89 74 95 00          	mov    DWORD PTR [rbp+rdx*4+0x0],esi
  4013be:	e9 94 fe ff ff       	jmp    401257 <run_instruction+0x67>
  4013c3:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  4013c8:	89 d2                	mov    edx,edx
  4013ca:	48 8b 45 28          	mov    rax,QWORD PTR [rbp+0x28]
  4013ce:	8b 54 95 00          	mov    edx,DWORD PTR [rbp+rdx*4+0x0]
  4013d2:	48 8b 04 d0          	mov    rax,QWORD PTR [rax+rdx*8]
  4013d6:	8b 54 9d 00          	mov    edx,DWORD PTR [rbp+rbx*4+0x0]
  4013da:	48 8b 40 08          	mov    rax,QWORD PTR [rax+0x8]
  4013de:	8b 04 90             	mov    eax,DWORD PTR [rax+rdx*4]
  4013e1:	89 ca                	mov    edx,ecx
  4013e3:	89 44 95 00          	mov    DWORD PTR [rbp+rdx*4+0x0],eax
  4013e7:	b8 01 00 00 00       	mov    eax,0x1
  4013ec:	e9 66 fe ff ff       	jmp    401257 <run_instruction+0x67>
  4013f1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  4013f8:	89 ca                	mov    edx,ecx
  4013fa:	48 8b 45 28          	mov    rax,QWORD PTR [rbp+0x28]
  4013fe:	8b 74 9d 00          	mov    esi,DWORD PTR [rbp+rbx*4+0x0]
  401402:	8b 54 95 00          	mov    edx,DWORD PTR [rbp+rdx*4+0x0]
  401406:	48 8b 04 d0          	mov    rax,QWORD PTR [rax+rdx*8]
  40140a:	44 89 e2             	mov    edx,r12d
  40140d:	8b 54 95 00          	mov    edx,DWORD PTR [rbp+rdx*4+0x0]
  401411:	48 8b 40 08          	mov    rax,QWORD PTR [rax+0x8]
  401415:	89 34 90             	mov    DWORD PTR [rax+rdx*4],esi
  401418:	b8 01 00 00 00       	mov    eax,0x1
  40141d:	e9 35 fe ff ff       	jmp    401257 <run_instruction+0x67>
  401422:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  401428:	89 d2                	mov    edx,edx
  40142a:	8b 44 9d 00          	mov    eax,DWORD PTR [rbp+rbx*4+0x0]
  40142e:	03 44 95 00          	add    eax,DWORD PTR [rbp+rdx*4+0x0]
  401432:	89 44 8d 00          	mov    DWORD PTR [rbp+rcx*4+0x0],eax
  401436:	b8 01 00 00 00       	mov    eax,0x1
  40143b:	e9 17 fe ff ff       	jmp    401257 <run_instruction+0x67>
  401440:	89 d2                	mov    edx,edx
  401442:	8b 44 95 00          	mov    eax,DWORD PTR [rbp+rdx*4+0x0]
  401446:	0f af 44 9d 00       	imul   eax,DWORD PTR [rbp+rbx*4+0x0]
  40144b:	89 44 8d 00          	mov    DWORD PTR [rbp+rcx*4+0x0],eax
  40144f:	b8 01 00 00 00       	mov    eax,0x1
  401454:	e9 fe fd ff ff       	jmp    401257 <run_instruction+0x67>
  401459:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  401460:	89 d2                	mov    edx,edx
  401462:	8b 44 95 00          	mov    eax,DWORD PTR [rbp+rdx*4+0x0]
  401466:	31 d2                	xor    edx,edx
  401468:	f7 74 9d 00          	div    DWORD PTR [rbp+rbx*4+0x0]
  40146c:	89 44 8d 00          	mov    DWORD PTR [rbp+rcx*4+0x0],eax
  401470:	b8 01 00 00 00       	mov    eax,0x1
  401475:	e9 dd fd ff ff       	jmp    401257 <run_instruction+0x67>
  40147a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  401480:	89 d2                	mov    edx,edx
  401482:	8b 44 95 00          	mov    eax,DWORD PTR [rbp+rdx*4+0x0]
  401486:	23 44 9d 00          	and    eax,DWORD PTR [rbp+rbx*4+0x0]
  40148a:	f7 d0                	not    eax
  40148c:	89 44 8d 00          	mov    DWORD PTR [rbp+rcx*4+0x0],eax
  401490:	b8 01 00 00 00       	mov    eax,0x1
  401495:	e9 bd fd ff ff       	jmp    401257 <run_instruction+0x67>
  40149a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  4014a0:	ba 4b 00 00 00       	mov    edx,0x4b
  4014a5:	be 5b 27 40 00       	mov    esi,0x40275b
  4014aa:	bf e8 3d 60 00       	mov    edi,0x603de8
  4014af:	e8 c4 01 00 00       	call   401678 <Except_raise>
  4014b4:	e9 53 fd ff ff       	jmp    40120c <run_instruction+0x1c>
  4014b9:	ba 8c 00 00 00       	mov    edx,0x8c
  4014be:	be 5b 27 40 00       	mov    esi,0x40275b
  4014c3:	bf e8 3d 60 00       	mov    edi,0x603de8
  4014c8:	e8 ab 01 00 00       	call   401678 <Except_raise>
  4014cd:	b8 01 00 00 00       	mov    eax,0x1
  4014d2:	e9 80 fd ff ff       	jmp    401257 <run_instruction+0x67>
  4014d7:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  4014de:	00 00 
  4014e0:	48 8b 7d 28          	mov    rdi,QWORD PTR [rbp+0x28]
  4014e4:	4c 8b 3c c7          	mov    r15,QWORD PTR [rdi+rax*8]
  4014e8:	e8 93 fc ff ff       	call   401180 <Segment_free>
  4014ed:	48 8b 45 28          	mov    rax,QWORD PTR [rbp+0x28]
  4014f1:	48 83 38 00          	cmp    QWORD PTR [rax],0x0
  4014f5:	74 14                	je     40150b <run_instruction+0x31b>
  4014f7:	ba f0 01 00 00       	mov    edx,0x1f0
  4014fc:	be 5b 27 40 00       	mov    esi,0x40275b
  401501:	bf e8 3d 60 00       	mov    edi,0x603de8
  401506:	e8 6d 01 00 00       	call   401678 <Except_raise>
  40150b:	4c 89 ff             	mov    rdi,r15
  40150e:	45 31 e4             	xor    r12d,r12d
  401511:	e8 ca fb ff ff       	call   4010e0 <Segment_length>
  401516:	89 c7                	mov    edi,eax
  401518:	41 89 c5             	mov    r13d,eax
  40151b:	e8 80 f9 ff ff       	call   400ea0 <Segment_new>
  401520:	49 89 c6             	mov    r14,rax
  401523:	45 85 ed             	test   r13d,r13d
  401526:	74 29                	je     401551 <run_instruction+0x361>
  401528:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  40152f:	00 
  401530:	44 89 e6             	mov    esi,r12d
  401533:	4c 89 ff             	mov    rdi,r15
  401536:	e8 d5 fb ff ff       	call   401110 <Segment_get>
  40153b:	44 89 e6             	mov    esi,r12d
  40153e:	4c 89 f7             	mov    rdi,r14
  401541:	41 83 c4 01          	add    r12d,0x1
  401545:	89 c2                	mov    edx,eax
  401547:	e8 e4 f8 ff ff       	call   400e30 <Segment_put>
  40154c:	45 39 e5             	cmp    r13d,r12d
  40154f:	75 df                	jne    401530 <run_instruction+0x340>
  401551:	48 8b 45 28          	mov    rax,QWORD PTR [rbp+0x28]
  401555:	4c 89 30             	mov    QWORD PTR [rax],r14
  401558:	e9 2b fe ff ff       	jmp    401388 <run_instruction+0x198>
  40155d:	0f 1f 00             	nop    DWORD PTR [rax]
  401560:	48 8b 7d 38          	mov    rdi,QWORD PTR [rbp+0x38]
  401564:	e8 c3 07 00 00       	call   401d2c <Seq_remlo>
  401569:	48 8b 55 28          	mov    rdx,QWORD PTR [rbp+0x28]
  40156d:	41 89 c5             	mov    r13d,eax
  401570:	89 c0                	mov    eax,eax
  401572:	48 89 1c c2          	mov    QWORD PTR [rdx+rax*8],rbx
  401576:	e9 46 fd ff ff       	jmp    4012c1 <run_instruction+0xd1>
  40157b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  401580:	c7 44 9d 00 ff ff ff 	mov    DWORD PTR [rbp+rbx*4+0x0],0xffffffff
  401587:	ff 
  401588:	b8 01 00 00 00       	mov    eax,0x1
  40158d:	e9 c5 fc ff ff       	jmp    401257 <run_instruction+0x67>
  401592:	ba e8 01 00 00       	mov    edx,0x1e8
  401597:	be 5b 27 40 00       	mov    esi,0x40275b
  40159c:	bf e8 3d 60 00       	mov    edi,0x603de8
  4015a1:	e8 d2 00 00 00       	call   401678 <Except_raise>
  4015a6:	e9 ce fd ff ff       	jmp    401379 <run_instruction+0x189>
  4015ab:	ba a4 01 00 00       	mov    edx,0x1a4
  4015b0:	be 5b 27 40 00       	mov    esi,0x40275b
  4015b5:	bf e8 3d 60 00       	mov    edi,0x603de8
  4015ba:	e8 b9 00 00 00       	call   401678 <Except_raise>
  4015bf:	e9 15 fd ff ff       	jmp    4012d9 <run_instruction+0xe9>
  4015c4:	ba 77 01 00 00       	mov    edx,0x177
  4015c9:	be 5b 27 40 00       	mov    esi,0x40275b
  4015ce:	bf e8 3d 60 00       	mov    edi,0x603de8
  4015d3:	e8 a0 00 00 00       	call   401678 <Except_raise>
  4015d8:	e9 a4 fc ff ff       	jmp    401281 <run_instruction+0x91>
  4015dd:	43 8d 04 3f          	lea    eax,[r15+r15*1]
  4015e1:	4c 89 f7             	mov    rdi,r14
  4015e4:	89 45 34             	mov    DWORD PTR [rbp+0x34],eax
  4015e7:	48 8d 34 c5 00 00 00 	lea    rsi,[rax*8+0x0]
  4015ee:	00 
  4015ef:	e8 1c f4 ff ff       	call   400a10 <realloc@plt>
  4015f4:	48 89 45 28          	mov    QWORD PTR [rbp+0x28],rax
  4015f8:	49 89 c6             	mov    r14,rax
  4015fb:	48 85 c0             	test   rax,rax
  4015fe:	74 2e                	je     40162e <run_instruction+0x43e>
  401600:	8b 45 34             	mov    eax,DWORD PTR [rbp+0x34]
  401603:	44 8b 6d 30          	mov    r13d,DWORD PTR [rbp+0x30]
  401607:	41 39 c7             	cmp    r15d,eax
  40160a:	0f 83 a3 fc ff ff    	jae    4012b3 <run_instruction+0xc3>
  401610:	83 e8 01             	sub    eax,0x1
  401613:	4b 8d 3c fe          	lea    rdi,[r14+r15*8]
  401617:	31 f6                	xor    esi,esi
  401619:	44 29 f8             	sub    eax,r15d
  40161c:	48 8d 14 c5 08 00 00 	lea    rdx,[rax*8+0x8]
  401623:	00 
  401624:	e8 67 f3 ff ff       	call   400990 <memset@plt>
  401629:	e9 85 fc ff ff       	jmp    4012b3 <run_instruction+0xc3>
  40162e:	ba 86 01 00 00       	mov    edx,0x186
  401633:	be 5b 27 40 00       	mov    esi,0x40275b
  401638:	bf e8 3d 60 00       	mov    edi,0x603de8
  40163d:	e8 36 00 00 00       	call   401678 <Except_raise>
  401642:	4c 8b 75 28          	mov    r14,QWORD PTR [rbp+0x28]
  401646:	eb b8                	jmp    401600 <run_instruction+0x410>

Disassembly of section .fini:
