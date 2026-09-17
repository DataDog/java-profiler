---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 06:26:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 8 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1789640510 30
1789640515 30
1789640520 30
1789640525 30
1789640530 30
1789640535 28
1789640540 28
1789640545 28
1789640550 28
1789640555 28
1789640560 28
1789640565 28
1789640570 28
1789640575 30
1789640580 30
1789640585 30
1789640590 28
1789640595 28
1789640600 28
1789640605 28
```
</details>

---

