---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 16:17:03 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 14 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 36-42 cores)</summary>

```
1794604432 42
1794604437 42
1794604442 42
1794604447 42
1794604452 39
1794604457 39
1794604462 39
1794604467 39
1794604472 39
1794604477 39
1794604482 39
1794604487 39
1794604492 39
1794604497 39
1794604502 39
1794604507 39
1794604512 39
1794604517 39
1794604522 39
1794604527 39
```
</details>

---

