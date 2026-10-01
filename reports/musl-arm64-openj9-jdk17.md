---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-01 07:50:44 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 352 |
| Sample Rate | 5.87/sec |
| Health Score | 367% |
| Threads | 11 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1790855195 53
1790855200 53
1790855206 53
1790855211 53
1790855216 53
1790855221 53
1790855226 64
1790855231 64
1790855236 64
1790855241 64
1790855246 64
1790855251 64
1790855256 64
1790855261 64
1790855266 64
1790855271 64
1790855276 64
1790855281 64
1790855286 64
1790855291 64
```
</details>

---

