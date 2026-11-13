---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 11:01:29 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794585447 48
1794585452 48
1794585457 48
1794585462 48
1794585467 48
1794585472 48
1794585477 48
1794585482 48
1794585487 48
1794585492 48
1794585497 48
1794585502 48
1794585507 48
1794585512 48
1794585517 48
1794585522 48
1794585527 48
1794585532 48
1794585537 48
1794585542 48
```
</details>

---

