---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-04 22:42:06 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1788575850 59
1788575855 59
1788575860 59
1788575865 59
1788575870 59
1788575875 59
1788575880 61
1788575885 61
1788575890 61
1788575895 61
1788575900 61
1788575905 61
1788575910 61
1788575915 61
1788575920 61
1788575925 61
1788575930 61
1788575935 61
1788575940 61
1788575945 61
```
</details>

---

