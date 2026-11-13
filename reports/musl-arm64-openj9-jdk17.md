---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 10:15:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1794582640 35
1794582645 35
1794582650 35
1794582655 35
1794582660 35
1794582665 35
1794582670 35
1794582675 35
1794582680 35
1794582685 40
1794582690 40
1794582696 40
1794582701 40
1794582706 40
1794582711 40
1794582716 40
1794582721 40
1794582726 40
1794582731 40
1794582736 40
```
</details>

---

