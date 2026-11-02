---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 06:22:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 221 |
| Sample Rate | 3.68/sec |
| Health Score | 230% |
| Threads | 14 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1793618331 43
1793618336 43
1793618341 43
1793618346 43
1793618351 43
1793618356 43
1793618361 43
1793618366 43
1793618371 43
1793618376 43
1793618381 43
1793618386 43
1793618391 48
1793618396 48
1793618401 48
1793618406 48
1793618411 48
1793618416 48
1793618421 48
1793618426 48
```
</details>

---

