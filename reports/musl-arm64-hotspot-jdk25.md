---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:47:15 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794408136 48
1794408141 48
1794408146 48
1794408151 48
1794408156 48
1794408161 48
1794408166 48
1794408171 48
1794408176 48
1794408181 43
1794408186 43
1794408191 43
1794408196 43
1794408201 43
1794408206 43
1794408211 43
1794408216 43
1794408221 43
1794408226 43
1794408231 43
```
</details>

---

