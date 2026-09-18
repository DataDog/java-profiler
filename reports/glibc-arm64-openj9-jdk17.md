---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:26:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 10 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 11 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1789737635 36
1789737640 36
1789737645 36
1789737650 36
1789737655 36
1789737660 36
1789737665 36
1789737670 36
1789737675 48
1789737680 48
1789737685 48
1789737690 48
1789737695 48
1789737700 48
1789737705 48
1789737710 48
1789737715 48
1789737720 48
1789737725 48
1789737730 48
```
</details>

---

