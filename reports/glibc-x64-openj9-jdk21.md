---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 06:03:38 EST

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 9-12 cores)</summary>

```
1794567598 10
1794567603 10
1794567608 10
1794567613 10
1794567618 10
1794567623 10
1794567628 10
1794567633 10
1794567638 10
1794567643 10
1794567648 10
1794567653 12
1794567658 12
1794567663 9
1794567668 9
1794567673 9
1794567678 9
1794567683 9
1794567688 9
1794567693 9
```
</details>

---

