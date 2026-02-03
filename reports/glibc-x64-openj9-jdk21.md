---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 07:41:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 21-24 cores)</summary>

```
1770122089 24
1770122094 24
1770122099 24
1770122104 24
1770122109 24
1770122114 24
1770122119 24
1770122124 24
1770122129 24
1770122134 24
1770122139 24
1770122144 24
1770122149 24
1770122154 24
1770122159 24
1770122164 24
1770122169 21
1770122174 21
1770122179 21
1770122184 21
```
</details>

---

