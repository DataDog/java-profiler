---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-30 05:30:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1777541172 32
1777541177 32
1777541182 32
1777541187 32
1777541192 32
1777541197 32
1777541202 32
1777541208 32
1777541213 32
1777541218 32
1777541223 32
1777541228 32
1777541233 32
1777541238 32
1777541243 32
1777541248 32
1777541253 32
1777541258 32
1777541263 32
1777541268 32
```
</details>

---

