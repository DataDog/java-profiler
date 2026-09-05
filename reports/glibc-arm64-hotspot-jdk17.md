---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-04 22:42:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1788575860 14
1788575865 14
1788575870 14
1788575875 34
1788575880 34
1788575885 34
1788575890 34
1788575895 34
1788575900 34
1788575905 34
1788575910 34
1788575915 34
1788575920 34
1788575925 34
1788575930 34
1788575935 34
1788575940 34
1788575945 34
1788575950 34
1788575955 34
```
</details>

---

