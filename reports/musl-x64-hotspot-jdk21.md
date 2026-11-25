---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 14:53:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 65 |
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
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (4 unique values: 61-70 cores)</summary>

```
1795636123 61
1795636128 70
1795636133 70
1795636138 70
1795636143 70
1795636148 70
1795636153 70
1795636158 70
1795636163 70
1795636168 70
1795636173 70
1795636178 70
1795636183 70
1795636188 70
1795636193 70
1795636198 67
1795636203 67
1795636208 67
1795636213 65
1795636218 65
```
</details>

---

