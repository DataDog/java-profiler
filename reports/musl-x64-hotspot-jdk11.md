---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:43:46 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 9 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 51-72 cores)</summary>

```
1794998151 72
1794998156 72
1794998161 72
1794998166 72
1794998171 72
1794998176 72
1794998181 72
1794998186 72
1794998191 72
1794998196 72
1794998201 72
1794998206 72
1794998211 72
1794998216 51
1794998221 51
1794998226 51
1794998232 51
1794998237 51
1794998242 51
1794998247 51
```
</details>

---

