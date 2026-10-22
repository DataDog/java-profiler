---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 17:27:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792704233 30
1792704238 30
1792704244 30
1792704249 30
1792704254 32
1792704259 32
1792704264 32
1792704269 32
1792704274 32
1792704279 32
1792704284 32
1792704289 32
1792704294 32
1792704299 32
1792704304 32
1792704309 32
1792704314 32
1792704319 32
1792704324 32
1792704329 32
```
</details>

---

