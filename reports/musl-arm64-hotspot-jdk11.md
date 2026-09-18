---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:39:52 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (4 unique values: 39-54 cores)</summary>

```
1789716547 49
1789716552 49
1789716557 49
1789716562 49
1789716567 49
1789716572 49
1789716577 54
1789716582 54
1789716587 54
1789716592 54
1789716597 54
1789716602 54
1789716607 54
1789716612 54
1789716617 49
1789716622 49
1789716627 49
1789716632 49
1789716637 49
1789716642 49
```
</details>

---

