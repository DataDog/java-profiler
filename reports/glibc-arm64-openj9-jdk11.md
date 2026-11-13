---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:25:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 341 |
| Sample Rate | 5.68/sec |
| Health Score | 355% |
| Threads | 15 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1794583293 64
1794583298 64
1794583303 64
1794583308 64
1794583313 64
1794583318 64
1794583323 64
1794583328 64
1794583333 64
1794583338 64
1794583343 64
1794583348 64
1794583353 64
1794583358 64
1794583363 64
1794583368 64
1794583373 64
1794583378 64
1794583383 64
1794583388 64
```
</details>

---

