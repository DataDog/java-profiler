---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 09:43:02 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 353 |
| Sample Rate | 5.88/sec |
| Health Score | 368% |
| Threads | 9 |
| Allocations | 176 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 9 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 40-45 cores)</summary>

```
1794494179 42
1794494184 42
1794494189 42
1794494194 42
1794494199 42
1794494204 40
1794494209 40
1794494214 40
1794494219 40
1794494224 40
1794494229 40
1794494234 45
1794494239 45
1794494244 45
1794494249 45
1794494254 45
1794494259 45
1794494264 45
1794494269 45
1794494274 45
```
</details>

---

