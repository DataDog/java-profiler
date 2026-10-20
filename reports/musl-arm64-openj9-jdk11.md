---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 07:43:41 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 7 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (4 unique values: 13-16 cores)</summary>

```
1792496356 16
1792496361 16
1792496366 16
1792496371 16
1792496376 16
1792496381 16
1792496386 14
1792496391 14
1792496396 13
1792496401 13
1792496406 13
1792496411 13
1792496416 13
1792496421 13
1792496426 13
1792496432 13
1792496437 13
1792496442 13
1792496447 13
1792496452 15
```
</details>

---

