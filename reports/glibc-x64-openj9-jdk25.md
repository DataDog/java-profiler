---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 14:09:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (5 unique values: 79-86 cores)</summary>

```
1794337474 81
1794337479 79
1794337484 79
1794337489 79
1794337494 79
1794337499 79
1794337504 79
1794337509 79
1794337514 79
1794337519 79
1794337524 79
1794337529 86
1794337534 86
1794337539 86
1794337544 86
1794337550 86
1794337555 86
1794337560 86
1794337565 84
1794337570 84
```
</details>

---

