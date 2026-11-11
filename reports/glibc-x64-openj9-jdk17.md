---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 16:06:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (4 unique values: 85-91 cores)</summary>

```
1794430853 85
1794430858 85
1794430863 85
1794430868 85
1794430873 87
1794430878 87
1794430883 89
1794430888 89
1794430893 89
1794430898 89
1794430903 89
1794430908 89
1794430913 89
1794430918 89
1794430923 89
1794430928 89
1794430933 89
1794430938 91
1794430943 91
1794430948 91
```
</details>

---

