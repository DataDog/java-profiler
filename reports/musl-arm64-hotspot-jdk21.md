---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 05:22:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 201 |
| Sample Rate | 3.35/sec |
| Health Score | 209% |
| Threads | 11 |
| Allocations | 141 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 11 |
| Allocations | 128 |

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
1795429149 50
1795429154 59
1795429159 59
1795429165 54
```
</details>

---

