---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 11:46:27 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 163 |
| Sample Rate | 2.72/sec |
| Health Score | 170% |
| Threads | 13 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (4 unique values: 46-64 cores)</summary>

```
1786376402 53
1786376407 53
1786376412 64
1786376417 64
1786376422 64
1786376427 64
1786376432 64
1786376437 51
1786376442 51
1786376447 51
1786376452 51
1786376457 46
1786376462 46
1786376467 46
1786376472 46
1786376477 46
1786376482 46
1786376487 46
1786376492 46
1786376497 46
```
</details>

---

