---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-07 07:29:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1791372327 53
1791372332 53
1791372337 53
1791372342 53
1791372347 53
1791372352 53
1791372357 53
1791372362 53
1791372367 53
1791372372 53
1791372377 53
1791372382 53
1791372387 53
1791372392 53
1791372397 64
1791372402 64
1791372407 53
1791372412 53
1791372417 53
1791372422 53
```
</details>

---

