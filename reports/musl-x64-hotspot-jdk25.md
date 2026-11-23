---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 06:57:00 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 67-72 cores)</summary>

```
1795434707 72
1795434712 72
1795434717 72
1795434722 72
1795434727 72
1795434732 72
1795434737 72
1795434742 72
1795434747 72
1795434752 72
1795434757 72
1795434762 67
1795434767 67
1795434772 67
1795434777 67
1795434782 67
1795434787 67
1795434792 67
1795434797 67
1795434802 67
```
</details>

---

