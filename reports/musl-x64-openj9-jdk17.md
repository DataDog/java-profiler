---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 06:57:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 43-71 cores)</summary>

```
1795434712 43
1795434717 43
1795434722 43
1795434727 43
1795434732 43
1795434737 71
1795434742 71
1795434747 71
1795434752 71
1795434757 71
1795434762 71
1795434767 71
1795434772 71
1795434777 71
1795434782 71
1795434787 71
1795434792 71
1795434797 71
1795434802 71
1795434807 71
```
</details>

---

