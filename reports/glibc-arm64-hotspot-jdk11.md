---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 16:17:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 10 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1794604377 44
1794604382 44
1794604387 44
1794604392 44
1794604397 39
1794604402 39
1794604407 39
1794604412 39
1794604417 39
1794604422 39
1794604427 39
1794604432 39
1794604437 39
1794604442 39
1794604447 39
1794604452 39
1794604457 39
1794604462 44
1794604467 44
1794604472 44
```
</details>

---

