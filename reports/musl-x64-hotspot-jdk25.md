---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 06:08:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 11 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1794567734 94
1794567739 96
1794567744 96
1794567749 96
1794567754 96
1794567759 96
1794567765 96
1794567770 96
1794567775 96
1794567780 94
1794567785 94
1794567790 94
1794567795 94
1794567800 94
1794567805 94
1794567810 94
1794567815 94
1794567820 94
1794567825 94
1794567830 94
```
</details>

---

