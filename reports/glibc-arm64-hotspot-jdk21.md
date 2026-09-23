---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 10:08:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 8 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1790172197 31
1790172202 31
1790172207 31
1790172212 31
1790172217 31
1790172222 31
1790172227 31
1790172232 31
1790172237 36
1790172242 36
1790172247 36
1790172252 36
1790172257 36
1790172262 36
1790172267 36
1790172272 36
1790172277 36
1790172282 36
1790172287 36
1790172292 36
```
</details>

---

