---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 08:52:14 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1794836817 70
1794836822 70
1794836827 70
1794836832 70
1794836837 70
1794836842 70
1794836847 70
1794836852 70
1794836857 70
1794836862 70
1794836867 70
1794836872 72
1794836877 72
1794836882 72
1794836887 72
1794836892 72
1794836897 72
1794836902 72
1794836907 72
1794836912 72
```
</details>

---

