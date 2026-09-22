---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 11:34:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 24-60 cores)</summary>

```
1790090855 24
1790090860 24
1790090865 24
1790090870 24
1790090875 24
1790090880 24
1790090885 24
1790090890 24
1790090895 24
1790090900 24
1790090905 24
1790090910 24
1790090915 24
1790090920 24
1790090925 24
1790090930 24
1790090935 60
1790090940 60
1790090945 50
1790090950 50
```
</details>

---

