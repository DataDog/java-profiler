---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 17:14:30 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 11 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 57-61 cores)</summary>

```
1795558146 61
1795558151 61
1795558156 61
1795558161 61
1795558166 61
1795558171 59
1795558176 59
1795558181 59
1795558186 59
1795558191 59
1795558196 59
1795558201 57
1795558206 57
1795558211 57
1795558216 57
1795558221 59
1795558226 59
1795558231 59
1795558236 59
1795558241 59
```
</details>

---

