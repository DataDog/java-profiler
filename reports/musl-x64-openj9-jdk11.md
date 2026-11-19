---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:28:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 926 |
| Sample Rate | 15.43/sec |
| Health Score | 964% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 65-82 cores)</summary>

```
1795108864 68
1795108869 73
1795108874 73
1795108879 73
1795108884 73
1795108889 73
1795108894 73
1795108899 73
1795108904 73
1795108909 73
1795108914 73
1795108919 73
1795108924 73
1795108929 73
1795108934 82
1795108939 82
1795108944 82
1795108949 82
1795108955 82
1795108960 82
```
</details>

---

