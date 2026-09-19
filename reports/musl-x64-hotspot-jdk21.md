---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-19 00:58:50 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 54-66 cores)</summary>

```
1789793666 54
1789793671 54
1789793676 54
1789793681 54
1789793686 54
1789793691 54
1789793696 54
1789793701 60
1789793706 60
1789793711 60
1789793716 60
1789793721 60
1789793726 60
1789793731 60
1789793736 60
1789793741 60
1789793746 60
1789793751 66
1789793756 66
1789793761 66
```
</details>

---

