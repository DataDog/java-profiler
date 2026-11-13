---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:06:24 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 919 |
| Sample Rate | 15.32/sec |
| Health Score | 957% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (5 unique values: 75-81 cores)</summary>

```
1794592802 80
1794592807 80
1794592812 75
1794592817 75
1794592822 75
1794592827 75
1794592832 75
1794592837 77
1794592842 77
1794592847 77
1794592852 81
1794592857 81
1794592862 81
1794592867 81
1794592872 81
1794592877 81
1794592882 81
1794592887 81
1794592892 81
1794592897 79
```
</details>

---

