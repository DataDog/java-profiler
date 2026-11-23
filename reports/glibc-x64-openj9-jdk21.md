---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 05:59:58 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 44-53 cores)</summary>

```
1795431323 44
1795431328 44
1795431333 44
1795431338 44
1795431343 44
1795431348 44
1795431353 44
1795431358 44
1795431363 44
1795431368 44
1795431373 44
1795431378 44
1795431383 52
1795431388 52
1795431393 52
1795431398 52
1795431403 52
1795431408 53
1795431413 53
1795431418 53
```
</details>

---

