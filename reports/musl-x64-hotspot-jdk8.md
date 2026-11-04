---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-04 12:28:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 211 |
| Sample Rate | 3.52/sec |
| Health Score | 220% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 82-84 cores)</summary>

```
1793812826 84
1793812831 84
1793812836 84
1793812841 84
1793812846 84
1793812851 84
1793812856 84
1793812861 84
1793812867 84
1793812872 84
1793812877 84
1793812882 84
1793812887 82
1793812892 82
1793812897 82
1793812902 82
1793812907 82
1793812912 82
1793812917 82
1793812922 82
```
</details>

---

