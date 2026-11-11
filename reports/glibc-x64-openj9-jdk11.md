---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 06:07:51 EST

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 91-93 cores)</summary>

```
1794394974 93
1794394979 93
1794394984 91
1794394989 91
1794394994 91
1794394999 91
1794395004 91
1794395009 91
1794395014 91
1794395019 91
1794395024 91
1794395029 91
1794395034 91
1794395039 91
1794395044 91
1794395049 91
1794395054 91
1794395059 91
1794395064 91
1794395069 91
```
</details>

---

