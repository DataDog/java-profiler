---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 00:07:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 399 |
| Sample Rate | 6.65/sec |
| Health Score | 416% |
| Threads | 11 |
| Allocations | 215 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 361 |
| Sample Rate | 6.02/sec |
| Health Score | 376% |
| Threads | 15 |
| Allocations | 170 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1793768532 38
1793768537 38
1793768542 43
1793768547 43
1793768552 43
1793768557 43
1793768562 43
1793768567 43
1793768572 43
1793768577 43
1793768582 43
1793768587 43
1793768592 43
1793768597 43
1793768602 43
1793768607 43
1793768612 43
1793768617 43
1793768622 43
1793768627 43
```
</details>

---

