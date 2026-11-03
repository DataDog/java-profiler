---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-03 16:51:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 210 |
| Sample Rate | 3.50/sec |
| Health Score | 219% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 212 |
| Sample Rate | 3.53/sec |
| Health Score | 221% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 73-84 cores)</summary>

```
1793742230 73
1793742235 73
1793742240 75
1793742245 75
1793742250 75
1793742255 75
1793742260 75
1793742265 75
1793742270 75
1793742275 75
1793742280 75
1793742285 75
1793742290 75
1793742295 75
1793742300 84
1793742305 84
1793742310 84
1793742315 84
1793742320 84
1793742325 79
```
</details>

---

