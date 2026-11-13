---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 06:03:38 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 385 |
| Sample Rate | 6.42/sec |
| Health Score | 401% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 76-78 cores)</summary>

```
1794567573 78
1794567578 76
1794567583 76
1794567588 76
1794567593 76
1794567598 76
1794567603 76
1794567608 76
1794567613 76
1794567618 76
1794567623 78
1794567628 78
1794567633 78
1794567638 78
1794567643 78
1794567648 78
1794567653 78
1794567658 78
1794567663 78
1794567668 78
```
</details>

---

