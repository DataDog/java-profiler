---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-15 05:49:48 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (5 unique values: 46-50 cores)</summary>

```
1778838162 49
1778838167 49
1778838172 49
1778838177 49
1778838182 49
1778838187 49
1778838192 49
1778838197 49
1778838202 46
1778838207 46
1778838212 46
1778838217 46
1778838222 46
1778838227 46
1778838232 46
1778838237 46
1778838242 46
1778838247 46
1778838252 46
1778838257 48
```
</details>

---

