---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 06:43:05 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790678261 43
1790678266 43
1790678271 43
1790678276 43
1790678281 43
1790678286 48
1790678291 48
1790678296 48
1790678301 43
1790678307 43
1790678312 43
1790678317 43
1790678322 43
1790678327 43
1790678332 43
1790678337 43
1790678342 46
1790678347 46
1790678352 46
1790678357 46
```
</details>

---

