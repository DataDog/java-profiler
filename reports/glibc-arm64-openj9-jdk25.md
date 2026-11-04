---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 17:22:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793830754 48
1793830759 48
1793830764 48
1793830769 48
1793830774 48
1793830779 48
1793830784 48
1793830789 48
1793830794 48
1793830799 48
1793830804 48
1793830809 48
1793830814 48
1793830819 48
1793830824 48
1793830829 48
1793830834 48
1793830839 48
1793830844 48
1793830849 48
```
</details>

---

