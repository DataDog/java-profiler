---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-26 10:49:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 75-84 cores)</summary>

```
1795707882 84
1795707887 84
1795707892 76
1795707897 76
1795707902 76
1795707907 76
1795707912 76
1795707917 76
1795707922 79
1795707927 79
1795707933 79
1795707938 79
1795707943 79
1795707948 79
1795707953 77
1795707958 77
1795707963 77
1795707968 77
1795707973 77
1795707978 75
```
</details>

---

