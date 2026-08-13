---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-13 11:55:11 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (5 unique values: 65-80 cores)</summary>

```
1786636201 65
1786636206 65
1786636211 65
1786636216 65
1786636221 65
1786636226 65
1786636231 65
1786636236 67
1786636241 67
1786636246 75
1786636251 75
1786636256 75
1786636261 78
1786636266 78
1786636271 78
1786636276 78
1786636281 78
1786636286 78
1786636291 78
1786636296 78
```
</details>

---

