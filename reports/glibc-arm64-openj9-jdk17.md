---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 10:59:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 318 |
| Sample Rate | 5.30/sec |
| Health Score | 331% |
| Threads | 13 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793721303 46
1793721308 46
1793721313 46
1793721318 51
1793721323 51
1793721328 51
1793721333 51
1793721338 51
1793721343 51
1793721348 51
1793721353 51
1793721358 51
1793721363 51
1793721368 51
1793721373 51
1793721378 51
1793721383 51
1793721388 51
1793721393 51
1793721398 51
```
</details>

---

