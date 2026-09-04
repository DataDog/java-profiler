---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-04 14:55:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 12 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1788547881 64
1788547886 59
1788547891 59
1788547896 59
1788547901 59
1788547906 59
1788547911 59
1788547916 59
1788547921 59
1788547926 59
1788547931 59
1788547936 59
1788547941 59
1788547946 59
1788547951 64
1788547956 64
1788547961 64
1788547966 64
1788547971 64
1788547976 64
```
</details>

---

