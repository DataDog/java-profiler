---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 18:10:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 7 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795129642 50
1795129647 50
1795129652 50
1795129657 50
1795129662 50
1795129667 50
1795129672 50
1795129677 50
1795129682 50
1795129687 50
1795129692 50
1795129697 50
1795129702 50
1795129707 50
1795129712 50
1795129717 50
1795129722 50
1795129727 50
1795129732 50
1795129737 50
```
</details>

---

