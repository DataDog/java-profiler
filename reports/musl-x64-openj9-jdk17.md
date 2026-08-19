---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-19 05:17:44 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1126 |
| Sample Rate | 18.77/sec |
| Health Score | 1173% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1787130775 96
1787130780 96
1787130785 96
1787130790 96
1787130795 96
1787130800 96
1787130805 96
1787130810 96
1787130815 96
1787130820 96
1787130825 96
1787130830 96
1787130835 96
1787130840 96
1787130845 96
1787130850 96
1787130855 96
1787130860 76
1787130865 76
1787130870 76
```
</details>

---

