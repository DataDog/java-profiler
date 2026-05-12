---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:42:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 979 |
| Sample Rate | 16.32/sec |
| Health Score | 1020% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (3 unique values: 63-67 cores)</summary>

```
1778582227 67
1778582232 67
1778582237 67
1778582242 67
1778582247 67
1778582252 67
1778582257 67
1778582262 67
1778582267 67
1778582272 67
1778582277 67
1778582282 67
1778582287 67
1778582292 67
1778582298 63
1778582303 63
1778582308 63
1778582313 63
1778582318 63
1778582323 63
```
</details>

---

