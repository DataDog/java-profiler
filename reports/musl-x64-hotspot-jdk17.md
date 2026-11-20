---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 16:44:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (4 unique values: 52-63 cores)</summary>

```
1795210732 61
1795210737 61
1795210742 63
1795210747 63
1795210752 63
1795210757 63
1795210762 63
1795210767 63
1795210772 63
1795210777 63
1795210783 63
1795210788 63
1795210793 63
1795210798 63
1795210803 63
1795210808 63
1795210813 63
1795210818 54
1795210823 54
1795210828 54
```
</details>

---

