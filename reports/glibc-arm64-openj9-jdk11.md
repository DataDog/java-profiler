---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 18:03:50 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (4 unique values: 36-48 cores)</summary>

```
1794524373 36
1794524378 36
1794524383 36
1794524388 36
1794524393 36
1794524398 36
1794524403 36
1794524408 36
1794524413 36
1794524418 36
1794524423 40
1794524428 40
1794524433 40
1794524438 44
1794524443 44
1794524448 44
1794524453 44
1794524458 44
1794524463 44
1794524468 44
```
</details>

---

