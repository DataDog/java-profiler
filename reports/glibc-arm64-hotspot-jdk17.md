---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 10:17:16 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1793196690 38
1793196695 38
1793196700 38
1793196705 38
1793196710 38
1793196715 38
1793196720 38
1793196725 43
1793196730 43
1793196735 43
1793196740 43
1793196745 43
1793196750 43
1793196755 48
1793196760 48
1793196765 48
1793196770 48
1793196775 48
1793196780 48
1793196785 48
```
</details>

---

