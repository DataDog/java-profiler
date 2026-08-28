---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-28 12:57:54 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 173 |
| Sample Rate | 2.88/sec |
| Health Score | 180% |
| Threads | 11 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 10 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (3 unique values: 18-22 cores)</summary>

```
1787935969 18
1787935974 18
1787935979 18
1787935984 18
1787935989 18
1787935994 18
1787935999 18
1787936004 18
1787936009 19
1787936014 19
1787936019 19
1787936024 19
1787936029 22
1787936034 22
1787936039 22
1787936044 22
1787936049 22
1787936054 22
1787936059 22
1787936064 22
```
</details>

---

