---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-07 13:11:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1786122390 32
1786122395 32
1786122400 32
1786122405 32
1786122410 32
1786122415 32
1786122420 32
1786122425 32
1786122430 32
1786122435 32
1786122440 32
1786122445 32
1786122450 32
1786122455 32
1786122460 32
1786122465 32
1786122470 32
1786122475 32
1786122480 32
1786122485 32
```
</details>

---

