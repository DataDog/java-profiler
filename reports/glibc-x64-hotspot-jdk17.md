---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-01 15:03:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 928 |
| Sample Rate | 15.47/sec |
| Health Score | 967% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 49-65 cores)</summary>

```
1788289021 63
1788289026 63
1788289031 63
1788289036 63
1788289041 63
1788289046 63
1788289051 65
1788289056 65
1788289061 51
1788289066 51
1788289071 51
1788289076 51
1788289081 51
1788289086 51
1788289091 51
1788289096 51
1788289101 51
1788289106 51
1788289111 49
1788289116 49
```
</details>

---

