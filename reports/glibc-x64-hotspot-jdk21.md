---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 11:12:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (5 unique values: 85-93 cores)</summary>

```
1794931720 93
1794931725 93
1794931730 91
1794931735 91
1794931740 91
1794931745 91
1794931750 91
1794931755 91
1794931760 89
1794931765 89
1794931770 89
1794931775 89
1794931780 89
1794931785 89
1794931790 89
1794931795 89
1794931800 89
1794931805 89
1794931810 89
1794931815 87
```
</details>

---

