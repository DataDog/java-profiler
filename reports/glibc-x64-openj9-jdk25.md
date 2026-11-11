---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 16:06:30 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (5 unique values: 77-94 cores)</summary>

```
1794430853 77
1794430858 77
1794430863 77
1794430868 91
1794430873 91
1794430878 89
1794430883 89
1794430888 92
1794430893 92
1794430898 92
1794430903 92
1794430908 92
1794430913 92
1794430918 92
1794430923 92
1794430928 92
1794430933 92
1794430938 92
1794430943 92
1794430948 92
```
</details>

---

