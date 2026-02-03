---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 08:20:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 789 |
| Sample Rate | 13.15/sec |
| Health Score | 822% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 23-27 cores)</summary>

```
1770124617 27
1770124622 27
1770124627 27
1770124632 27
1770124637 27
1770124642 27
1770124647 27
1770124652 27
1770124657 25
1770124662 25
1770124667 25
1770124672 25
1770124677 25
1770124682 25
1770124687 25
1770124692 25
1770124697 25
1770124702 25
1770124707 23
1770124712 23
```
</details>

---

