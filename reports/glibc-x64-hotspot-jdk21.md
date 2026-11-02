---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 05:56:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793616735 48
1793616740 48
1793616745 48
1793616750 48
1793616755 48
1793616760 48
1793616765 48
1793616770 48
1793616775 48
1793616780 48
1793616785 36
1793616790 36
1793616795 36
1793616800 36
1793616805 36
1793616810 36
1793616815 36
1793616820 36
1793616825 36
1793616830 36
```
</details>

---

