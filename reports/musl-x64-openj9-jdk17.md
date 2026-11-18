---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:07:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 69-74 cores)</summary>

```
1795014166 73
1795014171 73
1795014176 73
1795014181 73
1795014186 73
1795014191 73
1795014196 73
1795014201 73
1795014206 73
1795014211 73
1795014216 73
1795014221 73
1795014226 74
1795014231 74
1795014236 74
1795014241 71
1795014246 71
1795014251 71
1795014256 71
1795014261 71
```
</details>

---

