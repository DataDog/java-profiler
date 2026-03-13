---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-13 07:08:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 10 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 13 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (7 unique values: 29-53 cores)</summary>

```
1773399790 44
1773399795 39
1773399800 39
1773399805 29
1773399810 29
1773399815 34
1773399820 34
1773399825 34
1773399830 34
1773399835 46
1773399840 46
1773399845 46
1773399850 46
1773399855 46
1773399860 48
1773399865 48
1773399870 48
1773399875 48
1773399880 48
1773399885 48
```
</details>

---

