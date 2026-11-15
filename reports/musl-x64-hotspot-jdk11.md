---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 05:56:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 9 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 9 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1794739918 81
1794739923 81
1794739928 81
1794739933 81
1794739938 81
1794739943 81
1794739948 81
1794739953 81
1794739958 81
1794739963 81
1794739968 81
1794739973 81
1794739978 81
1794739983 81
1794739988 81
1794739993 81
1794739998 81
1794740003 81
1794740008 81
1794740013 79
```
</details>

---

