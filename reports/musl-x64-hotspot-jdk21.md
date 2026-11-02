---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 07:22:57 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793621960 46
1793621965 46
1793621970 46
1793621975 48
1793621980 48
1793621986 48
1793621991 48
1793621996 48
1793622001 48
1793622006 48
1793622011 48
1793622016 48
1793622021 48
1793622026 48
1793622031 48
1793622036 48
1793622041 48
1793622046 48
1793622051 48
1793622056 48
```
</details>

---

