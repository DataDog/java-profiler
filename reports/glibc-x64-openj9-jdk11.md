---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-13 07:08:41 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 812 |
| Sample Rate | 13.53/sec |
| Health Score | 846% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (4 unique values: 78-85 cores)</summary>

```
1773399853 80
1773399858 80
1773399863 85
1773399868 85
1773399873 85
1773399878 85
1773399883 85
1773399888 85
1773399893 85
1773399898 85
1773399903 85
1773399908 85
1773399913 85
1773399918 85
1773399923 85
1773399928 85
1773399933 85
1773399938 82
1773399943 82
1773399948 80
```
</details>

---

