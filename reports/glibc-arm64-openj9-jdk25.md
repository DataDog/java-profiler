---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 08:22:45 EST

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 13 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795007977 64
1795007982 64
1795007987 64
1795007992 64
1795007997 64
1795008002 64
1795008007 64
1795008012 64
1795008017 64
1795008022 64
1795008027 64
1795008032 64
1795008037 64
1795008042 64
1795008047 64
1795008052 64
1795008057 64
1795008062 64
1795008067 64
1795008072 64
```
</details>

---

