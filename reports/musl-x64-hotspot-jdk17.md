---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-13 05:44:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 8 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 10 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (3 unique values: 22-27 cores)</summary>

```
1773394718 27
1773394723 27
1773394729 27
1773394734 27
1773394739 27
1773394744 27
1773394749 24
1773394754 24
1773394759 24
1773394764 24
1773394769 24
1773394774 24
1773394779 24
1773394784 24
1773394789 24
1773394794 24
1773394799 24
1773394804 24
1773394809 24
1773394814 24
```
</details>

---

