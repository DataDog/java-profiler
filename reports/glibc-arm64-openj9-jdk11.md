---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 11:46:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 10 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1786376388 59
1786376393 59
1786376398 59
1786376403 59
1786376408 59
1786376413 59
1786376418 59
1786376423 59
1786376428 59
1786376433 59
1786376438 59
1786376443 59
1786376448 59
1786376453 59
1786376459 59
1786376464 64
1786376469 64
1786376474 64
1786376479 64
1786376484 64
```
</details>

---

