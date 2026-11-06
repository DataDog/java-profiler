---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-06 15:13:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 374 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 212 |
| Sample Rate | 3.53/sec |
| Health Score | 221% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 42-64 cores)</summary>

```
1793995724 43
1793995729 43
1793995734 43
1793995739 43
1793995744 43
1793995749 43
1793995754 43
1793995759 64
1793995764 64
1793995769 44
1793995774 44
1793995779 44
1793995784 44
1793995789 44
1793995794 44
1793995799 44
1793995804 42
1793995809 42
1793995814 42
1793995819 42
```
</details>

---

