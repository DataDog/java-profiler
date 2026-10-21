---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 08:20:54 EDT

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
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 10 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 817 |
| Sample Rate | 13.62/sec |
| Health Score | 851% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (4 unique values: 48-54 cores)</summary>

```
1792584986 49
1792584991 49
1792584996 49
1792585001 54
1792585006 54
1792585011 54
1792585016 54
1792585021 54
1792585026 49
1792585031 49
1792585036 48
1792585041 48
1792585046 48
1792585051 48
1792585056 48
1792585061 48
1792585066 48
1792585071 48
1792585076 48
1792585081 48
```
</details>

---

