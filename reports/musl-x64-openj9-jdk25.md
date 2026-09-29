---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-29 13:06:02 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 845 |
| Sample Rate | 14.08/sec |
| Health Score | 880% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 52-65 cores)</summary>

```
1790701229 52
1790701234 52
1790701239 52
1790701244 52
1790701249 52
1790701254 52
1790701259 52
1790701264 61
1790701269 61
1790701275 61
1790701280 61
1790701285 61
1790701290 61
1790701295 61
1790701300 61
1790701305 61
1790701310 61
1790701315 61
1790701320 61
1790701325 61
```
</details>

---

