---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-11 11:15:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 11-32 cores)</summary>

```
1791731370 11
1791731375 11
1791731380 11
1791731385 11
1791731390 11
1791731395 11
1791731400 11
1791731405 11
1791731410 11
1791731415 11
1791731420 11
1791731425 11
1791731430 11
1791731435 11
1791731440 11
1791731445 11
1791731450 11
1791731455 11
1791731460 32
1791731465 32
```
</details>

---

