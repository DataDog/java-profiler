---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 16:51:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 877 |
| Sample Rate | 14.62/sec |
| Health Score | 914% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 87-92 cores)</summary>

```
1793742150 87
1793742155 87
1793742160 87
1793742165 90
1793742170 90
1793742175 90
1793742180 92
1793742185 92
1793742190 92
1793742195 92
1793742200 92
1793742205 92
1793742210 92
1793742215 92
1793742220 92
1793742225 92
1793742230 92
1793742235 92
1793742240 92
1793742245 92
```
</details>

---

