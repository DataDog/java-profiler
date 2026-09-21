---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 05:49:06 EDT

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
| CPU Cores (start) | 7 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 7-32 cores)</summary>

```
1789983837 7
1789983842 7
1789983847 7
1789983852 7
1789983857 7
1789983862 32
1789983867 32
1789983872 32
1789983877 7
1789983882 7
1789983887 7
1789983892 7
1789983897 7
1789983902 7
1789983907 7
1789983912 7
1789983917 7
1789983922 7
1789983927 7
1789983932 7
```
</details>

---

