---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 13:18:39 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 11 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 42 |
| Sample Rate | 0.70/sec |
| Health Score | 44% |
| Threads | 10 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1795025650 51
1795025655 51
1795025660 51
1795025665 51
1795025670 51
1795025675 38
1795025680 38
1795025685 38
1795025690 38
1795025695 38
1795025700 38
1795025705 38
1795025710 38
1795025715 38
1795025720 38
1795025725 38
1795025730 38
1795025735 38
1795025740 38
1795025745 38
```
</details>

---

