---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:29:42 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 42-43 cores)</summary>

```
1794392595 42
1794392600 42
1794392605 42
1794392610 42
1794392615 42
1794392620 42
1794392625 42
1794392630 43
1794392635 43
1794392640 43
1794392645 43
1794392650 43
1794392655 43
1794392660 43
1794392665 43
1794392670 43
1794392675 43
1794392680 43
1794392685 43
1794392690 43
```
</details>

---

