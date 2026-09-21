---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 05:49:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 52-96 cores)</summary>

```
1789983829 52
1789983834 52
1789983839 78
1789983844 78
1789983849 78
1789983854 78
1789983859 78
1789983864 78
1789983869 96
1789983874 96
1789983879 96
1789983884 96
1789983889 96
1789983894 96
1789983899 96
1789983904 96
1789983909 96
1789983914 96
1789983919 96
1789983924 96
```
</details>

---

