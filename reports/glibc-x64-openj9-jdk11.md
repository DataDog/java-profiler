---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-29 09:48:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 19.67/sec |
| Health Score | 1229% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 808 |
| Sample Rate | 26.93/sec |
| Health Score | 1683% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (5 unique values: 62-90 cores)</summary>

```
1769697806 62
1769697811 62
1769697816 62
1769697821 62
1769697826 62
1769697831 62
1769697836 62
1769697841 62
1769697846 66
1769697851 66
1769697856 66
1769697861 66
1769697866 66
1769697872 66
1769697877 66
1769697882 63
1769697887 63
1769697892 63
1769697897 63
1769697902 63
```
</details>

---

