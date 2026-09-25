---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-25 06:49:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 10 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 11 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 56-76 cores)</summary>

```
1790332968 64
1790332973 64
1790332978 64
1790332983 64
1790332988 64
1790332993 64
1790332998 64
1790333003 64
1790333008 64
1790333013 56
1790333018 56
1790333023 56
1790333028 56
1790333033 56
1790333038 56
1790333043 56
1790333048 56
1790333053 56
1790333058 56
1790333063 56
```
</details>

---

