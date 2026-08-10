---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 06:26:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 7 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 943 |
| Sample Rate | 15.72/sec |
| Health Score | 982% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1786357307 25
1786357312 30
1786357317 30
1786357322 30
1786357327 30
1786357332 30
1786357337 30
1786357342 30
1786357347 30
1786357352 30
1786357357 30
1786357362 30
1786357367 30
1786357372 30
1786357377 30
1786357382 30
1786357387 30
1786357392 30
1786357397 30
1786357402 30
```
</details>

---

