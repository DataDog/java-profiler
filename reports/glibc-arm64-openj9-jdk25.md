---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 19:14:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 12 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 11 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1789686523 48
1789686528 48
1789686533 48
1789686538 48
1789686543 43
1789686548 43
1789686553 43
1789686558 43
1789686563 43
1789686568 43
1789686573 43
1789686578 43
1789686583 43
1789686588 43
1789686593 47
1789686598 47
1789686603 47
1789686608 47
1789686613 47
1789686618 47
```
</details>

---

