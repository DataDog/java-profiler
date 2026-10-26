---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-26 08:33:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 10-30 cores)</summary>

```
1793017740 10
1793017745 10
1793017750 12
1793017755 12
1793017760 12
1793017765 12
1793017770 10
1793017775 10
1793017780 30
1793017785 30
1793017790 30
1793017795 30
1793017800 30
1793017805 30
1793017810 30
1793017815 30
1793017820 30
1793017825 30
1793017830 30
1793017835 30
```
</details>

---

