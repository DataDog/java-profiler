---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-04 22:42:05 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 14 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1788575850 29
1788575855 29
1788575860 29
1788575865 29
1788575870 29
1788575875 29
1788575880 29
1788575885 29
1788575890 29
1788575895 29
1788575900 29
1788575905 29
1788575910 29
1788575915 29
1788575920 29
1788575925 29
1788575930 29
1788575935 34
1788575940 34
1788575945 34
```
</details>

---

