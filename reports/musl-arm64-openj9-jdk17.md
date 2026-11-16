---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 12:34:15 EST

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 9 |
| Allocations | 94 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (5 unique values: 23-31 cores)</summary>

```
1794850169 23
1794850174 28
1794850179 28
1794850184 28
1794850189 28
1794850194 28
1794850199 28
1794850204 31
1794850209 31
1794850214 31
1794850219 31
1794850224 31
1794850229 31
1794850234 31
1794850239 31
1794850244 26
1794850249 26
1794850254 26
1794850259 26
1794850264 26
```
</details>

---

