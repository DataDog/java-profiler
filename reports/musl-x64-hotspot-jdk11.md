---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 11:57:04 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 12 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 9 |
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

