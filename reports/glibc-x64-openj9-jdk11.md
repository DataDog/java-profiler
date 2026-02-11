---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-11 11:59:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (6 unique values: 20-34 cores)</summary>

```
1770828853 26
1770828858 20
1770828863 20
1770828868 31
1770828873 31
1770828878 31
1770828883 31
1770828888 31
1770828893 31
1770828898 31
1770828903 31
1770828908 31
1770828913 31
1770828918 31
1770828924 34
1770828929 34
1770828934 29
1770828939 29
1770828944 29
1770828949 29
```
</details>

---

