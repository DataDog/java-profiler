---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 05:27:34 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 11 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794306094 48
1794306099 48
1794306104 48
1794306109 43
1794306114 43
1794306119 43
1794306124 43
1794306129 43
1794306134 43
1794306140 43
1794306145 43
1794306150 43
1794306155 43
1794306160 43
1794306165 43
1794306170 43
1794306175 43
1794306180 48
1794306185 48
1794306190 48
```
</details>

---

