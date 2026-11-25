---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:28:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795641871 33
1795641876 33
1795641881 33
1795641886 33
1795641891 33
1795641896 33
1795641901 33
1795641906 33
1795641911 33
1795641916 33
1795641921 33
1795641926 33
1795641931 33
1795641936 33
1795641941 33
1795641946 33
1795641951 33
1795641956 33
1795641961 33
1795641966 33
```
</details>

---

