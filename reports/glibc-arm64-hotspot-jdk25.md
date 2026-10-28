---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 13:11:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 10 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (3 unique values: 48-53 cores)</summary>

```
1793207268 48
1793207273 53
1793207278 53
1793207283 53
1793207288 53
1793207293 53
1793207298 53
1793207303 53
1793207308 53
1793207313 53
1793207318 53
1793207323 53
1793207328 53
1793207333 53
1793207338 53
1793207343 53
1793207348 53
1793207353 53
1793207358 53
1793207363 51
```
</details>

---

