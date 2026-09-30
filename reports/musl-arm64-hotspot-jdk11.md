---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 11:36:50 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 12 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1790782325 44
1790782330 44
1790782335 44
1790782340 44
1790782345 44
1790782350 64
1790782355 64
1790782360 64
1790782365 44
1790782370 44
1790782375 44
1790782380 44
1790782385 44
1790782390 44
1790782395 44
1790782400 44
1790782405 44
1790782410 44
1790782415 44
1790782420 44
```
</details>

---

