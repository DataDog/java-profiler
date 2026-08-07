---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 16:14:05 EDT

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
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 49-51 cores)</summary>

```
1786133345 51
1786133350 51
1786133355 51
1786133360 51
1786133365 51
1786133370 51
1786133375 51
1786133380 51
1786133385 51
1786133390 51
1786133395 51
1786133400 51
1786133405 51
1786133410 51
1786133415 51
1786133420 51
1786133425 51
1786133430 50
1786133435 50
1786133440 49
```
</details>

---

