---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 17:16:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (5 unique values: 66-86 cores)</summary>

```
1794435116 71
1794435121 68
1794435126 68
1794435131 66
1794435136 66
1794435141 66
1794435146 66
1794435151 66
1794435156 66
1794435161 66
1794435166 66
1794435171 86
1794435176 86
1794435181 86
1794435186 86
1794435191 86
1794435196 86
1794435201 86
1794435206 83
1794435211 83
```
</details>

---

