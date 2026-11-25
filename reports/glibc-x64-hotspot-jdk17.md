---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 06:18:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 57-63 cores)</summary>

```
1795605035 61
1795605040 61
1795605045 61
1795605050 61
1795605055 61
1795605060 61
1795605065 61
1795605070 61
1795605075 61
1795605080 61
1795605085 61
1795605090 61
1795605095 63
1795605100 63
1795605105 63
1795605110 57
1795605115 57
1795605120 57
1795605125 57
1795605130 57
```
</details>

---

