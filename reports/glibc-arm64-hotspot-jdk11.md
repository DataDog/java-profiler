---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 11:57:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794502138 48
1794502143 48
1794502148 48
1794502153 48
1794502158 48
1794502163 48
1794502168 48
1794502173 48
1794502178 48
1794502183 48
1794502188 48
1794502193 48
1794502198 48
1794502203 48
1794502208 48
1794502213 48
1794502218 48
1794502223 48
1794502228 48
1794502233 48
```
</details>

---

