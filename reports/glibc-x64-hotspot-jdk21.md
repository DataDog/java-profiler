---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 13:47:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (4 unique values: 52-96 cores)</summary>

```
1793644993 52
1793644998 52
1793645003 52
1793645008 52
1793645013 54
1793645018 54
1793645023 54
1793645028 54
1793645033 75
1793645038 75
1793645043 75
1793645048 75
1793645053 96
1793645058 96
1793645063 96
1793645068 96
1793645073 96
1793645078 96
1793645083 96
1793645088 96
```
</details>

---

