---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 10:39:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 792 |
| Sample Rate | 13.20/sec |
| Health Score | 825% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 48-81 cores)</summary>

```
1789741892 48
1789741897 48
1789741902 48
1789741907 48
1789741912 48
1789741917 81
1789741922 81
1789741928 81
1789741933 81
1789741938 81
1789741943 81
1789741948 73
1789741953 73
1789741958 73
1789741963 73
1789741968 73
1789741973 73
1789741978 73
1789741983 73
1789741988 73
```
</details>

---

