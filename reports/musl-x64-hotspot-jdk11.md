---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 13:18:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (7 unique values: 56-69 cores)</summary>

```
1794420785 65
1794420790 65
1794420795 65
1794420800 67
1794420805 67
1794420810 69
1794420815 69
1794420820 58
1794420825 58
1794420830 58
1794420835 56
1794420840 56
1794420845 60
1794420850 60
1794420855 60
1794420860 60
1794420865 60
1794420870 60
1794420875 60
1794420880 60
```
</details>

---

