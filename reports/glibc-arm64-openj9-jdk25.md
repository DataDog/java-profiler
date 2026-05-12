---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-11 20:52:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 316 |
| Sample Rate | 5.27/sec |
| Health Score | 329% |
| Threads | 11 |
| Allocations | 161 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1778546968 64
1778546973 64
1778546978 64
1778546983 64
1778546988 64
1778546993 64
1778546998 64
1778547003 64
1778547008 64
1778547013 64
1778547018 64
1778547023 64
1778547028 64
1778547033 64
1778547038 64
1778547043 64
1778547048 64
1778547053 64
1778547058 64
1778547063 64
```
</details>

---

