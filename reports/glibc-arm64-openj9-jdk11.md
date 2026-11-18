---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:07:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 15 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1795014191 51
1795014196 51
1795014201 51
1795014206 51
1795014211 51
1795014216 51
1795014221 51
1795014226 51
1795014231 51
1795014236 51
1795014241 51
1795014246 51
1795014251 51
1795014256 51
1795014261 51
1795014266 51
1795014271 51
1795014276 51
1795014281 51
1795014286 51
```
</details>

---

