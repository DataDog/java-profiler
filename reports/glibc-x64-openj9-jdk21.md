---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 09:32:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 815 |
| Sample Rate | 13.58/sec |
| Health Score | 849% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 71-81 cores)</summary>

```
1787232421 79
1787232426 79
1787232431 79
1787232436 79
1787232441 79
1787232446 79
1787232451 81
1787232456 81
1787232461 73
1787232466 73
1787232471 73
1787232476 73
1787232481 73
1787232486 73
1787232491 73
1787232496 73
1787232501 73
1787232506 73
1787232511 73
1787232516 73
```
</details>

---

