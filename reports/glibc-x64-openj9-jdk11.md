---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:49:39 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 8 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 5 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 88-91 cores)</summary>

```
1795707867 88
1795707872 88
1795707877 88
1795707882 91
1795707887 91
1795707892 91
1795707897 91
1795707902 91
1795707907 91
1795707912 91
1795707917 91
1795707922 91
1795707927 91
1795707932 91
1795707937 91
1795707942 91
1795707947 91
1795707952 91
1795707957 91
1795707962 91
```
</details>

---

