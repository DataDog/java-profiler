---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 12:07:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 780 |
| Sample Rate | 13.00/sec |
| Health Score | 812% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (4 unique values: 76-85 cores)</summary>

```
1794848429 76
1794848434 76
1794848439 79
1794848444 79
1794848449 83
1794848454 83
1794848459 83
1794848464 83
1794848469 83
1794848474 83
1794848479 83
1794848484 83
1794848489 83
1794848494 83
1794848499 83
1794848504 83
1794848509 83
1794848514 83
1794848519 85
1794848524 85
```
</details>

---

