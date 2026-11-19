---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 18:13:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 6 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795129730 50
1795129735 50
1795129740 50
1795129745 50
1795129750 50
1795129755 50
1795129760 50
1795129765 50
1795129770 50
1795129775 50
1795129780 50
1795129785 50
1795129790 50
1795129795 50
1795129800 50
1795129805 50
1795129810 50
1795129815 50
1795129820 50
1795129825 50
```
</details>

---

