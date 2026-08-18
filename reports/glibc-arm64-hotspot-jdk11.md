---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-18 11:02:20 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 11 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787065100 64
1787065105 64
1787065110 64
1787065115 64
1787065120 64
1787065125 64
1787065130 64
1787065135 64
1787065140 64
1787065145 64
1787065150 64
1787065155 64
1787065160 64
1787065165 64
1787065170 64
1787065175 64
1787065180 64
1787065185 64
1787065190 64
1787065195 64
```
</details>

---

