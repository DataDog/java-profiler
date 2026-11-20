---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 05:39:02 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 14 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795170740 50
1795170745 50
1795170750 50
1795170755 50
1795170760 50
1795170765 50
1795170770 50
1795170775 50
1795170780 50
1795170785 50
1795170790 50
1795170795 50
1795170800 50
1795170805 50
1795170810 50
1795170815 50
1795170820 50
1795170825 50
1795170830 50
1795170835 50
```
</details>

---

