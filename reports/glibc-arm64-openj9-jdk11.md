---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 00:57:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 266 |
| Sample Rate | 4.43/sec |
| Health Score | 277% |
| Threads | 10 |
| Allocations | 193 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 244 |
| Sample Rate | 4.07/sec |
| Health Score | 254% |
| Threads | 10 |
| Allocations | 151 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1789966335 43
1789966340 43
1789966345 43
1789966350 43
1789966355 43
1789966360 43
1789966365 43
1789966370 43
1789966375 43
1789966380 43
1789966385 43
1789966390 43
1789966395 43
1789966400 43
1789966405 43
1789966410 43
1789966415 38
1789966420 38
1789966425 38
1789966430 38
```
</details>

---

