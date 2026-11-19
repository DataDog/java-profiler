---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:35:45 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (5 unique values: 36-48 cores)</summary>

```
1795112852 48
1795112857 48
1795112862 48
1795112867 48
1795112873 38
1795112878 38
1795112883 38
1795112888 38
1795112893 36
1795112898 36
1795112903 36
1795112908 36
1795112913 36
1795112918 36
1795112923 36
1795112928 36
1795112933 36
1795112938 36
1795112943 36
1795112948 38
```
</details>

---

