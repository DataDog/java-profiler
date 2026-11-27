---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 10:38:59 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1795793707 40
1795793712 40
1795793717 40
1795793722 40
1795793727 40
1795793732 40
1795793737 40
1795793742 40
1795793747 40
1795793752 40
1795793757 40
1795793762 40
1795793767 40
1795793772 40
1795793777 40
1795793782 40
1795793787 40
1795793792 40
1795793797 40
1795793802 40
```
</details>

---

