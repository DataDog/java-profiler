---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-12 05:55:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 10 |
| Allocations | 152 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 12 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (3 unique values: 19-21 cores)</summary>

```
1791798715 19
1791798720 19
1791798725 19
1791798730 20
1791798735 20
1791798740 21
1791798745 21
1791798750 21
1791798755 21
1791798760 21
1791798765 21
1791798770 21
1791798775 21
1791798780 21
1791798785 21
1791798790 21
1791798795 21
1791798800 21
1791798805 21
1791798810 21
```
</details>

---

