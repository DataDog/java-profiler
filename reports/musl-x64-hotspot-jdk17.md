---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 09:18:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (4 unique values: 47-61 cores)</summary>

```
1794492690 57
1794492695 57
1794492700 57
1794492705 57
1794492710 57
1794492715 61
1794492720 61
1794492725 61
1794492730 61
1794492735 61
1794492740 61
1794492745 61
1794492750 61
1794492755 61
1794492761 61
1794492766 61
1794492771 61
1794492776 61
1794492781 61
1794492786 61
```
</details>

---

