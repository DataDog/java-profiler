---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 04:46:08 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 834 |
| Sample Rate | 13.90/sec |
| Health Score | 869% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 27-64 cores)</summary>

```
1789980051 27
1789980056 27
1789980061 27
1789980066 27
1789980072 27
1789980077 27
1789980082 27
1789980087 27
1789980092 27
1789980097 27
1789980102 27
1789980107 27
1789980112 27
1789980117 27
1789980122 27
1789980127 27
1789980132 27
1789980137 27
1789980142 27
1789980147 27
```
</details>

---

