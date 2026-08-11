---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 11:48:04 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 12-19 cores)</summary>

```
1786462950 13
1786462955 13
1786462960 13
1786462965 14
1786462970 14
1786462975 12
1786462980 12
1786462985 14
1786462990 14
1786462995 14
1786463000 14
1786463005 14
1786463010 14
1786463015 14
1786463020 14
1786463025 14
1786463030 14
1786463035 14
1786463040 14
1786463045 14
```
</details>

---

