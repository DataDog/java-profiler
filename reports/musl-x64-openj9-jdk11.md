---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:29:24 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 8 |
| Allocations | 555 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795620197 85
1795620202 85
1795620207 85
1795620212 85
1795620217 85
1795620222 85
1795620227 85
1795620232 85
1795620237 85
1795620242 85
1795620247 87
1795620252 87
1795620257 87
1795620262 87
1795620267 87
1795620272 87
1795620277 87
1795620282 87
1795620287 87
1795620292 87
```
</details>

---

