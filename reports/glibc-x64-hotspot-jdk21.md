---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 09:53:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 64-70 cores)</summary>

```
1795618030 64
1795618035 64
1795618040 64
1795618045 64
1795618050 64
1795618055 64
1795618060 64
1795618065 66
1795618070 66
1795618075 66
1795618080 66
1795618085 66
1795618090 66
1795618095 66
1795618100 66
1795618105 66
1795618110 70
1795618115 70
1795618120 70
1795618125 70
```
</details>

---

