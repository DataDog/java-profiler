---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-24 05:16:31 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 14 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 40-46 cores)</summary>

```
1792833084 46
1792833089 46
1792833094 46
1792833099 41
1792833104 41
1792833109 41
1792833114 40
1792833119 40
1792833124 40
1792833129 40
1792833134 40
1792833139 40
1792833144 40
1792833149 40
1792833154 40
1792833159 40
1792833164 40
1792833169 40
1792833174 41
1792833179 41
```
</details>

---

