---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:02:39 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795618570 33
1795618575 33
1795618580 33
1795618585 33
1795618590 33
1795618595 33
1795618600 33
1795618605 33
1795618610 33
1795618615 33
1795618620 33
1795618625 33
1795618630 33
1795618635 33
1795618640 33
1795618645 33
1795618650 33
1795618655 33
1795618660 64
1795618665 64
```
</details>

---

