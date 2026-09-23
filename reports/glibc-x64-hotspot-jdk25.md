---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 10:08:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 58-62 cores)</summary>

```
1790172192 62
1790172197 62
1790172202 60
1790172207 60
1790172212 60
1790172217 60
1790172222 60
1790172227 60
1790172232 62
1790172237 62
1790172242 62
1790172247 62
1790172252 62
1790172257 62
1790172262 62
1790172267 60
1790172272 60
1790172277 60
1790172282 60
1790172287 60
```
</details>

---

