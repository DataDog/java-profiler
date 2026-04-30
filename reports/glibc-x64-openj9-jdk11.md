---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-30 05:30:09 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 865 |
| Sample Rate | 14.42/sec |
| Health Score | 901% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 66-94 cores)</summary>

```
1777541173 94
1777541178 94
1777541183 94
1777541188 94
1777541193 94
1777541198 94
1777541203 94
1777541208 94
1777541213 81
1777541218 81
1777541223 81
1777541228 81
1777541233 81
1777541238 81
1777541243 81
1777541248 81
1777541253 81
1777541258 81
1777541263 81
1777541268 81
```
</details>

---

