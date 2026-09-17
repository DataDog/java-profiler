---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-17 19:15:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 76-80 cores)</summary>

```
1789686642 80
1789686647 80
1789686652 80
1789686657 80
1789686662 80
1789686667 80
1789686672 80
1789686677 80
1789686682 80
1789686687 80
1789686692 80
1789686697 80
1789686702 80
1789686707 80
1789686712 80
1789686717 80
1789686722 76
1789686727 76
1789686732 76
1789686737 76
```
</details>

---

