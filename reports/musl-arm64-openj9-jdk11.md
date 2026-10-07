---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-07 07:29:48 EDT

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
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 13 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 43-46 cores)</summary>

```
1791372306 43
1791372311 43
1791372316 43
1791372321 43
1791372326 43
1791372331 43
1791372336 43
1791372341 43
1791372346 43
1791372351 43
1791372356 43
1791372361 46
1791372366 46
1791372371 46
1791372376 46
1791372381 46
1791372386 46
1791372391 46
1791372396 46
1791372401 46
```
</details>

---

