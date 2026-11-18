---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 12:33:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1795022943 62
1795022948 62
1795022953 62
1795022958 62
1795022963 62
1795022968 62
1795022973 62
1795022978 62
1795022983 62
1795022988 64
1795022993 64
1795022998 64
1795023003 64
1795023008 64
1795023013 64
1795023018 64
1795023023 64
1795023028 64
1795023033 64
1795023038 64
```
</details>

---

