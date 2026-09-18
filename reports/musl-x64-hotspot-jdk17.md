---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:07:48 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (4 unique values: 85-93 cores)</summary>

```
1789743557 87
1789743562 87
1789743567 87
1789743572 87
1789743577 87
1789743582 87
1789743587 85
1789743592 85
1789743597 85
1789743602 85
1789743607 85
1789743612 85
1789743617 85
1789743622 85
1789743627 85
1789743632 85
1789743637 85
1789743642 91
1789743647 91
1789743652 93
```
</details>

---

