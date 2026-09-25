---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 07:37:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 801 |
| Sample Rate | 13.35/sec |
| Health Score | 834% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 68-76 cores)</summary>

```
1790335985 76
1790335990 76
1790335995 76
1790336000 76
1790336005 76
1790336010 76
1790336015 76
1790336020 76
1790336025 76
1790336030 76
1790336035 76
1790336040 76
1790336045 76
1790336050 76
1790336055 76
1790336060 76
1790336065 76
1790336070 76
1790336075 68
1790336080 68
```
</details>

---

