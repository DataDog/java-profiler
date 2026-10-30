---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 01:04:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 74-86 cores)</summary>

```
1793336393 84
1793336398 84
1793336403 84
1793336408 84
1793336413 84
1793336418 84
1793336423 86
1793336428 86
1793336433 86
1793336438 86
1793336443 74
1793336448 74
1793336453 74
1793336458 74
1793336463 74
1793336468 74
1793336473 74
1793336478 74
1793336483 74
1793336488 76
```
</details>

---

