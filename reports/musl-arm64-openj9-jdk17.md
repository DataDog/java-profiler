---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-30 21:23:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 9 |
| Allocations | 151 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788139045 43
1788139050 43
1788139055 43
1788139060 43
1788139065 48
1788139070 48
1788139075 48
1788139080 48
1788139085 48
1788139090 48
1788139095 48
1788139100 48
1788139105 48
1788139110 48
1788139115 48
1788139120 48
1788139125 48
1788139130 48
1788139135 43
1788139140 43
```
</details>

---

