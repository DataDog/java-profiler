---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-11 09:47:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
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
1794408236 43
1794408241 48
1794408246 48
```
</details>

---

