---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 05:56:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1793616696 64
1793616701 64
1793616706 64
1793616711 64
1793616716 64
1793616721 64
1793616726 64
1793616731 64
1793616736 64
1793616741 64
1793616746 64
1793616751 64
1793616756 62
1793616761 62
1793616766 62
1793616771 62
1793616776 62
1793616781 62
1793616786 62
1793616791 62
```
</details>

---

