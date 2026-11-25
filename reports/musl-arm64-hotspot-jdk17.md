---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 08:44:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 318 |
| Sample Rate | 5.30/sec |
| Health Score | 331% |
| Threads | 11 |
| Allocations | 114 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 11 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795614045 47
1795614050 47
1795614055 47
1795614060 47
1795614065 47
1795614070 47
1795614076 47
1795614081 47
1795614086 47
1795614091 47
1795614096 47
1795614101 47
1795614106 47
1795614111 47
1795614116 42
1795614121 42
1795614126 42
1795614131 42
1795614136 42
1795614141 42
```
</details>

---

