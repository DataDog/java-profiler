---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 05:59:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 263 |
| Sample Rate | 4.38/sec |
| Health Score | 274% |
| Threads | 10 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1793876054 51
1793876059 51
1793876064 51
1793876069 51
1793876074 51
1793876079 51
1793876084 51
1793876089 51
1793876094 51
1793876099 51
1793876104 51
1793876109 51
1793876114 51
1793876119 51
1793876124 49
1793876129 49
1793876134 49
1793876139 49
1793876144 49
1793876149 49
```
</details>

---

