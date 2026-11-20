---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 04:31:01 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 259 |
| Sample Rate | 4.32/sec |
| Health Score | 270% |
| Threads | 12 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795166784 50
1795166789 50
1795166794 50
1795166799 50
1795166804 50
1795166809 50
1795166814 50
1795166819 50
1795166824 50
1795166829 50
1795166834 50
1795166839 50
1795166844 50
1795166849 50
1795166854 50
1795166859 50
1795166864 50
1795166869 50
1795166874 50
1795166879 50
```
</details>

---

