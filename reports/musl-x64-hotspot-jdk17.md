---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 09:59:32 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 83 |
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
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 67-83 cores)</summary>

```
1770130530 72
1770130535 72
1770130540 67
1770130545 67
1770130550 67
1770130555 67
1770130560 71
1770130565 71
1770130570 71
1770130575 71
1770130580 71
1770130585 71
1770130590 71
1770130595 83
1770130600 83
1770130605 83
1770130610 83
1770130615 83
1770130620 83
1770130625 83
```
</details>

---

