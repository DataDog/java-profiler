---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-02 12:03:20 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 75-86 cores)</summary>

```
1790956770 75
1790956775 75
1790956780 75
1790956785 75
1790956790 77
1790956795 77
1790956800 77
1790956805 77
1790956810 77
1790956815 77
1790956820 77
1790956825 77
1790956830 86
1790956835 86
1790956840 86
1790956845 86
1790956850 86
1790956855 86
1790956860 86
1790956865 86
```
</details>

---

