---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:57:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 931 |
| Sample Rate | 15.52/sec |
| Health Score | 970% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 55-64 cores)</summary>

```
1794408625 64
1794408630 64
1794408635 64
1794408640 64
1794408645 64
1794408650 64
1794408655 64
1794408660 55
1794408665 55
1794408670 55
1794408675 55
1794408680 55
1794408685 55
1794408691 55
1794408696 55
1794408701 55
1794408706 55
1794408711 55
1794408716 55
1794408721 55
```
</details>

---

