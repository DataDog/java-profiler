---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 09:09:13 EDT

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
| CPU Cores (start) | 7 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 7-12 cores)</summary>

```
1790168622 7
1790168627 7
1790168632 12
1790168637 12
1790168642 12
1790168647 12
1790168652 12
1790168657 12
1790168662 12
1790168667 12
1790168672 12
1790168677 12
1790168682 12
1790168687 12
1790168692 12
1790168697 12
1790168702 12
1790168707 12
1790168712 12
1790168717 12
```
</details>

---

