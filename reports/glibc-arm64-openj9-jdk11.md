---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-28 12:57:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 13 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1787935987 48
1787935992 48
1787935997 48
1787936002 47
1787936007 47
1787936012 47
1787936017 47
1787936022 47
1787936027 47
1787936032 47
1787936037 47
1787936042 47
1787936047 47
1787936052 47
1787936057 47
1787936062 47
1787936067 47
1787936072 47
1787936077 47
1787936082 47
```
</details>

---

