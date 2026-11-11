---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 06:35:25 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 10 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 52-96 cores)</summary>

```
1794396649 74
1794396654 74
1794396659 74
1794396664 74
1794396669 74
1794396674 74
1794396679 74
1794396684 74
1794396689 74
1794396694 74
1794396699 96
1794396704 96
1794396709 96
1794396714 96
1794396719 52
1794396724 52
1794396729 52
1794396734 52
1794396739 52
1794396744 52
```
</details>

---

