---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 14:13:17 EDT

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
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1793297293 43
1793297298 43
1793297303 43
1793297308 43
1793297313 43
1793297318 43
1793297323 43
1793297328 43
1793297333 43
1793297338 43
1793297343 43
1793297348 43
1793297353 48
1793297358 48
1793297363 48
1793297368 48
1793297373 48
1793297378 48
1793297383 48
1793297388 48
```
</details>

---

