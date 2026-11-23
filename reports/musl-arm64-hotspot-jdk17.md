---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 11:46:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 374 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 12 |
| Allocations | 133 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795451832 48
1795451837 48
1795451842 48
1795451847 48
1795451852 48
1795451857 48
1795451862 48
1795451867 48
1795451872 48
1795451877 48
1795451882 48
1795451887 64
1795451892 64
1795451897 64
1795451902 64
1795451907 64
1795451912 64
1795451917 48
1795451922 48
1795451927 48
```
</details>

---

