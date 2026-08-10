---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 15:00:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 89-96 cores)</summary>

```
1786388159 89
1786388164 89
1786388169 91
1786388174 91
1786388179 91
1786388184 91
1786388189 91
1786388194 91
1786388199 91
1786388204 91
1786388209 91
1786388214 91
1786388219 91
1786388224 91
1786388229 91
1786388234 91
1786388239 91
1786388244 93
1786388249 93
1786388254 93
```
</details>

---

