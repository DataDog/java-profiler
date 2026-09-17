---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 15:41:04 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 73-86 cores)</summary>

```
1789673462 73
1789673467 73
1789673472 73
1789673477 73
1789673482 73
1789673487 78
1789673492 78
1789673497 86
1789673502 86
1789673507 86
1789673512 86
1789673517 86
1789673522 86
1789673527 86
1789673532 86
1789673537 86
1789673542 86
1789673547 86
1789673552 86
1789673557 86
```
</details>

---

