---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 11:43:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 11-18 cores)</summary>

```
1795624621 11
1795624626 11
1795624631 11
1795624636 11
1795624641 13
1795624646 13
1795624651 13
1795624656 13
1795624661 13
1795624666 13
1795624671 13
1795624676 13
1795624681 18
1795624686 18
1795624691 18
1795624696 18
1795624701 18
1795624706 18
1795624711 18
1795624716 18
```
</details>

---

