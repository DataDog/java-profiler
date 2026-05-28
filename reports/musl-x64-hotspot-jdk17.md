---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-28 11:27:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 966 |
| Sample Rate | 16.10/sec |
| Health Score | 1006% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (5 unique values: 75-85 cores)</summary>

```
1779981655 85
1779981660 85
1779981666 85
1779981671 81
1779981676 81
1779981681 81
1779981686 79
1779981691 79
1779981696 79
1779981701 79
1779981706 79
1779981711 79
1779981716 79
1779981721 79
1779981726 79
1779981731 77
1779981736 77
1779981741 77
1779981746 77
1779981751 77
```
</details>

---

