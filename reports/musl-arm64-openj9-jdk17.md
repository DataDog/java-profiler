---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 09:56:25 EST

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (3 unique values: 13-15 cores)</summary>

```
1795186317 13
1795186322 13
1795186327 13
1795186332 13
1795186337 13
1795186342 13
1795186347 13
1795186352 13
1795186357 15
1795186362 15
1795186367 15
1795186372 15
1795186377 14
1795186382 14
1795186387 14
1795186392 14
1795186397 14
1795186402 14
1795186407 14
1795186412 14
```
</details>

---

