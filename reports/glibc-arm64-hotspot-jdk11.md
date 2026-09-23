---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:08:36 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 11 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790172231 50
1790172236 50
1790172241 50
1790172246 50
1790172251 50
1790172256 50
1790172261 50
1790172266 50
1790172271 50
1790172276 50
1790172281 50
1790172287 50
1790172292 50
1790172297 50
1790172302 50
1790172307 50
1790172312 50
1790172317 50
1790172322 50
1790172327 50
```
</details>

---

