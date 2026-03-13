---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-13 07:08:42 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 12 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 13 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (4 unique values: 85-96 cores)</summary>

```
1773399878 85
1773399883 89
1773399888 89
1773399893 89
1773399898 89
1773399903 89
1773399908 91
1773399913 91
1773399918 91
1773399923 91
1773399928 91
1773399933 91
1773399938 91
1773399943 96
1773399948 96
1773399953 96
1773399958 96
1773399963 96
1773399968 96
1773399973 96
```
</details>

---

