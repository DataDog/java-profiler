---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 03:32:41 EST

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 10 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 15-22 cores)</summary>

```
1793780908 15
1793780913 17
1793780918 17
1793780923 17
1793780928 17
1793780933 17
1793780938 17
1793780943 22
1793780948 22
1793780953 22
1793780959 22
1793780964 22
1793780969 22
1793780974 22
1793780979 22
1793780984 22
1793780989 22
1793780994 22
1793780999 22
1793781004 22
```
</details>

---

