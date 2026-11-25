---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 14:53:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 10 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (4 unique values: 33-59 cores)</summary>

```
1795636143 46
1795636148 46
1795636153 46
1795636158 46
1795636163 46
1795636168 59
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

