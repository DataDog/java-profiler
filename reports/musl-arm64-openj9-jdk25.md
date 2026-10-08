---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-08 09:20:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 47-51 cores)</summary>

```
1791465267 51
1791465272 51
1791465277 51
1791465282 51
1791465287 51
1791465292 51
1791465297 51
1791465302 51
1791465307 51
1791465312 51
1791465317 51
1791465322 51
1791465327 51
1791465332 49
1791465337 49
1791465342 49
1791465347 49
1791465352 49
1791465357 49
1791465362 49
```
</details>

---

