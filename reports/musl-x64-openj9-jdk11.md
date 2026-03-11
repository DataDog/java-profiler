---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-11 14:08:00 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 9 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1773252140 26
1773252145 26
1773252150 26
1773252155 26
1773252160 26
1773252165 26
1773252170 26
1773252175 26
1773252180 28
1773252185 28
1773252190 26
1773252195 26
1773252200 28
1773252205 28
1773252210 30
1773252215 30
1773252220 30
1773252225 30
1773252230 30
1773252235 32
```
</details>

---

