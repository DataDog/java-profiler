---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-30 21:23:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 8 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 938 |
| Sample Rate | 15.63/sec |
| Health Score | 977% |
| Threads | 9 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1788139065 29
1788139070 29
1788139075 29
1788139080 29
1788139085 29
1788139090 29
1788139095 29
1788139100 29
1788139105 29
1788139110 29
1788139115 29
1788139120 29
1788139125 29
1788139130 29
1788139135 29
1788139140 29
1788139145 29
1788139151 29
1788139156 29
1788139161 34
```
</details>

---

