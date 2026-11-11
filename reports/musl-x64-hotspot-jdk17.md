---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:37:21 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1794396737 28
1794396742 28
1794396747 28
1794396752 28
1794396757 28
1794396762 28
1794396767 28
1794396772 28
1794396777 28
1794396782 28
1794396787 28
1794396792 28
1794396797 30
1794396802 30
1794396807 32
1794396812 32
1794396817 32
1794396822 32
1794396827 32
1794396832 32
```
</details>

---

