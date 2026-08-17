---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-17 09:54:52 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (5 unique values: 88-96 cores)</summary>

```
1786974684 88
1786974689 90
1786974694 90
1786974699 90
1786974704 94
1786974709 94
1786974714 92
1786974719 92
1786974724 92
1786974729 92
1786974734 92
1786974739 92
1786974744 94
1786974749 94
1786974754 94
1786974759 96
1786974764 96
1786974769 96
1786974774 96
1786974779 96
```
</details>

---

