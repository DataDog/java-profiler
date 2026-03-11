---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-11 14:07:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 13 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 63-68 cores)</summary>

```
1773252119 63
1773252124 63
1773252129 63
1773252134 63
1773252139 63
1773252144 63
1773252149 63
1773252154 63
1773252159 63
1773252164 63
1773252169 63
1773252174 63
1773252179 63
1773252184 63
1773252189 63
1773252194 63
1773252199 63
1773252204 63
1773252209 63
1773252214 68
```
</details>

---

