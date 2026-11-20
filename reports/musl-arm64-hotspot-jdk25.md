---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 16:44:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
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
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795210795 50
1795210800 50
1795210805 50
1795210810 50
1795210815 50
1795210820 50
1795210825 50
1795210830 50
1795210835 50
1795210841 50
1795210846 50
1795210851 50
1795210856 50
1795210861 50
1795210866 50
1795210871 50
1795210876 50
1795210881 50
1795210886 50
1795210891 50
```
</details>

---

