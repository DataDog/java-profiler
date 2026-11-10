---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 08:11:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 10 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (4 unique values: 74-93 cores)</summary>

```
1794316046 76
1794316051 78
1794316056 78
1794316061 78
1794316066 78
1794316071 78
1794316076 78
1794316081 78
1794316086 78
1794316091 78
1794316096 78
1794316101 78
1794316106 78
1794316111 78
1794316116 93
1794316121 93
1794316126 93
1794316131 93
1794316136 93
1794316141 93
```
</details>

---

