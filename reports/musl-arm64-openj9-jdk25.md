---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 13:54:16 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 316 |
| Sample Rate | 5.27/sec |
| Health Score | 329% |
| Threads | 11 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789667271 43
1789667276 43
1789667281 43
1789667286 43
1789667291 43
1789667296 43
1789667301 43
1789667306 48
1789667311 48
1789667316 48
1789667321 48
1789667326 48
1789667331 48
1789667336 48
1789667341 48
1789667346 48
1789667351 48
1789667356 48
1789667361 48
1789667366 48
```
</details>

---

