---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-13 05:44:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 10 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 51-62 cores)</summary>

```
1773394719 51
1773394724 51
1773394729 51
1773394734 51
1773394739 60
1773394744 60
1773394749 60
1773394754 60
1773394759 60
1773394764 60
1773394769 60
1773394774 60
1773394779 60
1773394784 62
1773394789 62
1773394794 62
1773394799 62
1773394804 62
1773394809 62
1773394814 62
```
</details>

---

