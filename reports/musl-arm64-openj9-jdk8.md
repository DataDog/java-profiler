---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-18 10:39:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 34-44 cores)</summary>

```
1789741905 44
1789741910 44
1789741915 44
1789741920 44
1789741925 39
1789741930 39
1789741935 34
1789741940 34
1789741946 34
1789741951 34
1789741956 34
1789741961 34
1789741966 34
1789741971 34
1789741976 34
1789741981 44
1789741986 44
1789741991 44
1789741996 44
1789742001 44
```
</details>

---

