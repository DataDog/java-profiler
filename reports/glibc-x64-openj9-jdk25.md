---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 11:26:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1792164008 15
1792164013 15
1792164018 15
1792164023 15
1792164028 15
1792164033 15
1792164038 15
1792164043 15
1792164048 15
1792164053 15
1792164058 15
1792164063 15
1792164068 15
1792164073 15
1792164078 15
1792164083 15
1792164088 15
1792164093 15
1792164098 17
1792164103 17
```
</details>

---

