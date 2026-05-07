---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-05-07 17:16:19 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 66-82 cores)</summary>

```
1778188129 66
1778188134 66
1778188139 66
1778188144 66
1778188149 66
1778188154 66
1778188159 71
1778188164 71
1778188169 71
1778188174 71
1778188179 71
1778188184 71
1778188189 71
1778188194 73
1778188199 73
1778188204 73
1778188209 73
1778188214 73
1778188219 73
1778188224 79
```
</details>

---

