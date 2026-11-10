---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 14:09:19 EST

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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 44 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 11 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794337479 48
1794337484 48
1794337489 48
1794337494 48
1794337499 48
1794337504 48
1794337509 48
1794337514 48
1794337519 48
1794337524 48
1794337529 48
1794337534 48
1794337539 48
1794337544 48
1794337549 48
1794337554 48
1794337559 48
1794337564 48
1794337569 48
1794337574 48
```
</details>

---

