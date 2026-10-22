---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 08:32:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 46-68 cores)</summary>

```
1792672046 48
1792672051 48
1792672056 48
1792672061 48
1792672066 48
1792672071 48
1792672076 48
1792672081 48
1792672086 48
1792672091 48
1792672096 48
1792672101 46
1792672106 46
1792672111 46
1792672116 46
1792672121 46
1792672126 66
1792672131 66
1792672136 66
1792672141 68
```
</details>

---

