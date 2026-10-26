---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-26 10:05:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 841 |
| Sample Rate | 14.02/sec |
| Health Score | 876% |
| Threads | 12 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 78-86 cores)</summary>

```
1793023191 86
1793023196 86
1793023201 78
1793023206 78
1793023211 78
1793023216 78
1793023221 78
1793023226 78
1793023231 78
1793023236 78
1793023241 78
1793023246 78
1793023252 78
1793023257 78
1793023262 80
1793023267 80
1793023272 80
1793023277 80
1793023282 80
1793023287 80
```
</details>

---

