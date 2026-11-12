---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 08:02:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (3 unique values: 89-93 cores)</summary>

```
1794488222 91
1794488227 91
1794488232 91
1794488237 91
1794488242 91
1794488247 91
1794488252 91
1794488257 91
1794488262 91
1794488267 89
1794488272 89
1794488277 89
1794488282 89
1794488287 89
1794488292 89
1794488297 89
1794488302 89
1794488307 91
1794488312 91
1794488317 91
```
</details>

---

