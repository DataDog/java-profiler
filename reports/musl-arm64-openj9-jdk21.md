---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-22 05:27:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 312 |
| Sample Rate | 5.20/sec |
| Health Score | 325% |
| Threads | 11 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 15 |
| Allocations | 93 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787390487 48
1787390492 48
1787390497 43
1787390502 43
1787390507 43
1787390513 43
1787390518 43
1787390523 43
1787390528 43
1787390533 43
1787390538 43
1787390543 43
1787390548 43
1787390553 43
1787390558 43
1787390563 48
1787390568 48
1787390573 48
1787390578 48
1787390583 48
```
</details>

---

