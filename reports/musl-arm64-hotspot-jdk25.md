---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 05:13:49 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 446 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 11 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793614079 51
1793614084 51
1793614089 46
1793614094 46
1793614099 46
1793614104 46
1793614109 46
1793614114 46
1793614119 46
1793614124 46
1793614129 46
1793614134 46
1793614139 46
1793614144 46
1793614149 51
1793614154 51
1793614159 51
1793614164 51
1793614169 51
1793614174 51
```
</details>

---

