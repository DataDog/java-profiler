---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-29 08:52:42 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 5.77/sec |
| Health Score | 361% |
| Threads | 12 |
| Allocations | 166 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793278106 48
1793278111 48
1793278116 43
1793278121 43
1793278126 43
1793278132 43
1793278137 43
1793278142 43
1793278147 43
1793278152 43
1793278157 43
1793278162 43
1793278167 43
1793278172 43
1793278177 43
1793278182 43
1793278187 48
1793278192 48
1793278197 48
1793278202 48
```
</details>

---

