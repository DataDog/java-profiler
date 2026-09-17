---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 19:15:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (3 unique values: 65-96 cores)</summary>

```
1789686647 65
1789686652 65
1789686657 65
1789686662 65
1789686667 88
1789686672 88
1789686677 88
1789686682 88
1789686687 88
1789686692 88
1789686697 96
1789686702 96
1789686707 96
1789686712 96
1789686717 96
1789686722 96
1789686727 96
1789686732 96
1789686737 96
1789686742 96
```
</details>

---

