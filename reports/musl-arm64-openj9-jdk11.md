---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:22:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (5 unique values: 49-59 cores)</summary>

```
1795429069 49
1795429074 49
1795429079 49
1795429084 49
1795429089 49
1795429094 49
1795429099 49
1795429104 49
1795429109 55
1795429114 55
1795429119 55
1795429124 55
1795429129 50
1795429134 50
1795429139 50
1795429144 50
1795429149 59
1795429154 59
1795429159 59
1795429164 54
```
</details>

---

