---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 12:37:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794850044 46
1794850049 46
1794850054 46
1794850059 46
1794850064 46
1794850069 46
1794850074 46
1794850079 48
1794850084 48
1794850089 48
1794850094 48
1794850099 48
1794850104 48
1794850109 48
1794850114 48
1794850119 48
1794850124 48
1794850129 48
1794850134 48
1794850139 48
```
</details>

---

