---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 09:09:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 7 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 12 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1790168623 41
1790168628 43
1790168633 43
1790168638 43
1790168643 43
1790168648 48
1790168653 48
1790168658 48
1790168663 43
1790168668 43
1790168673 38
1790168678 38
1790168683 38
1790168688 38
1790168693 38
1790168698 38
1790168703 38
1790168708 38
1790168713 38
1790168718 38
```
</details>

---

