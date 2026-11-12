---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 07:47:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 14 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (3 unique values: 39-44 cores)</summary>

```
1794487387 43
1794487392 43
1794487397 43
1794487402 43
1794487407 43
1794487412 43
1794487417 43
1794487422 39
1794487427 39
1794487432 44
1794487437 44
1794487442 44
1794487447 44
1794487452 44
1794487457 44
1794487462 44
1794487467 44
1794487472 44
1794487477 44
1794487482 44
```
</details>

---

