---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-28 07:43:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 334 |
| Sample Rate | 5.57/sec |
| Health Score | 348% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 54-60 cores)</summary>

```
1793187387 60
1793187392 60
1793187397 60
1793187402 60
1793187407 60
1793187412 60
1793187417 60
1793187422 60
1793187427 60
1793187432 60
1793187437 60
1793187442 57
1793187447 57
1793187452 57
1793187457 57
1793187462 57
1793187467 57
1793187472 57
1793187477 57
1793187482 57
```
</details>

---

