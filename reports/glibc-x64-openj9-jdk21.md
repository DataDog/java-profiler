---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 12:34:14 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 54-74 cores)</summary>

```
1794850178 74
1794850183 74
1794850188 54
1794850193 54
1794850198 56
1794850203 56
1794850208 56
1794850213 56
1794850218 56
1794850223 56
1794850228 56
1794850233 56
1794850238 56
1794850243 56
1794850248 56
1794850253 56
1794850258 56
1794850263 56
1794850268 56
1794850273 56
```
</details>

---

