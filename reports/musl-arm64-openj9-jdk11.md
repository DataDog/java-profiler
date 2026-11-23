---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:39:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 8 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 13 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795451657 49
1795451662 49
1795451667 49
1795451672 49
1795451677 49
1795451682 49
1795451687 49
1795451692 49
1795451697 49
1795451702 49
1795451707 49
1795451712 49
1795451717 49
1795451722 49
1795451727 44
1795451732 44
1795451737 44
1795451742 44
1795451747 44
1795451752 44
```
</details>

---

