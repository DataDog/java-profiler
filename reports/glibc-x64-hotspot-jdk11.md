---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:47:15 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 8 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 35-37 cores)</summary>

```
1795113805 36
1795113810 36
1795113815 36
1795113820 36
1795113825 36
1795113830 37
1795113835 37
1795113840 37
1795113845 37
1795113850 37
1795113855 37
1795113860 37
1795113865 37
1795113870 37
1795113875 37
1795113880 37
1795113885 37
1795113890 37
1795113895 37
1795113900 35
```
</details>

---

