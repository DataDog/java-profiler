---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 05:21:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 48-56 cores)</summary>

```
1794478527 56
1794478532 56
1794478537 56
1794478542 56
1794478547 56
1794478552 56
1794478557 56
1794478562 56
1794478567 56
1794478572 56
1794478577 56
1794478582 48
1794478587 48
1794478592 48
1794478597 48
1794478602 48
1794478607 48
1794478612 48
1794478617 48
1794478622 50
```
</details>

---

