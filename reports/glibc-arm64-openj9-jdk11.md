---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 09:46:46 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 10 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 941 |
| Sample Rate | 15.68/sec |
| Health Score | 980% |
| Threads | 9 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (2 unique values: 16-36 cores)</summary>

```
1793194988 36
1793194993 36
1793194998 36
1793195003 16
1793195008 16
1793195013 16
1793195018 16
1793195024 16
1793195029 16
1793195034 16
1793195039 16
1793195044 16
1793195049 16
1793195054 16
1793195059 16
1793195064 16
1793195069 16
1793195074 16
1793195079 16
1793195084 16
```
</details>

---

