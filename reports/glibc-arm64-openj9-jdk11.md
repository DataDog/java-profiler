---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 08:00:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 14 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795006537 51
1795006542 51
1795006547 51
1795006552 51
1795006557 51
1795006562 46
1795006567 46
1795006572 46
1795006577 46
1795006582 46
1795006587 46
1795006592 46
1795006597 46
1795006602 46
1795006607 46
1795006612 46
1795006617 46
1795006622 46
1795006627 46
1795006632 51
```
</details>

---

