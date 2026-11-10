---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 14:54:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
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
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794340086 46
1794340091 46
1794340096 46
1794340101 46
1794340106 46
1794340111 46
1794340116 46
1794340121 46
1794340126 46
1794340131 46
1794340136 46
1794340142 46
1794340147 46
1794340152 46
1794340157 48
1794340162 48
1794340167 48
1794340172 48
1794340177 48
1794340182 48
```
</details>

---

