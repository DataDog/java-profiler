---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-25 06:23:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 55-60 cores)</summary>

```
1795605455 60
1795605460 60
1795605465 60
1795605470 60
1795605475 60
1795605480 60
1795605485 60
1795605490 60
1795605495 60
1795605500 60
1795605505 60
1795605510 60
1795605515 60
1795605520 60
1795605525 60
1795605530 55
1795605535 55
1795605540 55
1795605545 55
1795605550 55
```
</details>

---

