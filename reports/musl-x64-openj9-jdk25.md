---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 13:47:35 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 80-91 cores)</summary>

```
1795200149 88
1795200154 88
1795200159 88
1795200164 88
1795200169 88
1795200174 88
1795200179 88
1795200184 88
1795200189 88
1795200194 88
1795200199 91
1795200204 91
1795200209 91
1795200214 91
1795200219 91
1795200224 91
1795200229 91
1795200234 91
1795200239 91
1795200244 80
```
</details>

---

