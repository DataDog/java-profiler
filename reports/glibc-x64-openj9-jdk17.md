---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 12:22:25 EDT

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
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792426623 30
1792426628 30
1792426633 30
1792426638 30
1792426643 32
1792426648 32
1792426653 30
1792426658 30
1792426663 30
1792426668 30
1792426673 30
1792426678 30
1792426683 30
1792426688 30
1792426693 30
1792426698 30
1792426703 30
1792426708 30
1792426713 30
1792426718 30
```
</details>

---

