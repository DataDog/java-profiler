---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 13:06:41 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1786122133 53
1786122138 53
1786122143 53
1786122148 53
1786122153 53
1786122158 53
1786122163 53
1786122168 53
1786122173 53
1786122178 53
1786122183 48
1786122188 48
1786122193 48
1786122198 48
1786122203 48
1786122208 48
1786122213 48
1786122218 48
1786122223 48
1786122228 48
```
</details>

---

