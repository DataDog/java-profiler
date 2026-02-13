---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-13 07:46:24 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 5 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 9 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1770986583 24
1770986588 24
1770986593 24
1770986598 24
1770986603 24
1770986608 24
1770986613 24
1770986618 24
1770986623 24
1770986628 24
1770986633 24
1770986638 24
1770986643 24
1770986648 24
1770986653 24
1770986658 24
1770986663 24
1770986668 24
1770986673 24
1770986678 24
```
</details>

---

