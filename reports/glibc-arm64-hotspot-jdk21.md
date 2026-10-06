---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-06 09:07:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 9 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (4 unique values: 38-45 cores)</summary>

```
1791291562 43
1791291567 43
1791291572 43
1791291577 43
1791291582 43
1791291587 43
1791291592 41
1791291597 41
1791291602 41
1791291607 41
1791291612 41
1791291617 41
1791291622 41
1791291627 41
1791291632 38
1791291637 38
1791291642 38
1791291647 38
1791291652 38
1791291657 38
```
</details>

---

