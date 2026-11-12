---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 08:02:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (4 unique values: 31-48 cores)</summary>

```
1794488212 31
1794488217 31
1794488222 31
1794488227 31
1794488232 31
1794488237 31
1794488242 31
1794488247 31
1794488252 31
1794488257 31
1794488262 31
1794488267 31
1794488272 36
1794488277 36
1794488282 36
1794488287 36
1794488292 36
1794488297 36
1794488302 36
1794488307 36
```
</details>

---

