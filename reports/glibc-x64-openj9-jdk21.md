---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 13:47:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 10 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 811 |
| Sample Rate | 13.52/sec |
| Health Score | 845% |
| Threads | 11 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (2 unique values: 52-54 cores)</summary>

```
1795200171 54
1795200176 54
1795200181 54
1795200186 54
1795200191 54
1795200196 54
1795200201 54
1795200206 54
1795200211 54
1795200216 54
1795200221 54
1795200226 54
1795200231 54
1795200236 54
1795200241 52
1795200246 52
1795200251 52
1795200256 52
1795200261 52
1795200266 52
```
</details>

---

