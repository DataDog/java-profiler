---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:28:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1795108862 23
1795108867 23
1795108872 23
1795108877 23
1795108882 23
1795108887 23
1795108892 23
1795108897 23
1795108902 23
1795108907 32
1795108912 32
1795108917 32
1795108922 32
1795108927 32
1795108932 32
1795108937 32
1795108942 32
1795108947 32
1795108952 32
1795108957 32
```
</details>

---

