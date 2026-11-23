---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:39:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 11 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 55-64 cores)</summary>

```
1795451627 64
1795451632 64
1795451637 55
1795451642 55
1795451647 55
1795451652 55
1795451657 55
1795451662 55
1795451667 55
1795451672 55
1795451677 55
1795451682 55
1795451687 55
1795451692 55
1795451697 60
1795451702 60
1795451707 55
1795451712 55
1795451717 55
1795451722 55
```
</details>

---

