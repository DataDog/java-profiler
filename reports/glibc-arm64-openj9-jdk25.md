---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-24 17:08:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787605378 64
1787605383 64
1787605388 64
1787605393 64
1787605398 64
1787605403 64
1787605408 64
1787605413 64
1787605418 64
1787605423 64
1787605428 64
1787605433 64
1787605438 64
1787605443 64
1787605448 64
1787605453 64
1787605458 64
1787605463 64
1787605468 64
1787605473 64
```
</details>

---

