---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 06:56:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
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
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795434744 48
1795434749 48
1795434754 48
1795434759 48
1795434764 48
1795434769 48
1795434774 48
1795434779 48
1795434784 48
1795434789 48
1795434794 48
1795434799 48
1795434804 48
1795434809 48
1795434814 48
1795434819 48
1795434824 48
1795434829 48
1795434834 64
1795434839 64
```
</details>

---

