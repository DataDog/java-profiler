---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 13:47:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 7 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 41-50 cores)</summary>

```
1795113786 41
1795113791 41
1795113796 41
1795113801 41
1795113806 41
1795113811 41
1795113816 43
1795113821 43
1795113826 43
1795113831 43
1795113836 43
1795113841 43
1795113846 43
1795113851 43
1795113856 43
1795113861 43
1795113866 43
1795113871 43
1795113876 48
1795113881 48
```
</details>

---

