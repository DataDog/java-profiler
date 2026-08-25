---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-25 16:41:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 7 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 9 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1787690305 64
1787690310 64
1787690315 64
1787690320 64
1787690325 64
1787690330 59
1787690335 59
1787690340 59
1787690345 59
1787690350 54
1787690355 54
1787690360 54
1787690365 54
1787690370 54
1787690375 54
1787690380 54
1787690385 59
1787690390 59
1787690395 59
1787690400 59
```
</details>

---

