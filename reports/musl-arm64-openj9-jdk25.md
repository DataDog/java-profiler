---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 04:31:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 14 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795166778 50
1795166783 50
1795166788 50
1795166793 50
1795166798 50
1795166803 50
1795166808 50
1795166813 50
1795166818 50
1795166823 50
1795166828 50
1795166833 50
1795166838 50
1795166843 50
1795166848 50
1795166853 50
1795166858 50
1795166863 50
1795166868 50
1795166873 50
```
</details>

---

