---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 07:14:34 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 273 |
| Sample Rate | 4.55/sec |
| Health Score | 284% |
| Threads | 13 |
| Allocations | 159 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794399070 46
1794399075 46
1794399080 46
1794399085 46
1794399090 46
1794399095 46
1794399100 46
1794399105 48
1794399110 48
1794399115 48
1794399120 48
1794399125 48
1794399130 48
1794399135 48
1794399140 48
1794399145 48
1794399150 48
1794399155 48
1794399160 48
1794399165 48
```
</details>

---

