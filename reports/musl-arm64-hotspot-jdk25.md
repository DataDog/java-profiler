---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 10:50:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 290 |
| Sample Rate | 4.83/sec |
| Health Score | 302% |
| Threads | 14 |
| Allocations | 174 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1795189588 50
1795189593 50
1795189598 50
1795189603 50
1795189608 50
1795189613 50
1795189618 50
1795189623 50
1795189628 50
1795189633 50
1795189638 50
1795189643 50
1795189648 50
1795189653 50
1795189658 50
1795189663 64
1795189668 64
1795189673 64
1795189678 64
1795189683 64
```
</details>

---

