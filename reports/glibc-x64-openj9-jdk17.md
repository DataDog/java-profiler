---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 11:46:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 56-68 cores)</summary>

```
1786376387 68
1786376392 68
1786376397 68
1786376402 68
1786376407 68
1786376412 68
1786376417 56
1786376422 56
1786376427 56
1786376432 56
1786376437 56
1786376442 56
1786376447 56
1786376452 56
1786376457 56
1786376462 56
1786376467 56
1786376472 56
1786376477 56
1786376482 56
```
</details>

---

