---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 09:45:21 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 59-76 cores)</summary>

```
1793367624 76
1793367629 76
1793367634 76
1793367639 76
1793367644 59
1793367649 59
1793367654 59
1793367659 59
1793367665 59
1793367670 59
1793367675 59
1793367680 59
1793367685 59
1793367690 59
1793367695 59
1793367700 59
1793367705 59
1793367710 59
1793367715 59
1793367720 59
```
</details>

---

