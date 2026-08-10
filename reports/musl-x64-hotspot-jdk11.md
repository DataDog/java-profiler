---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 15:31:45 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 842 |
| Sample Rate | 14.03/sec |
| Health Score | 877% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (4 unique values: 59-77 cores)</summary>

```
1786389980 77
1786389985 69
1786389990 69
1786389995 69
1786390000 71
1786390005 71
1786390010 71
1786390015 71
1786390020 71
1786390025 71
1786390030 71
1786390035 71
1786390040 71
1786390045 71
1786390050 59
1786390055 59
1786390060 59
1786390065 59
1786390070 59
1786390075 59
```
</details>

---

