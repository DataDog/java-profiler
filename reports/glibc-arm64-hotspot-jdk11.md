---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 15:00:49 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 352 |
| Sample Rate | 5.87/sec |
| Health Score | 367% |
| Threads | 13 |
| Allocations | 172 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1786388154 32
1786388159 32
1786388164 32
1786388169 32
1786388174 32
1786388179 32
1786388184 32
1786388189 32
1786388194 32
1786388199 32
1786388204 32
1786388209 32
1786388214 32
1786388219 32
1786388224 32
1786388230 32
1786388235 32
1786388240 32
1786388245 27
1786388250 27
```
</details>

---

