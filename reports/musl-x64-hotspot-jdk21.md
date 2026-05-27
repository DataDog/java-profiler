---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-27 06:39:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 42-43 cores)</summary>

```
1779878190 42
1779878195 42
1779878200 42
1779878205 42
1779878210 42
1779878215 42
1779878220 42
1779878225 43
1779878230 43
1779878235 43
1779878240 43
1779878245 43
1779878250 43
1779878255 43
1779878260 43
1779878265 43
1779878270 43
1779878275 43
1779878280 43
1779878285 43
```
</details>

---

