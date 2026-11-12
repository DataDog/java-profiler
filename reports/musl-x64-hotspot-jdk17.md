---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 11:57:04 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 8 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 10 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 66-68 cores)</summary>

```
1794502103 68
1794502108 68
1794502113 68
1794502118 68
1794502123 68
1794502128 68
1794502133 68
1794502138 68
1794502143 68
1794502148 66
1794502153 66
1794502158 66
1794502163 66
1794502168 66
1794502173 66
1794502178 66
1794502183 66
1794502188 66
1794502193 66
1794502198 66
```
</details>

---

