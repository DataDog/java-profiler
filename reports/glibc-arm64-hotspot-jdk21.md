---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 16:44:19 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 11 |
| Allocations | 144 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 10 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1795210808 35
1795210813 35
1795210818 35
1795210823 35
1795210828 35
1795210833 35
1795210838 35
1795210843 35
1795210848 35
1795210853 30
1795210858 30
1795210863 30
1795210868 30
1795210873 30
1795210878 30
1795210883 30
1795210888 30
1795210893 30
1795210898 30
1795210903 30
```
</details>

---

