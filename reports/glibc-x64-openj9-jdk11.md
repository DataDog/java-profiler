---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 08:02:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 8 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (2 unique values: 63-65 cores)</summary>

```
1794488217 63
1794488222 63
1794488227 63
1794488232 63
1794488237 63
1794488242 63
1794488247 63
1794488252 63
1794488257 63
1794488262 63
1794488267 63
1794488272 63
1794488277 63
1794488282 63
1794488287 63
1794488292 63
1794488297 63
1794488302 65
1794488307 65
1794488312 65
```
</details>

---

