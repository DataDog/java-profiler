---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-13 05:44:29 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 11 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 811 |
| Sample Rate | 13.52/sec |
| Health Score | 845% |
| Threads | 12 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 38-45 cores)</summary>

```
1773394740 45
1773394745 45
1773394750 45
1773394755 45
1773394760 45
1773394765 45
1773394770 45
1773394775 43
1773394780 43
1773394785 43
1773394790 43
1773394795 43
1773394800 43
1773394805 40
1773394810 40
1773394815 40
1773394820 40
1773394825 40
1773394830 40
1773394835 40
```
</details>

---

