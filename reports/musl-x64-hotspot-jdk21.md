---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-12 11:39:22 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 13 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (5 unique values: 76-91 cores)</summary>

```
1773329754 76
1773329759 76
1773329764 76
1773329769 76
1773329775 76
1773329780 88
1773329785 88
1773329790 88
1773329795 90
1773329800 90
1773329805 90
1773329810 85
1773329815 85
1773329820 85
1773329825 85
1773329830 91
1773329835 91
1773329840 91
1773329845 91
1773329850 91
```
</details>

---

