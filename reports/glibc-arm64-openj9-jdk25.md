---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 12:27:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 14 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1794504191 48
1794504196 48
1794504201 48
1794504206 48
1794504211 48
1794504216 48
1794504221 48
1794504226 48
1794504231 48
1794504236 48
1794504241 48
1794504246 28
1794504251 28
1794504256 28
1794504261 28
1794504266 28
1794504271 28
1794504276 28
1794504281 28
1794504286 28
```
</details>

---

