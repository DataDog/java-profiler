---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 12:04:39 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 11 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1793203160 14
1793203165 14
1793203170 14
1793203175 14
1793203180 14
1793203185 14
1793203190 14
1793203195 14
1793203200 14
1793203205 14
1793203210 14
1793203215 14
1793203220 14
1793203225 14
1793203230 14
1793203235 14
1793203240 14
1793203245 14
1793203250 9
1793203255 9
```
</details>

---

