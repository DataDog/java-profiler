---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 16:44:21 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795210753 50
1795210758 50
1795210763 50
1795210768 50
1795210773 50
1795210778 50
1795210783 50
1795210788 50
1795210793 50
1795210798 50
1795210803 50
1795210808 50
1795210813 50
1795210818 50
1795210823 50
1795210828 50
1795210833 50
1795210838 50
1795210843 50
1795210848 50
```
</details>

---

