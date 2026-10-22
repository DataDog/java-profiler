---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 05:55:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 8 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792662646 43
1792662651 43
1792662656 43
1792662661 43
1792662666 48
1792662671 48
1792662676 48
1792662681 48
1792662686 48
1792662691 48
1792662696 48
1792662701 48
1792662706 48
1792662711 48
1792662716 48
1792662721 48
1792662726 48
1792662731 48
1792662736 48
1792662741 48
```
</details>

---

