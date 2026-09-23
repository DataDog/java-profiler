---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 10:08:37 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 11 |
| Allocations | 172 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 14 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1790172194 45
1790172199 45
1790172204 45
1790172209 45
1790172214 45
1790172219 45
1790172224 45
1790172229 45
1790172234 48
1790172239 48
1790172244 48
1790172249 48
1790172254 48
1790172259 48
1790172264 48
1790172269 48
1790172274 48
1790172279 48
1790172284 48
1790172289 48
```
</details>

---

