---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 13:10:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 37-64 cores)</summary>

```
1790096740 37
1790096745 37
1790096750 37
1790096755 37
1790096760 37
1790096765 37
1790096770 37
1790096775 37
1790096780 37
1790096785 37
1790096790 37
1790096795 42
1790096800 42
1790096805 42
1790096810 42
1790096815 42
1790096820 42
1790096825 42
1790096830 42
1790096835 42
```
</details>

---

