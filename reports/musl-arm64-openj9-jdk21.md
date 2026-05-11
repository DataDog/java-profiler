---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-11 11:23:14 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 13 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778512728 64
1778512733 64
1778512738 64
1778512743 64
1778512748 64
1778512753 64
1778512758 64
1778512763 64
1778512768 64
1778512773 64
1778512778 64
1778512783 64
1778512788 64
1778512793 64
1778512798 64
1778512803 64
1778512808 64
1778512813 64
1778512818 64
1778512823 64
```
</details>

---

