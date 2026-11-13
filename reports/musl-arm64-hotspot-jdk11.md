---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 12:19:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
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
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794590054 43
1794590059 43
1794590064 43
1794590069 43
1794590074 43
1794590079 43
1794590084 46
1794590089 46
1794590094 46
1794590099 46
1794590104 46
1794590109 46
1794590114 46
1794590119 46
1794590125 48
1794590130 48
1794590135 48
1794590140 48
1794590145 48
1794590150 48
```
</details>

---

