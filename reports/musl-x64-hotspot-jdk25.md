---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 01:30:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 10 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (4 unique values: 67-92 cores)</summary>

```
1776662863 90
1776662868 90
1776662873 90
1776662878 90
1776662883 90
1776662888 90
1776662893 90
1776662898 90
1776662903 90
1776662908 90
1776662913 90
1776662918 90
1776662923 90
1776662928 92
1776662933 92
1776662938 92
1776662943 92
1776662948 92
1776662953 92
1776662958 92
```
</details>

---

