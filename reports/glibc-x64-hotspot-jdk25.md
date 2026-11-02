---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 13:47:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 368 |
| Sample Rate | 6.13/sec |
| Health Score | 383% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 41-61 cores)</summary>

```
1793644983 41
1793644988 41
1793644993 41
1793644998 41
1793645003 41
1793645008 41
1793645013 41
1793645018 41
1793645023 41
1793645028 41
1793645033 61
1793645038 61
1793645043 61
1793645048 61
1793645053 61
1793645058 61
1793645063 61
1793645068 61
1793645073 61
1793645078 61
```
</details>

---

