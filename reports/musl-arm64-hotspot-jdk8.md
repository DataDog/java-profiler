---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-17 09:09:13 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 306 |
| Sample Rate | 5.10/sec |
| Health Score | 319% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 38-48 cores)</summary>

```
1786971640 38
1786971645 38
1786971650 43
1786971655 43
1786971660 42
1786971665 42
1786971670 47
1786971675 47
1786971680 47
1786971685 47
1786971691 48
1786971696 48
1786971701 48
1786971706 48
1786971711 48
1786971716 48
1786971721 46
1786971726 46
1786971731 46
1786971736 46
```
</details>

---

