---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-21 17:49:36 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 14-30 cores)</summary>

```
1792619105 14
1792619110 14
1792619115 14
1792619120 30
1792619125 30
1792619130 30
1792619135 30
1792619140 30
1792619145 30
1792619150 30
1792619155 30
1792619160 30
1792619165 30
1792619170 30
1792619175 30
1792619180 30
1792619185 30
1792619190 30
1792619195 30
1792619200 30
```
</details>

---

