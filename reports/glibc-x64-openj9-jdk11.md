---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 12:28:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 825 |
| Sample Rate | 13.75/sec |
| Health Score | 859% |
| Threads | 9 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (3 unique values: 58-79 cores)</summary>

```
1792772674 58
1792772679 58
1792772684 58
1792772689 58
1792772694 58
1792772699 58
1792772704 58
1792772709 58
1792772714 58
1792772719 58
1792772724 58
1792772729 79
1792772734 79
1792772739 79
1792772744 79
1792772749 79
1792772754 79
1792772759 79
1792772764 79
1792772769 79
```
</details>

---

