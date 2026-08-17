---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-17 05:46:53 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1786959762 96
1786959767 96
1786959772 96
1786959777 96
1786959782 96
1786959787 96
1786959792 96
1786959797 96
1786959802 94
1786959807 94
1786959812 94
1786959817 94
1786959822 94
1786959827 94
1786959832 94
1786959837 94
1786959842 96
1786959847 96
1786959852 96
1786959857 96
```
</details>

---

