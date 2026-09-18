---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 10:39:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 49-73 cores)</summary>

```
1789741905 53
1789741910 53
1789741915 53
1789741920 53
1789741925 53
1789741930 49
1789741935 49
1789741940 49
1789741945 49
1789741950 49
1789741955 49
1789741960 49
1789741965 49
1789741970 49
1789741975 73
1789741980 73
1789741985 73
1789741990 73
1789741995 73
1789742000 73
```
</details>

---

