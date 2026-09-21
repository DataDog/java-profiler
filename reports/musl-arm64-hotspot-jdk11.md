---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 05:49:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 10 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 23-27 cores)</summary>

```
1789983804 23
1789983809 23
1789983814 23
1789983819 23
1789983824 23
1789983829 23
1789983834 23
1789983839 23
1789983844 23
1789983849 23
1789983854 23
1789983859 23
1789983864 23
1789983869 23
1789983874 23
1789983879 23
1789983884 23
1789983889 23
1789983894 23
1789983899 23
```
</details>

---

