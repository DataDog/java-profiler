---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:23:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 9 |
| Allocations | 157 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 15 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 30-45 cores)</summary>

```
1795195177 30
1795195182 45
1795195187 45
1795195192 45
1795195197 30
1795195202 30
1795195207 30
1795195212 30
1795195217 30
1795195222 30
1795195227 30
1795195232 30
1795195237 30
1795195242 30
1795195247 30
1795195252 30
1795195257 30
1795195262 30
1795195267 30
1795195272 30
```
</details>

---

