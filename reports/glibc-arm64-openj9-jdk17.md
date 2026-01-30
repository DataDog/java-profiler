---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-01-30 05:41:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769769372 24
1769769377 24
1769769382 24
1769769387 24
1769769392 24
1769769397 24
1769769402 24
1769769407 24
1769769412 24
1769769417 24
1769769422 24
1769769427 24
1769769432 24
1769769437 24
1769769442 24
1769769447 24
1769769452 24
1769769457 24
1769769462 24
1769769467 24
```
</details>

---

