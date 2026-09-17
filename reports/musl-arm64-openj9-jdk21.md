---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 16:48:49 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 10 |
| Allocations | 134 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 9 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789677750 48
1789677755 48
1789677760 48
1789677765 48
1789677771 48
1789677776 48
1789677781 48
1789677786 48
1789677791 48
1789677796 48
1789677801 48
1789677806 48
1789677811 48
1789677816 48
1789677821 48
1789677826 43
1789677831 43
1789677836 43
1789677841 43
1789677846 43
```
</details>

---

