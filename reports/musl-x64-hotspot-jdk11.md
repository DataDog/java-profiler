---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 09:14:07 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 926 |
| Sample Rate | 15.43/sec |
| Health Score | 964% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1792588093 91
1792588098 91
1792588103 91
1792588108 91
1792588113 91
1792588118 91
1792588123 91
1792588128 91
1792588133 91
1792588138 91
1792588143 91
1792588148 91
1792588153 91
1792588158 89
1792588163 89
1792588168 89
1792588173 89
1792588178 89
1792588183 89
1792588188 89
```
</details>

---

