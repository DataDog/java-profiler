---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-30 19:50:56 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1777592812 64
1777592817 64
1777592822 64
1777592827 64
1777592832 64
1777592837 64
1777592842 64
1777592847 64
1777592852 64
1777592857 64
1777592862 64
1777592867 64
1777592872 64
1777592877 64
1777592882 64
1777592887 64
1777592892 64
1777592897 62
1777592902 62
1777592907 60
```
</details>

---

