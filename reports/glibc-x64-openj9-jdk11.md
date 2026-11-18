---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:07:54 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 50-56 cores)</summary>

```
1795014171 53
1795014176 53
1795014181 53
1795014186 53
1795014191 53
1795014196 53
1795014201 53
1795014206 50
1795014211 50
1795014216 50
1795014221 50
1795014226 50
1795014231 50
1795014236 50
1795014241 50
1795014246 50
1795014251 50
1795014256 50
1795014261 50
1795014266 50
```
</details>

---

