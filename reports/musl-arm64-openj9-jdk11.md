---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-22 05:27:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 11 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (4 unique values: 24-44 cores)</summary>

```
1787390480 29
1787390485 29
1787390490 34
1787390495 34
1787390500 34
1787390505 34
1787390510 34
1787390515 34
1787390520 24
1787390525 24
1787390530 29
1787390535 29
1787390540 44
1787390545 44
1787390550 44
1787390555 44
1787390560 44
1787390565 44
1787390570 44
1787390575 44
```
</details>

---

