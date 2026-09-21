---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 00:57:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1789966375 53
1789966380 53
1789966385 53
1789966390 53
1789966395 53
1789966400 53
1789966405 53
1789966410 53
1789966415 53
1789966420 53
1789966425 53
1789966430 53
1789966435 53
1789966440 53
1789966445 53
1789966450 53
1789966455 55
1789966460 55
1789966465 55
1789966470 55
```
</details>

---

