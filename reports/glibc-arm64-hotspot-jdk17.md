---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 08:37:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795786370 42
1795786375 42
1795786380 42
1795786385 42
1795786390 42
1795786395 42
1795786400 42
1795786405 42
1795786410 42
1795786415 42
1795786420 42
1795786425 42
1795786430 42
1795786435 47
1795786440 47
1795786445 47
1795786450 47
1795786455 47
1795786460 47
1795786465 47
```
</details>

---

