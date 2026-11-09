---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 10:19:57 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 833 |
| Sample Rate | 13.88/sec |
| Health Score | 868% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 70-80 cores)</summary>

```
1794237215 70
1794237220 80
1794237225 80
1794237230 80
1794237235 73
1794237240 73
1794237245 73
1794237250 73
1794237255 73
1794237260 73
1794237265 73
1794237270 73
1794237275 73
1794237280 73
1794237286 73
1794237291 73
1794237296 73
1794237301 73
1794237306 75
1794237311 75
```
</details>

---

