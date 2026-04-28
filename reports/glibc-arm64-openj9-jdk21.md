---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-28 09:37:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 11 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777383095 64
1777383100 64
1777383105 64
1777383110 59
1777383115 59
1777383120 59
1777383125 59
1777383130 59
1777383135 59
1777383140 59
1777383145 59
1777383150 59
1777383155 59
1777383160 59
1777383165 59
1777383170 59
1777383175 59
1777383180 59
1777383185 59
1777383190 59
```
</details>

---

