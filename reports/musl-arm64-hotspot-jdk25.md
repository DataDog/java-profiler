---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-03 04:34:57 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 10 |
| Allocations | 35 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (4 unique values: 42-59 cores)</summary>

```
1791016239 42
1791016244 42
1791016249 42
1791016254 42
1791016259 47
1791016264 47
1791016269 47
1791016274 47
1791016279 54
1791016284 54
1791016289 54
1791016294 54
1791016299 54
1791016304 54
1791016309 54
1791016314 54
1791016319 54
1791016324 54
1791016329 54
1791016334 54
```
</details>

---

