---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-30 09:45:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (6 unique values: 67-76 cores)</summary>

```
1793367640 67
1793367645 67
1793367650 67
1793367655 69
1793367660 69
1793367665 71
1793367670 71
1793367675 71
1793367680 71
1793367685 71
1793367690 71
1793367695 71
1793367700 68
1793367705 68
1793367710 74
1793367715 74
1793367720 74
1793367725 74
1793367730 74
1793367735 74
```
</details>

---

