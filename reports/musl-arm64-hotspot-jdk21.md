---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-20 08:51:02 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787229955 64
1787229960 64
1787229965 64
1787229970 64
1787229975 64
1787229980 64
1787229985 64
1787229990 64
1787229995 64
1787230000 64
1787230005 64
1787230010 64
1787230015 64
1787230020 64
1787230025 64
1787230030 64
1787230035 64
1787230040 64
1787230045 64
1787230050 64
```
</details>

---

