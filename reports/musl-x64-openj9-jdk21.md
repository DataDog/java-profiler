---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-30 19:50:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (5 unique values: 39-62 cores)</summary>

```
1777592807 57
1777592812 57
1777592817 57
1777592822 57
1777592827 57
1777592832 42
1777592837 42
1777592842 42
1777592847 42
1777592852 42
1777592857 42
1777592862 62
1777592867 62
1777592872 62
1777592877 62
1777592882 62
1777592887 39
1777592892 39
1777592897 58
1777592902 58
```
</details>

---

