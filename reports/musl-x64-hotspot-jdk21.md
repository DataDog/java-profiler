---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-08 12:51:00 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 843 |
| Sample Rate | 14.05/sec |
| Health Score | 878% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (4 unique values: 81-91 cores)</summary>

```
1775666660 81
1775666665 81
1775666670 81
1775666675 85
1775666680 85
1775666685 85
1775666690 85
1775666695 85
1775666700 85
1775666705 85
1775666710 85
1775666715 85
1775666720 85
1775666725 91
1775666730 91
1775666735 91
1775666740 91
1775666745 91
1775666750 91
1775666755 91
```
</details>

---

