---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 10:31:18 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790346372 38
1790346377 38
1790346382 38
1790346387 38
1790346392 38
1790346397 38
1790346402 43
1790346407 43
1790346412 43
1790346417 43
1790346422 43
1790346427 43
1790346432 43
1790346437 48
1790346442 48
1790346447 48
1790346452 48
1790346457 48
1790346462 48
1790346467 48
```
</details>

---

