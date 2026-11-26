---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 08:21:31 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 301 |
| Sample Rate | 5.02/sec |
| Health Score | 314% |
| Threads | 10 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 285 |
| Sample Rate | 4.75/sec |
| Health Score | 297% |
| Threads | 14 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (2 unique values: 37-42 cores)</summary>

```
1795698955 42
1795698960 42
1795698965 42
1795698970 42
1795698975 42
1795698980 42
1795698985 42
1795698990 42
1795698995 37
1795699000 37
1795699005 37
1795699010 37
1795699015 37
1795699020 37
1795699025 37
1795699030 37
1795699035 37
1795699040 37
1795699045 37
1795699050 37
```
</details>

---

