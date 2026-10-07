---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-07 12:48:06 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1791391479 48
1791391484 48
1791391489 48
1791391494 53
1791391499 53
1791391504 53
1791391509 53
1791391514 53
1791391519 53
1791391524 53
1791391529 53
1791391534 53
1791391539 53
1791391544 53
1791391549 53
1791391554 53
1791391559 53
1791391564 53
1791391569 53
1791391574 48
```
</details>

---

