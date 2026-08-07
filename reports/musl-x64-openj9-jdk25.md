---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-07 05:50:47 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (4 unique values: 70-96 cores)</summary>

```
1786095955 70
1786095960 94
1786095965 94
1786095970 94
1786095975 94
1786095980 94
1786095985 94
1786095990 94
1786095995 94
1786096000 96
1786096005 96
1786096010 96
1786096015 92
1786096020 92
1786096025 92
1786096030 92
1786096035 92
1786096040 92
1786096045 92
1786096050 92
```
</details>

---

