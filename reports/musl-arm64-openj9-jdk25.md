---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 09:14:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 438 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 11 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794319705 43
1794319710 43
1794319715 43
1794319720 43
1794319725 43
1794319730 43
1794319735 43
1794319740 43
1794319745 43
1794319750 43
1794319755 43
1794319760 43
1794319765 43
1794319770 43
1794319775 43
1794319780 43
1794319785 48
1794319790 48
1794319795 48
1794319800 48
```
</details>

---

