---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-28 00:04:19 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 11 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 33-40 cores)</summary>

```
1795842034 40
1795842039 40
1795842045 40
1795842050 40
1795842055 40
1795842060 40
1795842065 40
1795842070 40
1795842075 40
1795842080 40
1795842085 40
1795842090 40
1795842095 40
1795842100 40
1795842105 40
1795842110 40
1795842115 40
1795842120 40
1795842125 40
1795842130 40
```
</details>

---

