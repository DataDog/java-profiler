---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-30 19:50:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 77-81 cores)</summary>

```
1777592827 77
1777592832 77
1777592837 77
1777592842 77
1777592847 77
1777592852 77
1777592857 77
1777592862 77
1777592867 77
1777592872 77
1777592877 77
1777592882 81
1777592887 81
1777592892 81
1777592897 81
1777592902 81
1777592907 81
1777592912 81
1777592917 81
1777592922 81
```
</details>

---

