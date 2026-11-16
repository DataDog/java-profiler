---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ❌ FAIL

**Date:** 2026-11-16 12:07:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (5 unique values: 71-88 cores)</summary>

```
1794848434 79
1794848439 79
1794848444 79
1794848449 79
1794848454 79
1794848459 79
1794848464 79
1794848469 79
1794848474 79
1794848479 79
1794848484 79
1794848489 79
1794848494 81
1794848499 81
1794848504 81
1794848509 81
1794848514 85
1794848519 85
1794848524 85
1794848529 85
```
</details>

---

