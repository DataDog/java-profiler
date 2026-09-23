---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-23 10:08:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
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
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 40-45 cores)</summary>

```
1790172204 42
1790172209 42
1790172214 42
1790172219 42
1790172224 42
1790172229 42
1790172234 42
1790172239 42
1790172244 42
1790172249 42
1790172254 42
1790172259 42
1790172264 42
1790172269 41
1790172274 41
1790172279 45
1790172284 45
1790172289 45
1790172294 45
1790172299 40
```
</details>

---

