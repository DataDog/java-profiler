---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 14:01:19 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 239 |
| Sample Rate | 3.98/sec |
| Health Score | 249% |
| Threads | 15 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795201010 44
1795201015 44
1795201020 44
1795201025 44
1795201030 44
1795201035 44
1795201040 44
1795201045 49
1795201050 49
1795201055 49
1795201060 49
1795201065 49
1795201070 49
1795201075 49
1795201080 49
1795201085 49
1795201090 49
1795201095 49
1795201100 49
1795201105 49
```
</details>

---

