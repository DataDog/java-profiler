---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 12:40:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (4 unique values: 27-32 cores)</summary>

```
1793378152 30
1793378157 30
1793378162 30
1793378167 32
1793378172 32
1793378177 29
1793378182 29
1793378187 29
1793378192 29
1793378197 29
1793378202 29
1793378207 29
1793378212 29
1793378217 29
1793378222 29
1793378227 29
1793378232 29
1793378237 27
1793378242 27
1793378247 27
```
</details>

---

