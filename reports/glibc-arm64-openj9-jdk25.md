---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 18:03:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1794524383 44
1794524388 44
1794524393 44
1794524398 44
1794524403 44
1794524408 44
1794524413 48
1794524418 48
1794524423 48
1794524428 48
1794524433 48
1794524438 48
1794524443 48
1794524448 48
1794524453 48
1794524458 48
1794524463 48
1794524468 48
1794524473 48
1794524478 48
```
</details>

---

