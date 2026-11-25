---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 14:53:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (4 unique values: 33-59 cores)</summary>

```
1795636143 46
1795636148 46
1795636153 46
1795636158 46
1795636163 46
1795636168 46
1795636173 59
1795636178 59
1795636183 33
1795636188 33
1795636193 42
1795636198 42
1795636203 42
1795636208 42
1795636213 42
1795636218 42
1795636223 42
1795636228 42
1795636233 42
1795636238 42
```
</details>

---

