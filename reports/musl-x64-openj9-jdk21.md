---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-25 10:31:19 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 880 |
| Sample Rate | 14.67/sec |
| Health Score | 917% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1790346372 32
1790346377 32
1790346382 32
1790346387 32
1790346392 32
1790346397 32
1790346402 32
1790346407 32
1790346412 32
1790346417 32
1790346422 32
1790346427 32
1790346432 32
1790346437 32
1790346442 32
1790346447 32
1790346452 32
1790346457 32
1790346462 32
1790346467 32
```
</details>

---

