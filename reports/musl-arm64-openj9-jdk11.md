---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-09 07:07:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 8 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791543720 43
1791543725 43
1791543730 43
1791543735 43
1791543740 43
1791543745 48
1791543750 48
1791543755 48
1791543760 48
1791543765 43
1791543770 43
1791543775 43
1791543780 43
1791543785 43
1791543790 43
1791543795 43
1791543800 43
1791543805 43
1791543810 43
1791543815 43
```
</details>

---

