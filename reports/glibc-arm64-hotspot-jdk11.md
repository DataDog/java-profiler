---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-22 05:27:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 13 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1787390470 47
1787390475 47
1787390480 47
1787390485 47
1787390490 47
1787390495 47
1787390500 47
1787390505 47
1787390510 47
1787390515 47
1787390520 47
1787390525 47
1787390530 48
1787390535 48
1787390540 48
1787390545 48
1787390550 48
1787390555 48
1787390560 48
1787390565 48
```
</details>

---

