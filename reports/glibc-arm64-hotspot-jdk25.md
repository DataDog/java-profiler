---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 11:01:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
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
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 12 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 14 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794326141 48
1794326146 43
1794326151 43
1794326156 43
1794326161 43
1794326166 43
1794326171 43
1794326176 43
1794326181 43
1794326186 43
1794326191 43
1794326196 43
1794326201 43
1794326206 43
1794326211 43
1794326216 48
1794326221 48
1794326226 48
1794326231 48
1794326236 48
```
</details>

---

