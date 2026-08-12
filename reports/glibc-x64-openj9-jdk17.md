---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-12 11:23:58 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (4 unique values: 41-73 cores)</summary>

```
1786547946 73
1786547951 73
1786547956 73
1786547961 73
1786547966 73
1786547971 73
1786547976 73
1786547981 73
1786547986 73
1786547991 73
1786547996 44
1786548001 44
1786548006 44
1786548011 44
1786548016 44
1786548021 44
1786548026 44
1786548031 44
1786548036 46
1786548041 46
```
</details>

---

