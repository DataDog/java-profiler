---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 13:03:13 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 15 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1794851952 35
1794851957 35
1794851962 35
1794851967 35
1794851972 40
1794851977 40
1794851982 40
1794851987 40
1794851992 40
1794851997 40
1794852002 40
1794852007 40
1794852012 40
1794852017 40
1794852022 40
1794852027 40
1794852032 40
1794852037 40
1794852042 40
1794852047 40
```
</details>

---

