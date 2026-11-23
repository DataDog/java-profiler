---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 06:55:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 185 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 14 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795434609 44
1795434614 44
1795434619 44
1795434624 44
1795434629 44
1795434634 44
1795434639 49
1795434644 49
1795434649 49
1795434654 49
1795434660 49
1795434665 49
1795434670 44
1795434675 44
1795434680 44
1795434685 44
1795434690 44
1795434695 44
1795434700 44
1795434705 44
```
</details>

---

