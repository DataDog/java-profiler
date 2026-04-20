---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 04:41:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 140 |
| Sample Rate | 2.33/sec |
| Health Score | 146% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1056 |
| Sample Rate | 17.60/sec |
| Health Score | 1100% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776674170 64
1776674175 64
1776674180 64
1776674185 64
1776674190 64
1776674195 64
1776674200 64
1776674205 64
1776674210 64
1776674215 64
1776674220 64
1776674225 64
1776674230 64
1776674235 64
1776674240 64
1776674245 64
1776674250 64
1776674255 64
1776674260 64
1776674265 64
```
</details>

---

