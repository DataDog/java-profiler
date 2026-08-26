---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-26 01:04:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 9 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 12 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1787720260 40
1787720265 40
1787720270 40
1787720275 40
1787720280 40
1787720285 40
1787720290 48
1787720295 48
1787720300 48
1787720305 48
1787720310 48
1787720315 48
1787720320 48
1787720325 48
1787720330 48
1787720335 48
1787720340 48
1787720345 48
1787720350 48
1787720355 48
```
</details>

---

