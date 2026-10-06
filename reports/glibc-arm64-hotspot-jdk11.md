---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 09:07:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 8 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 35-40 cores)</summary>

```
1791291597 35
1791291602 35
1791291607 35
1791291612 35
1791291617 35
1791291622 35
1791291627 35
1791291632 35
1791291637 40
1791291642 40
1791291647 40
1791291652 40
1791291657 40
1791291662 40
1791291667 40
1791291672 40
1791291677 40
1791291682 40
1791291687 40
1791291692 40
```
</details>

---

