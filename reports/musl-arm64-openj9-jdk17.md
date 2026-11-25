---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 08:44:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 15 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (2 unique values: 44-47 cores)</summary>

```
1795614030 47
1795614035 47
1795614040 47
1795614045 47
1795614050 47
1795614055 47
1795614060 47
1795614066 47
1795614071 47
1795614076 47
1795614081 47
1795614086 47
1795614091 44
1795614096 44
1795614101 44
1795614106 44
1795614111 44
1795614116 44
1795614121 44
1795614126 44
```
</details>

---

