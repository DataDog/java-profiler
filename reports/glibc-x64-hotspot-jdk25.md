---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 19:07:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 48-62 cores)</summary>

```
1793836976 62
1793836981 62
1793836986 62
1793836991 50
1793836996 50
1793837001 50
1793837006 50
1793837011 50
1793837016 50
1793837021 50
1793837026 50
1793837031 50
1793837036 50
1793837041 50
1793837046 50
1793837051 50
1793837056 50
1793837061 50
1793837066 50
1793837071 50
```
</details>

---

