---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-23 16:41:00 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (6 unique values: 34-71 cores)</summary>

```
1792787748 38
1792787753 34
1792787758 34
1792787763 34
1792787768 34
1792787773 36
1792787778 36
1792787783 36
1792787788 36
1792787793 38
1792787798 38
1792787803 38
1792787808 71
1792787813 71
1792787818 71
1792787823 71
1792787828 50
1792787833 50
1792787838 50
1792787843 52
```
</details>

---

