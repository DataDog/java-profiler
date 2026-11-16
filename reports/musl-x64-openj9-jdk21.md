---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 09:37:47 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 72-76 cores)</summary>

```
1794839610 72
1794839615 72
1794839620 72
1794839625 72
1794839630 74
1794839635 74
1794839640 76
1794839645 76
1794839650 76
1794839655 76
1794839660 76
1794839665 76
1794839670 76
1794839675 76
1794839680 76
1794839685 76
1794839690 76
1794839695 76
1794839700 76
1794839705 76
```
</details>

---

